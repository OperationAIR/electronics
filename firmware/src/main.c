#include "board.h"
#include "board_GPIO_ID.h"
#include <lpc_tools/boardconfig.h>
#include <chip.h>

#include <lpc_tools/clock.h>
#include <lpc_tools/irq.h>
#include <mcu_timing/delay.h>

#include "global_settings.h"
#include "actuators/DPR.h"
#include "actuators/control_signals.h"
#include "usb/app_usb.h"
#include "watchdog.h"
#include "app.h"
#include "app_cli.h"
#include "log.h"
#include "clock.h"
#include "generated/firmware_version.h"

#include "cmsis_dsp_lib/arm_math.h"

#include <c_utils/ringbuffer.h>
#include "pi_communication.h"

#define CLK_FREQ (48e6)

void assert(bool should_be_true)
{
    if(should_be_true) {
        return;
    }

    // Something bad happened!
    // TODO alarm, reset? (enable watchdog, mcu will be reset..)
    while(1);
}

arm_pid_instance_f32 pid_instance;

void test_pid()
{
    float Kp = 1;
    float Ki = 0.1;
    float Kd = 0.01;

    arm_pid_reset_f32(&pid_instance);

    pid_instance.Kp = Kp;
    pid_instance.Ki = Ki;
    pid_instance.Kd = Kd;
    // init calculates the required coefficients based on the PID input
    // A0 = Kp + Ki + Kd
    // A1 = (-Kp ) - (2 * Kd )
    // A2 = Kd
    // The PID controller calculates the following transfer function
    // y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
    arm_pid_init_f32(&pid_instance, 1);

    float signal_in = 3.14;
    float signal_out = arm_pid_f32(&pid_instance, signal_in);

    log_wtime("PID in: %.3f", signal_in);

}

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 256	/* Send */
#define UART_RRB_SIZE 256	/* Receive */
/* Transmit and receive ring buffers */
STATIC RINGBUFF_T txring;
// static uint8_t rxbuff[UART_RRB_SIZE];
static uint8_t txbuff[UART_SRB_SIZE];



uint8_t rb_Rx_buffer[UART_RRB_SIZE];
uint8_t rb_Tx_buffer[UART_SRB_SIZE];

Ringbuffer rb_Rx;
Ringbuffer rb_Tx;



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
	// RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
	// RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(LPC_USART, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_EnableIRQ(UART0_IRQn);

}

DPR dpr;

int main(void)
{
    board_setup();
    board_setup_NVIC();
    board_setup_pins();

    clock_set_frequency(CLK_FREQ);
    SystemCoreClockUpdate();

    delay_init();
    logging_init();

    test_pid();
    // USB init
    if (!app_usb_init())
    {
        delay_us(2000 * 1000);
    }

    control_signals_init();

    const int hw_version = 0;

    app_init(hw_version);
    app_cli_init();
    watchdog_init();

    Uart_Init();

    log_wtime("Operation Air firmware started");
    char buf[SERIAL_NUM_STR_SIZE];
    log_wtime("serial number: %s", log_get_serialnumber_str(buf, SERIAL_NUM_STR_SIZE));
    log_wtime("Firmware version: %s", FIRMWARE_VERSION);


    DPR_init(&dpr, LPC_SSP1, board_get_GPIO(GPIO_ID_PREG_CS));

    GPIO *led_status = board_get_GPIO(GPIO_ID_LED_STATUS);
    GPIO *led_error = board_get_GPIO(GPIO_ID_LED_ERROR);

    GPIO_HAL_set(led_status, 1);
    GPIO_HAL_set(led_error, 1);

    while (true)
    {
        pi_comm_tasks(&rb_Rx);
        add_cli_tasks();
        log_tasks();

        // Maybe only feed watchdog if some sanity checks succeed?
        watchdog_feed();
    }
    return 0;
}

void HardFault_Handler(void)
{
    // Should never happen: system has crashed.
    // Watchdog will reboot the system eventually...
    while (1);
}

