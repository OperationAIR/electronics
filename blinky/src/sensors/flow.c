#include "flow.h"

#include <stdbool.h>
#include <stdint.h>

#include "i2c.h"

#include "chip.h"

#include <stddef.h>
#include <c_utils/f2strn.h>
#include <log.h>


static void _flowsensor_boot(void);
static void _flowsensor_set_sampling_time(void);
static bool _flowsensor_selftest(void);
static float _read_sensor(uint8_t data_reg);
static float _read_flow(void);
static float _read_temp_celcius(void);



bool flowsensor_enable(void)
{
    // boot sensor in case it is not already booted
    _flowsensor_boot();

    if(!_flowsensor_selftest()) {
        return false;
    }

    _flowsensor_set_sampling_time();

    return true;
}

float flowsensor_test(void)
{
    const bool ok = flowsensor_enable();
    if(!ok) {
        return 0;
    }

    const float temp_celcius = _read_temp_celcius();
    const float flow = _read_flow();

    char temp_str[32];
    f2strn(temp_celcius, temp_str, sizeof(temp_str), 3);

    char flow_str[32];
    f2strn(flow, flow_str, sizeof(flow_str), 3);
//
   log_debug("Flowsensor: temp='%s' C, flow='%s'",
           temp_str,
           flow_str);
    return flow;
}

float read_flow_sensor(void) {
//    const bool ok = flowsensor_enable();
//    if(!ok) {
//        return 0.f;
//    }
    const float flow = _read_flow();

    return flow;
}

static void _flowsensor_boot(void) {
    // The flowsensor may be in 'bootloader mode' after first power-on.
    // This command switches the sensor to 'sensor mode'.
    uint8_t rx[1];
    const uint8_t boot_addr = 0x42;
    const uint8_t boot_reg = 0x45;
    // If this fails, the sensor was probably already in 'sensor mode'.

    Chip_I2C_MasterCmdRead(DEFAULT_I2C, boot_addr, boot_reg, rx, sizeof(rx));
}

static void _flowsensor_set_sampling_time(void) {
    // set the sampling time of the flowsensor in ms
    int sampling_time = 10;

    I2C_XFER_T xfer;

    // Transfer buffer
    uint8_t tx[3];

    xfer.slaveAddr = 0x55;
    tx[0] = 0x55; // set number of samples averaged
    tx[1] = (uint8_t) (sampling_time & 0xFF);           // lower part
    tx[2] = (uint8_t) ((sampling_time >> 8) & 0xFF);    // higher part

    xfer.txBuff = &tx[0];

    /* Send data */
    Chip_I2C_MasterSend(DEFAULT_I2C, xfer.slaveAddr, xfer.txBuff, 3);
}

static bool _flowsensor_selftest(void) {
    uint8_t rx[1] = {0};
    const uint8_t sensor_addr = 0x55;
    const uint8_t boot_reg = 0x19;
    size_t bytes_received = Chip_I2C_MasterCmdRead(DEFAULT_I2C, sensor_addr, boot_reg, rx, sizeof(rx));

    return ((bytes_received == 1) && (rx[0] == sensor_addr));
}

static float _read_sensor(uint8_t data_reg) {
    const uint8_t sensor_addr = 0x55;

    union {
        float value;
        uint8_t bytes[4];
    } conversion;

    size_t result = Chip_I2C_MasterCmdRead(DEFAULT_I2C, sensor_addr, data_reg,
            conversion.bytes, sizeof(conversion.bytes));
    if(result != sizeof(conversion.bytes)) {
        return 0.0;
    }
    return conversion.value;
}

static float _read_flow(void)
{
     return _read_sensor(0x1);
}
static float _read_temp_celcius(void)
{
     return _read_sensor(0x2);
}

