#include "self_test.h"
#include "log.h"

#include "actuators/control_signals.h"
#include "sensors/sensors.h"

static struct {
    enum TestState test_state;

    volatile uint32_t test_cycle_time;

    volatile uint8_t test_result;

    int32_t pressure_insp;
    int32_t pressure_exp;
    int32_t pressure_leak;
} self_test;


/**
Functions needed to perform the system test
*/
enum TestState test_get_result(void)
{
    return self_test.test_state;
}

int32_t _average_pressure(void) {
    self_test.pressure_insp = sensors_read_pressure_insp_pa();
    self_test.pressure_exp = sensors_read_pressure_exp_pa();
    return (self_test.pressure_insp+self_test.pressure_exp) / 2;
}

void pre_self_test(void) {
    self_test.test_cycle_time = 0;
    self_test.test_state = TestEmptySystem;
    self_test.test_result = 0;

    // TODO issue #18: Finish implementation of self-test.
    //
    // Start by holding everything open for X seconds?
    // NOTE: can this be dangerous if a patient is connected?
    control_MFC_off();
    control_valve_insp_on(10000);
    control_valve_exp_on(10000);

    log_wtime("Empty System");
}

bool run_self_test(const int dt)
{
    int32_t pressure_MFC;
    bool ok = false;

    switch (self_test.test_state) {
        case TestEmptySystem:
            if (self_test.test_cycle_time > begin_wait_time) {
                self_test.test_cycle_time = 0;

                log_wtime("Test MFC");
                self_test.test_state = TestMFCPresSensor;
                control_valve_insp_off();
                control_MFC_on(10, 0.21);
            }
            break;
        case TestMFCPresSensor:
            pressure_MFC = sensors_read_pressure_MFC_pa();

            if (pressure_MFC > minimal_MFC_pres) {
                ok = true;
                log_wtime("MFC and pres OK");
                self_test.test_result |= TestMFCPresSensor;
            }

            if (self_test.test_cycle_time > minimal_MFC_wait_time || ok) {
                self_test.test_cycle_time = 0;
                control_MFC_off();

                log_wtime("Test Insp Pres Sensor");
                self_test.test_state = TestInspPresSensor;
                control_valve_exp_off();
                control_valve_insp_on(10000);
                control_MFC_on(10, 0.21);
            }
            break;
        case TestInspPresSensor:
            self_test.pressure_insp = sensors_read_pressure_insp_pa();

            if (self_test.pressure_insp > minimal_insp_pres ) {
                ok = true;
                log_wtime("Pres Insp OK");
                self_test.test_result |= TestInspPresSensor;
            }

            if (self_test.test_cycle_time > minimal_insp_pres_wait_time || ok) {
                self_test.test_cycle_time = 0;

                log_wtime("Test Exp Pres Sensor");
                self_test.test_state = TestExpPresSensor;
            }
            break;
        case TestExpPresSensor:
            self_test.pressure_exp = sensors_read_pressure_exp_pa();

            if (self_test.pressure_exp > minimal_exp_pres) {
                ok = true;
                log_wtime("Pres Exp OK");
                self_test.test_result |= TestExpPresSensor;
            }

            if (self_test.test_cycle_time > minimal_exp_pres_wait_time || ok) {
                self_test.test_cycle_time = 0;
                control_valve_insp_off();
                control_MFC_off();

                log_wtime("Test Leak");
                self_test.test_state = TestLeak;

                self_test.pressure_leak = _average_pressure();
                log_wtime("%d",
                          (int) _average_pressure() );

            }
            break;
        case TestLeak:

            if (self_test.test_cycle_time > minimal_leak_wait_time) {
                self_test.test_cycle_time = 0;

                log_wtime("%d",
                          (int) _average_pressure() );

                self_test.pressure_leak -= _average_pressure();

                if (self_test.pressure_leak < maximum_leak_pressure_drop) {
                    log_wtime("Test Leak OK");
                    self_test.test_result |= TestLeak;
                }

                log_wtime("Exp valve test");
                self_test.test_state = TestExpValve;
                control_valve_exp_on(10000);
            }
            break;
        case TestExpValve:
            if (self_test.test_cycle_time > minimal_exp_valve_wait_time) {
                self_test.test_cycle_time = 0;

                if (_average_pressure() < minimal_exp_valve_pres) {
                    log_wtime("Exp Valve OK");
                    self_test.test_result |= TestExpValve;
                }
                log_wtime("%d", self_test.test_result);
                return false;
            }
            break;
    }
    self_test.test_cycle_time+=dt;
    return true;
}

