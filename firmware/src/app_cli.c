#include "cli.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <mcu_timing/delay.h>
#include <startup_lpc11xxx/stacktools.h>

#include "watchdog.h"
#include "cdc_vcom.h"
#include "log.h"
#include "board.h"
#include "global_settings.h"
#include "app.h"
#include "actuators/control_signals.h"
#include "actuators/DPR.h"
#include "sensors/sensors.h"
#include "stats.h"
#include "clock.h"
#include "generated/firmware_version.h"

#include <chip.h>

#ifndef FIRMWARE_VERSION
    #error "Please define FIRMWARE_VERSION in the Makefile"
#endif


#define MAX_USB_PACKET_LENGHT 64
char cmd_buf[MAX_USB_PACKET_LENGHT + 1]; // +1 byte for 0 terminator

extern DPR dpr;

void current_time(char *args) {

	char time[20];
	log_get_time_as_str(time);
	log_cli(time);
}


void start(char *args) {
	app_program_start();
}

void stop(char *args) {
	app_program_stop();
}

void dpr_test(char *args) {
    bool ok = DPR_enable(&dpr);

    int status = DPR_status(&dpr);
    log_wtime("DPR status: %d", status);

    ok&= DPR_write(&dpr, 2048);
    delay_us(1000*1000);
    ok&= DPR_write(&dpr, 0);

    log_wtime("DPR test: %s", (ok ? "OK" : "ERR"));

}


void led_status(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_LED_status_on();
		log_cli("Enable status LED");
	} else if (strncmp(args, "off", 3) == 0) {
		control_LED_status_off();
		log_cli("Disable status LED");
	}
}
void led_error(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_LED_error_on();
		log_cli("Enable error LED");
	} else if (strncmp(args, "off", 3) == 0) {
		control_LED_error_off();
		log_cli("Disable error LED");
	}
}

void switch1(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_switch1_on();
		log_cli("Enable switch 1");
	} else if (strncmp(args, "off", 3) == 0) {
		control_switch1_off();
		log_cli("Disable switch 1");
	} else {
		if (control_switch1_get_state()) {
			log_cli("Switch 1: On");
		} else {
			log_cli("Switch 1: Off");
		}
	}
}

void switch2(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_switch2_on();
		log_cli("Enable switch 2");
	} else if (strncmp(args, "off", 3) == 0) {
		control_switch2_off();
		log_cli("Disable switch 2");
	} else {
		if (control_switch2_get_state()) {
			log_cli("Switch 2: on");
		} else {
			log_cli("Switch 2: off");
		}
	}
}

void halt(char *args)
{
	app_halt();
	log_cli("Halt application..");
}

void resume(char *args)
{
	app_resume();
	log_cli("Resume application..");
}

void app(char *args)
{
	if (app_is_running()) {
		log_cli("app is running in state [%s]", app_get_state());
	} else {
		log_cli("app is halted in state [%s]", app_get_state());
	}
}

void test(char *args)
{
	app_self_test();
}

void serial_number(char *args)
{
	char buf[SERIAL_NUM_STR_SIZE];
    log_wtime("serial number:\r\n%s", log_get_serialnumber_str(buf, SERIAL_NUM_STR_SIZE));
}

void version(char *args)
{
	log_cli("Firmware version:");
	log_cli(FIRMWARE_VERSION);
}

void pressure(char *args)
{
	log_cli("Pressure: N/A");
}

void valves_toggle(char *args)
{
	log_cli("Not supported!");
}

void status() {
	app("");
	switch1("");
	switch2("");
	led_status("");
}

CliCommand cli_commands[] = {
	{
		.cmd = "status",
		.help = "Print a status overview of internal state",
		.function = status
	},
	{
		.cmd = "time",
		.help = "Show the current (relative) time",
		.function = current_time
	},
	{
		.cmd = "start",
		.help = "start (demo) program",
		.function = start
	},
	{
		.cmd = "stop",
		.help = "stop (demo) program",
		.function = stop
	},
	{
		.cmd = "led_status",
		.help = "Control status led: 'on' or 'off'",
		.function = led_status
	},
	{
		.cmd = "DPR_test",
		.help = "Enables DPR for 1 second at half-scale",
		.function = dpr_test
	},
	{
		.cmd = "led_error",
		.help = "Control error led: 'on' or 'off'",
		.function = led_error
	},
	{
		.cmd = "switch1",
		.help = "Control switch 1: 'on' or 'off'",
		.function = switch1
	},
	{
		.cmd = "switch2",
		.help = "Control valve 2: 'on' or 'off'",
		.function = switch2
	},
	{
		.cmd = "halt",
		.help = "Halt application state machine",
		.function = halt
	},
	{
		.cmd = "cont",
		.help = "continue/resume application state machine",
		.function = resume
	},
	{
		.cmd = "app",
		.help = "get app status",
		.function = app
	},
	{
		.cmd = "sn",
		.help = "get 128bit chip serial number",
		.function = serial_number
	},
	{
		.cmd = "version",
		.help = "Firmware version",
		.function = version
	},
};

void app_cli_init() {
    cli_init(cli_commands, sizeof(cli_commands) / sizeof(CliCommand), (write_fn)log_cli);
}

void add_cli_tasks() {
	uint32_t l = vcom_bread((uint8_t*)cmd_buf, MAX_USB_PACKET_LENGHT);
	if (l) {
		cmd_buf[l] = 0;
		cli_exec(cmd_buf, l);
	}
}
