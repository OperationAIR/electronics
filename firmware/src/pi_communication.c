
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <chip.h>

#include <c_utils/ringbuffer.h>

#include "settings.h"
#include "crc/crc.h"


/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 256	/* Send */
#define UART_RRB_SIZE 256	/* Receive */

uint8_t rb_Rx_buffer[UART_RRB_SIZE];
uint8_t rb_Tx_buffer[UART_SRB_SIZE];

Ringbuffer rb_Rx;
Ringbuffer rb_Tx;


enum PiCommand {
    PiCommandNone = 0,
    PiCommandNewSettings = 1,
    PiCommandRequestSensorValues = 2,
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
	/* Setup UART for 115.2K8N1 */
	Chip_UART_Init(LPC_USART);
	Chip_UART_SetBaud(LPC_USART, 115200);
	Chip_UART_ConfigData(LPC_USART, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT));
	Chip_UART_SetupFIFOS(LPC_USART, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
	Chip_UART_TXEnable(LPC_USART);


	ringbuffer_init(&rb_Rx, rb_Rx_buffer, 1, UART_RRB_SIZE);
    ringbuffer_init(&rb_Tx, rb_Tx_buffer, 1, UART_RRB_SIZE);
	/* Before using the ring buffers, initialize them using the ring
	   buffer init function */

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(LPC_USART, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_EnableIRQ(UART0_IRQn);
}

void pi_comm_init(void)
{
	Uart_Init();
}


static enum PiCommand match_start_sequence(Ringbuffer *rb)
{
	size_t count = ringbuffer_used_count(rb);
	if (count >= 4) {
		while (0 < count--) {
			uint32_t *ptr = ringbuffer_get_readable(rb);
			uint32_t start;
			memcpy(&start, ptr, 4);// = *ptr; Misaligned access, is that okay?
			if (start == 0x41424344) {
				ringbuffer_flush(rb, 4);
				return PiCommandNewSettings;
			} else {
				// no match, advance rb 1 byte, try again until magic sequence is found
				ringbuffer_advance(rb);
			}
		}
	}

	return PiCommandNone;

}

void pi_comm_tasks()
{
    if (g_current_command == PiCommandNone) {
        g_current_command = match_start_sequence(&rb_Rx);
    }

    if (g_current_command == PiCommandNewSettings) {
        size_t count = ringbuffer_used_count(&rb_Rx);
		if (count >= sizeof(OperationSettings)) {
			OperationSettings *settings = ringbuffer_get_readable(&rb_Rx);

            uint16_t res = crc16_usb_stream_check(&settings->crc, (uint8_t*)settings, 20);

            if (res == settings->crc) {
                const bool settings_ok = settings_update(settings);
                if (!settings_ok) {
                    // settings error
                }
            } else {
                // crc error
            }
			ringbuffer_clear(&rb_Rx);
			g_current_command = PiCommandNone;
		}
    }
}

void pi_comm_send(uint8_t *buffer, size_t len)
{
	Chip_UART_IntDisable(LPC_USART, UART_IER_THREINT);
    ringbuffer_write(&rb_Tx, buffer, len);
    Chip_UART_IntEnable(LPC_USART, UART_IER_THREINT);
	UART_IRQHandler(); //TODO: does this make sense? Compare with uint32_t Chip_UART_SendRB from chip libray
}
