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
#include "RGB_LED/LED_api.h"
#include "sensors/sensors.h"
#include "board.h"
#include "global_settings.h"
#include "app.h"
#include "actuators/control_signals.h"
#include "stats.h"
#include "clock.h"
#include "generated/firmware_version.h"

#include <chip.h>

#ifndef FIRMWARE_VERSION
    #error "Please define FIRMWARE_VERSION in the Makefile"
#endif


#define MAX_USB_PACKET_LENGHT 64
char cmd_buf[MAX_USB_PACKET_LENGHT + 1]; // +1 byte for 0 terminator


void pressure(char *args) {
	int pressure = sensors_read_pressure();
	log_cli("pressure: %d kPa", pressure);
}

void current_time(char *args) {

	char time[20];
	log_get_time_as_str(time);
	log_cli(time);
}

void led(char *args) {

	RGBColor color = {0, 0, 0};
	if (strncmp(args, "red", 3) == 0) {
		color.red = 200;
		log_cli("Set LED to RED");
		LED_set(&color);
	} else if (strncmp(args, "blue", 4) == 0) {
		color.blue = 200;
		log_cli("Set LED to Blue");
		LED_set(&color);
	} else if (strncmp(args, "green", 5) == 0) {
		color.green = 200;
		log_cli("Set LED to Green");
		LED_set(&color);
	} else if (strncmp(args, "yellow", 6) == 0) {
		color.red = 200;
		color.green = 200;
		log_cli("Set LED to Yellow");
		LED_set(&color);
	} else if (strncmp(args, "white", 5) == 0) {
		color.red = 200;
		color.green = 200;
		color.blue = 200;
		log_cli("Set LED to White");
		LED_set(&color);
	} else if (strncmp(args, "magenta", 7) == 0) {
		color.red = 200;
		color.blue = 200;
		log_cli("Set LED to Magenta");
		LED_set(&color);
	} else if (strncmp(args, "cyan", 4) == 0) {
		color.green = 200;
		color.blue = 200;
		log_cli("Set LED to Cyan");
		LED_set(&color);
	} else if (strncmp(args, "off", 3) == 0) {
		log_cli("Set LED off");
		LED_set(&color);
	} else if (strncmp(args, "help", 4) == 0) {
		// cli_remove_enter(args, 10);
		// log_cli("Unrecognized color '%s'", args);
		log_cli("Supported colors: red, green, blue, white, yellow, magenta, cyan, off");
	} else {
		RGBColor c;
		LED_get_color(&c);
		log_cli("LED: %u, %u, %u", c.red, c.green, c.blue);
	}

}

void start(char *args) {
	app_program_start();
}

void stop(char *args) {
	app_program_stop();
}

void valve1(char *args) {
	if (strncmp(args, "open", 4) == 0) {
		control_valve1_open();
		log_cli("Open valve 1");
	} else if (strncmp(args, "close", 5) == 0) {
		control_valve1_close();
		log_cli("Close valve 1");
	} else {
		if (control_valve1_get_state()) {
			log_cli("Valve 1: Open");
		} else {
			log_cli("Valve 1: Closed");
		}
	}
}

void valve2(char *args) {
	if (strncmp(args, "open", 4) == 0) {
		control_valve2_open();
		log_cli("Open valve 2");
	} else if (strncmp(args, "close", 5) == 0) {
		control_valve2_close();
		log_cli("Close valve 2");
	} else {
		if (control_valve2_get_state()) {
			log_cli("Valve 2: Open");
		} else {
			log_cli("Valve 2: Closed");
		}
	}
}

void valves_toggle(char *args)
{
	control_valves_toggle();
	log_cli("Toggling valves");
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

void status() {
	app("");
	pressure("");
	valve1("");
	valve2("");
	led("");
}

CliCommand cli_commands[] = {
	{
		.cmd = "status",
		.help = "Print a status overview of internal state",
		.function = status
	},
	{
		.cmd = "pres",
		.help = "The current pressure measurement",
		.function = pressure
	},
	{
		.cmd = "time",
		.help = "Show the current (relative) time",
		.function = current_time
	},
	{
		.cmd = "led",
		.help = "set led color: led [color]",
		.function = led
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
		.cmd = "valve1",
		.help = "Controll valve 1: 'open' or 'close'",
		.function = valve1
	},
	{
		.cmd = "valve2",
		.help = "Controll valve 2: 'open' or 'close'",
		.function = valve2
	},
	{
		.cmd = "valves toggle",
		.help = "Toggle the states of both valves",
		.function = valves_toggle
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
