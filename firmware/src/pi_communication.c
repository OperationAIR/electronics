
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <chip.h>

#include <c_utils/ringbuffer.h>
#include <mcu_timing/delay.h>

#include "pi_communication.h"

#include "app.h"
#include "settings.h"
#include "crc/crc.h"

#include "actuators/control_signals.h"
#include "sensors/sensors.h"

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 256	/* Send */
#define UART_RRB_SIZE 256	/* Receive */

uint8_t rb_Rx_buffer[UART_RRB_SIZE];
uint8_t rb_Tx_buffer[UART_SRB_SIZE];

Ringbuffer rb_Rx;
Ringbuffer rb_Tx;


enum PiCommand {
    PiCommandNone 					= 0,
	PiCommandLedOn 					= 0x55550000,
	PiCommandLedOff 				= 0x66660000,
    PiCommandNewSettings 			= 0x41424344,
    PiCommandRequestSensorValues 	= 0x22226666,
	PiCommandSwitch1On				= 0x55551111,
	PiCommandSwitch1Off				= 0x66661111,
	PiCommandSwitch2On				= 0x55553333,
	PiCommandSwitch2Off				= 0x66663333,
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
            if (byte) {
                Chip_UART_SendByte(LPC_USART, *byte);
                ringbuffer_advance(&rb_Tx);
            }
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
	Chip_UART_SetBaud(LPC_USART, 115200);
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


static enum PiCommand match_start_sequence(Ringbuffer *rb)
{
	uint32_t cmd = PiCommandNone;
	size_t count = ringbuffer_used_count(rb);
	if (count >= 4) {
		while (0 < count--) {
			uint32_t *ptr = ringbuffer_get_readable(rb);
			memcpy(&cmd, ptr, 4); // cmd = *ptr; memcpy to handle misaligned access.
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
				case PiCommandSwitch1On:
					ringbuffer_flush(rb, 4);
					control_switch1_on(10000);
					pi_comm_send_string("Switch 1 On\n");
					return PiCommandNone;
				case PiCommandSwitch1Off:
					ringbuffer_flush(rb, 4);
					control_switch1_off();
					pi_comm_send_string("Switch 1 Off\n");
					return PiCommandNone;
				case PiCommandSwitch2On:
					ringbuffer_flush(rb, 4);
					control_switch2_on();
					pi_comm_send_string("Switch 2 On\n");
					return PiCommandNone;
				case PiCommandSwitch2Off:
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
			sensors_read_all(&data);
			uint16_t crc_state = 0xFFFF;
            uint16_t crc16 = crc16_usb_stream_check(&crc_state, (uint8_t*)&data, sizeof(SensorsAllData));
			uint32_t prefix = PiCommandRequestSensorValues;
			pi_comm_send((uint8_t*)&prefix, 4);
			pi_comm_send((uint8_t*)&data, sizeof(SensorsAllData));
			pi_comm_send((uint8_t*)&crc16, 2);
			pi_comm_reset();
	} else if (g_current_command == PiCommandNewSettings) {
        size_t count = ringbuffer_used_count(&rb_Rx);
		if (count >= sizeof(OperationSettings)) {
			OperationSettings *settings = ringbuffer_get_readable(&rb_Rx);

			uint16_t crc_state = 0xFFFF;
            uint16_t res = crc16_usb_stream_check(&crc_state, (uint8_t*)settings, sizeof(OperationSettings)-2);

            if (res == settings->crc) {
                const bool settings_ok = settings_update(settings);
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
			ringbuffer_clear(&rb_Rx);
			g_current_command = PiCommandNone;
		} else if (delay_timeout_done(&pi_comm_timeout)) {
			pi_comm_reset();
		}
    }

}



void pi_comm_send_string(char *string)
{
	pi_comm_send((uint8_t*)"###", 3);
	pi_comm_send((uint8_t*)string, strlen(string));
}

void pi_comm_send(uint8_t *buffer, size_t len)
{
	Chip_UART_IntDisable(LPC_USART, UART_IER_THREINT);
    ringbuffer_write(&rb_Tx, buffer, len);
    Chip_UART_IntEnable(LPC_USART, UART_IER_THREINT);
	UART_IRQHandler(); //TODO: does this make sense? Compare with uint32_t Chip_UART_SendRB from chip libray
}
