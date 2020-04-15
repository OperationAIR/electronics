#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"

#include "log.h"
#include "crc/crc.h"


void test_crc(void)
{

    uint8_t buffer[] = {0x00, 0x00, 0x14, 0x00, 0x14, 0x00, 0x02, 0x00, 0x28, 0x00, 0x19, 0x00, 0x2d,
    0x00, 0x05, 0x00, 0x90, 0x01, 0xc8, 0x00, 0x32, 0x00, 0x14, 0x00};
    uint16_t crc_state = 0xFFFF;
    uint16_t res = crc16_usb_stream_check(&crc_state, buffer, sizeof(buffer));

    TEST_ASSERT_EQUAL(0xbe31, res);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_crc);

    UNITY_END();

    return 0;
}
