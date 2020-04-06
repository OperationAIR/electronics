#include "cli.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <mcu_timing/delay.h>
#include <c_utils/array.h>
#include <c_utils/f2strn.h>
#include <startup_lpc11xxx/stacktools.h>

#include "watchdog.h"
#include "cdc_vcom.h"
#include "log.h"
#include "global_settings.h"
#include "app.h"
#include "actuators/control_signals.h"
#include "sensors/sensors.h"
#include "stats.h"
#include "clock.h"
#include "generated/firmware_version.h"
#include "parse_utils.h"
#include "breathing.h"

#include <chip.h>

#ifndef FIRMWARE_VERSION
    #error "Please define FIRMWARE_VERSION in the Makefile"
#endif


// TODO FIXME: this is for flowsensor test only...
#include "actuators/i2c_dac.h"

#define MAX_USB_PACKET_LENGHT 64
char cmd_buf[MAX_USB_PACKET_LENGHT + 1]; // +1 byte for 0 terminator

static void current_time(char *args) {

	char time[20];
	log_get_time_as_str(time);
	log_cli(time);
}

static void start(char *args) {
	app_program_start();
}

static void stop(char *args) {
	app_program_stop();
}

static void in_hold(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		app_start_inspiratory_hold();
	} else if (strncmp(args, "off", 3) == 0) {
		app_stop_inspiratory_hold();
	} else {
		// TODO return current inspiratory state
	}
}

static void dpr(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_DPR_on();
		log_cli("Enable DPR");
	} else if (strncmp(args, "off", 3) == 0) {
		control_DPR_off();
		log_cli("Disable DPR");
    }
}

static void mfc(char *args) {

    float params[3];
    size_t n_params = 0;

    if(!parse_float_csv(&n_params, params, array_length(params), args) || (n_params != 1)) {
        log_cli("invalid flowrate '%s': expected <flow SLPM>", args);
        return;
    }

    float flow_SLPM = params[0];
    control_MFC_set(flow_SLPM, 0.21);
    log_cli("MFC flowrate set to ca '%d'", (int)flow_SLPM);

}

static void dpr_PID(char *args) {

    if(!strlen(args)) {
        breathing_print_DPR_PID();
        return;
    }
    log_cli("Setting DPR PID...");

    float pid[3];
    size_t n_params = 0;

    if(!parse_float_csv(&n_params, pid, array_length(pid), args) || (n_params != 3)) {
        log_cli("invalid PID values '%s': expected <P>,<I>,<D>", args);
        return;
    }
    breathing_tune_DPR_PID(pid[0], pid[1], pid[2]);
    log_cli("DPR: PID updated");
}

static void mfc_PID(char *args) {

    if(!strlen(args)) {
        breathing_print_MFC_PID();
        return;
    }
    log_cli("Setting MFC PID...");

    float pid[3];
    size_t n_params = 0;

    if(!parse_float_csv(&n_params, pid, array_length(pid), args) || (n_params != 3)) {
        log_cli("invalid PID values '%s': expected <P>,<I>,<D>", args);
        return;
    }
    breathing_tune_MFC_PID(pid[0], pid[1], pid[2]);
    log_cli("MFC: PID updated");
}

static void flow_test(char *args) {
    log_cli("Testing flow...");

    flowsensor_test();

}

static void dpr_set(char *args) {
    log_cli("Setting DPR..");

    if(!control_DPR_on()) {
        log_cli("DPR ERR");
    }

    long int setpoint = 0;
    if(!parse_int(args, &setpoint)) {
        log_cli("DPR setpoint '%s' not valid", args);
        return;
    }
    const bool ok = control_DPR_set_pa(setpoint);
    log_cli("DPR setpoint %d %s", setpoint, (ok ? "OK" : "ERR"));
}

static void led_status(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_LED_status_on();
		log_cli("Enable status LED");
	} else if (strncmp(args, "off", 3) == 0) {
		control_LED_status_off();
		log_cli("Disable status LED");
	}
}
static void led_error(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_LED_error_on();
		log_cli("Enable error LED");
	} else if (strncmp(args, "off", 3) == 0) {
		control_LED_error_off();
		log_cli("Disable error LED");
	}
}

static void switch1(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_switch1_on(10000);
		log_cli("Enable switch 1");
	} else if (strncmp(args, "off", 3) == 0) {
		control_switch1_off();
		log_cli("Disable switch 1");
	}
}

static void switch2(char *args) {
	if (strncmp(args, "on", 2) == 0) {
		control_switch2_on();
		log_cli("Enable switch 2");
	} else if (strncmp(args, "off", 3) == 0) {
		control_switch2_off();
		log_cli("Disable switch 2");
	}
}

static void sensors(char *args) {

    char str[32];
    f2strn(sensors_read_flow_out_SCCPM()/1000.0, str, sizeof(str), 3);
    log_cli("Flow out: '%s' SLPM", str);
    f2strn(sensors_read_flow_MFC_O2_SCCPM()/1000.0, str, sizeof(str), 3);
    log_cli("MFC flow O2: '%s' SLPM", str);
    f2strn(sensors_read_flow_MFC_air_SCCPM()/1000.0, str, sizeof(str), 3);
    log_cli("MFC flow air: '%s' SLPM", str);
    log_cli("Pressure MFC: %d Pa", sensors_read_pressure_MFC_pa());
    log_cli("Pressure in: %d Pa", sensors_read_pressure_in_pa());
    log_cli("Pressure out: %d Pa", sensors_read_pressure_out_pa());
}

static void halt(char *args)
{
	app_halt();
	log_cli("Halt application..");
}

static void resume(char *args)
{
	app_resume();
	log_cli("Resume application..");
}

static void app(char *args)
{
	if (app_is_running()) {
		log_cli("app is running in state [%s]", app_get_state());
	} else {
		log_cli("app is halted in state [%s]", app_get_state());
	}
}

static void serial_number(char *args)
{
	char buf[SERIAL_NUM_STR_SIZE];
    log_wtime("serial number:\r\n%s", log_get_serialnumber_str(buf, SERIAL_NUM_STR_SIZE));
}

static void version(char *args)
{
	log_cli("Firmware version:");
	log_cli(FIRMWARE_VERSION);
}


static void status() {
	app("");
    sensors("");
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
	    .cmd = "in",
	    .help = "'on' or 'off' Inspiratory Hold function [during breathing]",
        .function = in_hold
    },
	{
		.cmd = "stop",
		.help = "stop (demo) program",
		.function = stop
	},
	{
		.cmd = "sensors",
		.help = "Show sensor data",
		.function = sensors
	},
	{
		.cmd = "led_status",
		.help = "Control status led: 'on' or 'off'",
		.function = led_status
	},
	{
		.cmd = "led_error",
		.help = "Control error led: 'on' or 'off'",
		.function = led_error
	},
	{
		.cmd = "flow_test",
		.help = "Test flow sensor",
		.function = flow_test
	},
	{
		.cmd = "DPR_set",
		.help = "Set DPR to given setpoint: <int>",
		.function = dpr_set
	},
	{
		.cmd = "DPR_PID",
		.help = "Set DPR PID values <P>,<I>,<D>",
		.function = dpr_PID
	},
	{
		.cmd = "MFC_PID",
		.help = "Set MFC PID values <P>,<I>,<D>",
		.function = mfc_PID
	},
	{
		.cmd = "DPR",
		.help = "Enable/disable DPR: 'on' or 'off'",
		.function = dpr
	},
	{
		.cmd = "MFC",
		.help = "Set flowrate in SLPM",
		.function = mfc
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
