#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"

#include "log.h"
#include "sensors/flow.h"


void test_flow_interpolation(void)
{
    // values <= 0 flow
    TEST_ASSERT_EQUAL(0, flow_interpolate_sccm(INT_MIN));
    TEST_ASSERT_EQUAL(0, flow_interpolate_sccm(-1));
    TEST_ASSERT_EQUAL(0, flow_interpolate_sccm(0));
    TEST_ASSERT_EQUAL(0, flow_interpolate_sccm(1000));

    // test interpolation: see AWM720P1 table in datasheet
    TEST_ASSERT_EQUAL(12563, flow_interpolate_sccm(2000));
    TEST_ASSERT_EQUAL(25000, flow_interpolate_sccm(2990));
    TEST_ASSERT_EQUAL(150000, flow_interpolate_sccm(4860));
    TEST_ASSERT_EQUAL(200000, flow_interpolate_sccm(5000));

    // extreme values: should not go beyond end of lookup table
    TEST_ASSERT_EQUAL(200000, flow_interpolate_sccm(5001));
    TEST_ASSERT_EQUAL(200000, flow_interpolate_sccm(10000));
    TEST_ASSERT_EQUAL(200000, flow_interpolate_sccm(INT_MAX));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_flow_interpolation);

    UNITY_END();

    return 0;
}
