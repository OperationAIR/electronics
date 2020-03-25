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
#include "log_storage/log_storage.h"
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

void logdata_erase(char *args)
{
	if(strncmp(args, "all", 3)) {
		log_cli("Are you sure? Type 'erase all' to erase all stored data");
		return;
	}
	if(log_storage_erase_all()) {
		log_cli("All logdata erased");
		char buf[SERIAL_NUM_STR_SIZE];
    	log_wtime("serial number: %s", log_get_serialnumber_str(buf, SERIAL_NUM_STR_SIZE));
		log_wtime("Firmware version: %s", FIRMWARE_VERSION);
	} else {
		log_cli("Failed to erase logdata!");
	}
}

void logdata(char *args)
{
    const size_t num_bytes = atoi(args);


    log_cli("== Start of logdata  ==");

    size_t offset = 0;
    while(true) {

        uint8_t buffer[64+1];
        size_t length = log_storage_read(LOG_STORE_TEXT, offset,
                buffer, sizeof(buffer)-1);
        buffer[length] = 0;

        if(!length) {
            break;
        }
        if(num_bytes && (offset >= num_bytes)) {
            break;
        }

		// replace all non-ascii values
		for(size_t i=0;i<length;i++) {
			if(buffer[i] > 127) {
				buffer[i] = '#';
			}
		}

        if(!log_cli("%s", (char*)buffer)) {
			log_cli("== End of logdata (aborted: timeout!) ==\r\n");
		}
        offset+= length;

		// This command may take very long, so we need to feed the watchdog
        watchdog_feed();

    }
    log_cli("== End of logdata (%u bytes) ==\r\n", offset);
}

void memory_info(char *args)
{
	const size_t total = stack_total_size();
	const size_t used = total - stack_unused_size();
	log_cli("Memory usage: %u/%u", used, total);
}

void pressure(char *args) {
	int pressure = sensors_read_pressure();
	log_cli("pressure: %d kPa", pressure);
}

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
		.cmd = "logdata",
		.help = "Print all stored logdata (may take a while..)",
		.function = logdata
	},
	{
		.cmd = "erase",
		.help = "Erase all stored logdata (may take a while..)",
		.function = logdata_erase
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
		.cmd = "memory",
		.help = "get info about memory usage",
		.function = memory_info
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
