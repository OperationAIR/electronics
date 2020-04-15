#ifndef OPERATION_AIR_SELF_TEST_H
#define OPERATION_AIR_SELF_TEST_H

#include "settings.h"

enum TestBoundaries {
    begin_wait_time = 3000,             // ms
    minimal_MFC_pres = 2000,            // Pa
    minimal_MFC_wait_time = 5000,       // ms
    minimal_insp_pres = 5000,           // Pa
    minimal_insp_pres_wait_time = 7500, // ms
    minimal_exp_pres = 5000,            // Pa
    minimal_exp_pres_wait_time =7500,   // ms
    maximum_leak_pressure_drop = 1000,  // Pa
    minimal_leak_wait_time = 1000,      // ms
    minimal_exp_valve_pres = 1000,      // Pa
    minimal_exp_valve_wait_time = 2000  // ms
};

enum TestState {
    TestEmptySystem,
//    TestMFCAir = 1 << 0,
//    TestMFCO2 = 1 << 1,
            TestMFCPresSensor = 1 << 2,
    TestInspPresSensor = 1 << 3,
    TestExpPresSensor = 1 << 4,
    TestLeak = 1 << 5,
    TestExpValve = 1 << 6
};

enum TestState test_get_result(void);
void pre_self_test(void);
bool run_self_test(const int dt);



#endif //OPERATION_AIR_SELF_TEST_H
