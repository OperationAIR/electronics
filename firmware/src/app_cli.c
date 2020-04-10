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
#include "sensors/flow.h"

#include <chip.h>

// profiling
#include <mcu_timing/profile.h>
#include <lpc_tools/irq.h>

#ifndef FIRMWARE_VERSION
    #error "Please define FIRMWARE_VERSION in the Makefile"
#endif


// TODO FIXME: this is for flowsensor test only...
#include "actuators/i2c_dac.h"



static void profile(char *args)
{
    bool irq_state = irq_disable();

    Profile **list;
    int n = profile_get_data(&list);


    log_cli("====    [ Profile ]  [avg]     [max]     [n calls]:");

    for(int i=0;i<n;i++) {
        Profile *p = list[i];
        log_cli("%16s %9u %9u %9u",
                p->label,
                (unsigned int)profile_get_average(p),
                (unsigned int)profile_get_max(p),
                (unsigned int)profile_get_total_call_count(p));
        profile_reset(p);
    }
    irq_restore(irq_state);
}



#define MAX_USB_PACKET_LENGHT 64
char cmd_buf[MAX_USB_PACKET_LENGHT + 1]; // +1 byte for 0 terminator

static void current_time(char *args) {

	char time[20];
	log_get_time_as_str(time);
	log_cli(time);
}

static void test(char *args) {
	app_start_self_test();
}

static void start(char *args) {
	app_program_force_start();
}

static void stop(char *args) {
	app_program_force_stop();
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

static void out_hold(char *args) {
    if (strncmp(args, "on", 2) == 0) {
        app_start_expiratory_hold();
    } else if (strncmp(args, "off", 3) == 0) {
        app_stop_expiratory_hold();
    } else {
        // TODO return current expiratory state
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
    control_MFC_on(flow_SLPM, 0.21);
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

static void exp_PID(char *args) {

	if(!strlen(args)) {
		breathing_print_EXP_PID();
		return;
	}
	log_cli("Setting EXP PID...");

	float pid[3];
	size_t n_params = 0;

	if(!parse_float_csv(&n_params, pid, array_length(pid), args) || (n_params != 3)) {
		log_cli("invalid PID values '%s': expected <P>,<I>,<D>", args);
		return;
	}
	breathing_tune_EXP_PID(pid[0], pid[1], pid[2]);
	log_cli("EXP: PID updated");
}

static void flow_test(char *args) {
    log_cli("Testing flow...");

    // flowsensor_test();
	float flow = read_flow_sensor();

	log_cli("Flow: %d", (int)flow);

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

static void valve_insp(char *args) {
	if (strncmp(args, "open", 2) == 0) {
		control_valve_insp_on(10000);
		log_cli("Inspiration valve opened");
	} else if (strncmp(args, "close", 3) == 0) {
		control_valve_insp_off();
		log_cli("Inspiration valve closed");
	}
}

static void valve_exp(char *args) {
	if (strncmp(args, "open", 2) == 0) {
		control_valve_exp_on(10000);
		log_cli("Expiration valve opened");
	} else if (strncmp(args, "close", 3) == 0) {
		control_valve_exp_off();
		log_cli("Expiration valve closed");
	}
}
static void valve_extra(char *args) {
	if (strncmp(args, "open", 2) == 0) {
		control_extra_on(10000);
		log_cli("Extra valve opened");
	} else if (strncmp(args, "close", 3) == 0) {
		control_extra_off();
		log_cli("Extra valve closed");
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
    log_cli("Pressure in: %d Pa", sensors_read_pressure_insp_pa());
    log_cli("Pressure out: %d Pa", sensors_read_pressure_exp_pa());
    log_cli("Oxygen: %d %%", sensors_read_oxygen_percent());
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
	valve_insp("");
	valve_exp("");
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
		.cmd = "test",
		.help = "start test program",
		.function = test
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
        .cmd = "out",
        .help = "'on' or 'off' Expiratory Hold function [during breathing]",
        .function = out_hold
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
		.cmd = "EXP_PID",
		.help = "Set EXP PID values <P>,<I>,<D>",
		.function = exp_PID
	},
	{
		.cmd = "MFC",
		.help = "Set flowrate in SLPM",
		.function = mfc
	},
	{
		.cmd = "valve_insp",
		.help = "Inpiration valve: 'open' or 'close'",
		.function = valve_insp
	},
	{
		.cmd = "valve_exp",
		.help = "Expiration valve: 'open' or 'close'",
		.function = valve_exp
	},
	{
		.cmd = "valve_extra",
		.help = "Extra valve: 'open' or 'close'",
		.function = valve_extra
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
		.cmd = "profile",
		.help = "get performance profiling info",
		.function = profile
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
