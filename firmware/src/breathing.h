#ifndef BREATHING_H
#define BREATHING_H

enum TestState {
    TestStateNone,
    TestStateBuildPressure,
    TestStateHold,
    TestStateSuccess,
    TestStateFailed
};

bool breathing_init(void);
void breathing_start_program(void);
void breathing_stop(void);

/**
 * Runs a breathing breathing_start_program
 * This function needs to be called repeatedly durnig breathinging.
 *
 * Returns the current pressure (as int) or 0 if program is finished.
 */
int breathing_run(void);

void breathing_start_test(void);
enum TestState breathing_test(void);
enum TestState breathing_test_get_result(void);

#endif