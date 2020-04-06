
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <chip.h>

#include <c_utils/ringbuffer.h>
#include <mcu_timing/delay.h>
#include <lpc_tools/irq.h>

#include "pi_communication.h"

#include "app.h"
#include "settings.h"
#include "crc/crc.h"

#include "actuators/control_signals.h"
#include "sensors/sensors.h"

#define BAUDRATE 500000
/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 256	/* Send */
#define UART_RRB_SIZE 256	/* Receive */

uint8_t rb_Rx_buffer[UART_RRB_SIZE];
uint8_t rb_Tx_buffer[UART_SRB_SIZE];

Ringbuffer rb_Rx;
Ringbuffer rb_Tx;


enum PiCommand {
    PiCommandNone 					= 0,
    PiCommandNewSettings 			= 0x41424344,
	PiCommandRequestSettings 		= 0x45464748,
    PiCommandRequestSensorValues 	= 0x0D15EA5E,
	PiCommandLedOn 					= 0x55551111,
	PiCommandLedOff 				= 0x55661111,
	PiCommandErrorOn 				= 0x55552222,
	PiCommandErrorOff 				= 0x55662222,
	PiCommandSwitchExhaleOn			= 0x66663333,
	PiCommandSwitchExhaleOff		= 0x66773333,
	PiCommandSwitchInhaleOn			= 0x66664444,
	PiCommandSwitchInhaleOff		= 0x66774444,
	PiCommandSwitchExtraOn			= 0x66665555,
	PiCommandSwitchExtraOff			= 0x66775555,
	PiCommandMFCAirSet				= 0x77771111,
	PiCommandMFCAirGet				= 0x77881111,
	PiCommandMFCO2Set				= 0x77772222,
	PiCommandMFCO2Get				= 0x77882222,
	PiCommandBatteryLevel			= 0x88881111,
	PiCommandPowerStatus			= 0x88882222,
	PiCommandUserSwitchGet			= 0x88883333,
};
static enum PiCommand g_current_command = PiCommandNone;



/**
 * @brief	UART interrupt handler using ring buffers
 * @return	Nothing
 */
void UART_IRQHandler(void)
{
	/* Want to handle any errors? Do it here. */
    // TODO handle uart errors

	/* Handle transmit interrupt if enabled */
	if (LPC_USART->IER & UART_IER_THREINT) {

        /* Fill FIFO until full or until TX ring buffer is empty */
        while ((Chip_UART_ReadLineStatus(LPC_USART) & UART_LSR_THRE) != 0) {
            uint8_t *byte = ringbuffer_get_readable(&rb_Tx);
            if (!byte) {
                break;
            }
            Chip_UART_SendByte(LPC_USART, *byte);
            ringbuffer_advance(&rb_Tx);
        }

		/* Disable transmit interrupt if the ring buffer is empty */
        if (ringbuffer_is_empty(&rb_Tx)) {
			Chip_UART_IntDisable(LPC_USART, UART_IER_THREINT);
		}
	}

	// receive

	/* New data will be ignored if data not popped in time */
	while (Chip_UART_ReadLineStatus(LPC_USART) & UART_LSR_RDR) {
		uint8_t byte = Chip_UART_ReadByte(LPC_USART);
		ringbuffer_write(&rb_Rx, &byte, 1);
	}


}

static void Uart_Init(void)
{
	// Setup UART for 115.2K8N1
	Chip_UART_Init(LPC_USART);
	Chip_UART_SetBaud(LPC_USART, BAUDRATE);
	Chip_UART_ConfigData(LPC_USART, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT));
	Chip_UART_SetupFIFOS(LPC_USART, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
	Chip_UART_TXEnable(LPC_USART);

	ringbuffer_init(&rb_Rx, rb_Rx_buffer, 1, UART_RRB_SIZE);
    ringbuffer_init(&rb_Tx, rb_Tx_buffer, 1, UART_RRB_SIZE);

	// Enable receive data and line status interrupt
	Chip_UART_IntEnable(LPC_USART, (UART_IER_RBRINT | UART_IER_RLSINT));

	NVIC_EnableIRQ(UART0_IRQn);
}

void pi_comm_init(void)
{
	Uart_Init();
}


/**
 * Read ringbuffer elements without advancing read pointer
 *
 * NOTE: only call if you know for sure the amount of requested data
 * is in the ringbuffer! Otherwise this will block..
 */
uint32_t ringbuffer_read_ahead(Ringbuffer *ringbuffer,
        void *elements, uint32_t element_count)
{
    void *read;
    uint8_t *elems = elements;
    uint32_t elements_read = 0;
    while((elements_read < element_count)
            && (read = ringbuffer_get_readable_offset(ringbuffer, elements_read))) {
        memcpy(elems, read, ringbuffer->elem_sz);
        elems+= ringbuffer->elem_sz;
        elements_read++;
    }
    return elements_read;
}

