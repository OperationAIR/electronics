#include "board.h"
#include "board_GPIO_ID.h"

#include <chip.h>
#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <lpc_tools/GPIO_HAL_LPC.h>
#include <lpc_tools/clock.h>
#include <mcu_timing/delay.h>
#include <stdio.h>
#include <string.h>
#include "settings.h"

#include <c_utils/ringbuffer.h>

#include "pi_communication.h"

#define CLK_FREQ (48e6)

volatile char buf[256];

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 256	/* Send */
#define UART_RRB_SIZE 256	/* Receive */
/* Transmit and receive ring buffers */
STATIC RINGBUFF_T txring;
static uint8_t txbuff[UART_SRB_SIZE];



uint8_t rb_Rx_buffer[UART_RRB_SIZE];
Ringbuffer rb_Rx;

OperationSettings settings;

/**
 * Dummy syscall to use printf features
 */
void *_sbrk(int incr)
{
    void *st = 0;
    return st;
}

/**
 * @brief	UART interrupt handler using ring buffers
 * @return	Nothing
 */
void UART_IRQHandler(void)
{

	/* Want to handle any errors? Do it here. */

	/* Use default ring buffer handler. Override this with your own
	   code if you need more capability. */
	// Chip_UART_IRQRBHandler(LPC_USART, &rxring, &txring);


	/* Handle transmit interrupt if enabled */
	if (LPC_USART->IER & UART_IER_THREINT) {
		Chip_UART_TXIntHandlerRB(LPC_USART, &txring);

		/* Disable transmit interrupt if the ring buffer is empty */
		if (RingBuffer_IsEmpty(&txring)) {
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
	/* Before using the ring buffers, initialize them using the ring
	   buffer init function */
	// RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(LPC_USART, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_EnableIRQ(UART0_IRQn);

}

bool match_start_sequence()
{
	size_t count = ringbuffer_used_count(&rb_Rx);
	if (count >= 4) {
		uint8_t byte;
		int i = 0;
		while (0 < count--) {
			uint32_t *ptr = ringbuffer_get_readable(&rb_Rx);
			uint32_t start;
			memcpy(&start, ptr, 4);// = *ptr; Misaligned access, is that okay?
			if (start == 0x41424344) {
				ringbuffer_flush(&rb_Rx, 4);
				return true;
			} else {
				// no match, advance rb 1 byte, try again until magic sequence is found
				ringbuffer_advance(&rb_Rx);
			}
		}
	}

	return false;

}

int main(void)
{
    board_setup();
    board_setup_NVIC();
    board_setup_pins();

	// configure System Clock at 48MHz
	clock_set_frequency(CLK_FREQ);
	SystemCoreClockUpdate();

    delay_init();

    // get the GPIO with the led (see board.c)
    const GPIO *led = board_get_GPIO(GPIO_ID_LED);

	Uart_Init();



	snprintf(buf, sizeof(buf) - 1, "Uart test\n");
	Chip_UART_SendRB(LPC_USART, &txring, buf, sizeof(buf) - 1);

	delay_us(1000*1000);

	bool match = false;
	uint8_t bytes[50];
	memset(bytes, 0, sizeof(bytes));
	while(true)
	{
        delay_us(100*1000);


		pi_comm_tasks(&rb_Rx);

		// if (!match) {
		// 	match = match_start_sequence();
		// }

		// size_t count = ringbuffer_used_count(&rb_Rx);
		// if (match && (count >= sizeof(OperationSettings))) {
		// 	GPIO_HAL_toggle(led);
		// 	OperationSettings *ptr = ringbuffer_get_readable(&rb_Rx);
		// 	memcpy(&settings, ptr, sizeof(OperationSettings));
		// 	ringbuffer_clear(&rb_Rx);
		// 	match = false;

		// 	// todo verify settings, check for valid range

		// 	// send back settings
		// 	Chip_UART_SendRB(LPC_USART, &txring, &settings, sizeof(settings));

		// }


	}
	return 0;
}