static enum PiCommand match_start_sequence(Ringbuffer *rb)
{
	uint32_t cmd = PiCommandNone;
	size_t count = ringbuffer_used_count(rb);
	if (count >= 4) {
		while (4 <= count--) {
			ringbuffer_read_ahead(rb, &cmd, 4);
			switch (cmd) {
				case PiCommandNewSettings:
					ringbuffer_flush(rb, 4);
					return PiCommandNewSettings;
				case PiCommandRequestSensorValues:
					ringbuffer_flush(rb, 4);
					return PiCommandRequestSensorValues;
				case PiCommandLedOn:
					ringbuffer_flush(rb, 4);
					control_LED_status_on();
					pi_comm_send_string("Status LED on\n");
					return PiCommandNone;
				case PiCommandLedOff:
					ringbuffer_flush(rb, 4);
					control_LED_status_off();
					pi_comm_send_string("Status LED off\n");
					return PiCommandNone;
				case PiCommandSwitchExhaleOn:
					ringbuffer_flush(rb, 4);
					control_switch1_on(10000);
					pi_comm_send_string("Switch 1 On\n");
					return PiCommandNone;
				case PiCommandSwitchExhaleOff:
					ringbuffer_flush(rb, 4);
					control_switch1_off();
					pi_comm_send_string("Switch 1 Off\n");
					return PiCommandNone;
				case PiCommandSwitchInhaleOn:
					ringbuffer_flush(rb, 4);
					control_switch2_on();
					pi_comm_send_string("Switch 2 On\n");
					return PiCommandNone;
				case PiCommandSwitchInhaleOff:
					ringbuffer_flush(rb, 4);
					control_switch2_off();
					pi_comm_send_string("Switch 2 Off\n");
					return PiCommandNone;
				default:
					// no match, advance rb 1 byte, try again until magic sequence is found
					ringbuffer_advance(rb);
			}
		}
	}

	return PiCommandNone;

}

static delay_timeout_t pi_comm_timeout;

static void pi_comm_reset()
{
	g_current_command = PiCommandNone;
	ringbuffer_clear(&rb_Rx);
}

void pi_comm_tasks()
{
    if (g_current_command == PiCommandNone) {
        g_current_command = match_start_sequence(&rb_Rx);
		// start new command, set timout in case communication fails
		if (g_current_command) {
    		delay_timeout_set(&pi_comm_timeout, 10000);
		}
    }

	if (g_current_command == PiCommandRequestSensorValues) {

			SensorsAllData data;
            // Critical section: sensor data should be read atomically.
            // This guarantees no values are halfway being updated.
            const bool critical_section = irq_disable();
			sensors_read_all(&data);
            irq_restore(critical_section);

			uint16_t crc_state = 0xFFFF;
            uint16_t crc16 = crc16_usb_stream_check(&crc_state, (uint8_t*)&data, sizeof(SensorsAllData));
			uint32_t prefix = PiCommandRequestSensorValues;
			pi_comm_send((uint8_t*)&prefix, 4);
			pi_comm_send((uint8_t*)&data, sizeof(SensorsAllData));
			pi_comm_send((uint8_t*)&crc16, 2);
			g_current_command = PiCommandNone;
	} else if (g_current_command == PiCommandNewSettings) {
        size_t count = ringbuffer_used_count(&rb_Rx);
		if (count >= sizeof(OperationSettings)) {
			OperationSettings settings;
			ringbuffer_read(&rb_Rx, &settings, sizeof(OperationSettings));

			uint16_t crc_state = 0xFFFF;
            uint16_t res = crc16_usb_stream_check(&crc_state, (uint8_t*)&settings, sizeof(OperationSettings)-2);

            if (res == settings.crc) {
                const bool settings_ok = settings_update(&settings);
                if (settings_ok) {
					pi_comm_send_string("Settings Ok!\n");
					// send settings back for verification

					uint32_t prefix = PiCommandNewSettings;
					pi_comm_send((uint8_t*)&prefix, 4);
					pi_comm_send((uint8_t*)app_get_settings(), sizeof(OperationSettings));
                } else {
					control_LED_error_on();
					pi_comm_send_string("Error: settings verification failed!\n");
				}

            } else {
				pi_comm_send_string("CRC Error!\n");
                // crc error: send back settings so Rpi knows they're wrong
				uint32_t prefix = PiCommandNewSettings;
				pi_comm_send((uint8_t*)&prefix, 4);
				pi_comm_send((uint8_t*)app_get_settings(), sizeof(OperationSettings));
            }
			g_current_command = PiCommandNone;
		} else if (delay_timeout_done(&pi_comm_timeout)) {
			pi_comm_reset();
		}
    }

}



void pi_comm_send_string(char *string)
{
	pi_comm_send((uint8_t*)"####", 4);
	pi_comm_send((uint8_t*)string, strlen(string));
}

void pi_comm_send(uint8_t *buffer, size_t len)
{
	Chip_UART_IntDisable(LPC_USART, UART_IER_THREINT);
    ringbuffer_write(&rb_Tx, buffer, len);
    Chip_UART_IntEnable(LPC_USART, UART_IER_THREINT);
	UART_IRQHandler(); //TODO: does this make sense? Compare with uint32_t Chip_UART_SendRB from chip libray
}
