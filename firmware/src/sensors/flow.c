#include "flow.h"

#include <stdbool.h>
#include <stdint.h>

#include "i2c.h"

#include "chip.h"

#include <stddef.h>
#include <c_utils/f2strn.h>
#include <log.h>

#include "system_status.h"


static void _flowsensor_boot(void);
static bool _flowsensor_set_sampling_time(void);
static bool _flowsensor_selftest(void);
static float _read_sensor(uint8_t data_reg);
static float _read_temp_celcius(void);



bool flowsensor_enable(void)
{
    // boot sensor in case it is not already booted
    _flowsensor_boot();

    if(!_flowsensor_selftest()) {
        return false;
    }

    if(!_flowsensor_set_sampling_time()) {
        return false;
    }

    return true;
}

float flowsensor_test(void)
{
    const bool ok = flowsensor_enable();
    if(!ok) {
        return 0;
    }

    const float temp_celcius = _read_temp_celcius();
    const float flow = flowsensor_read();

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

float flowsensor_read(void)
{
     return _read_sensor(0x1);
}

static void _flowsensor_boot(void) {
    // The flowsensor may be in 'bootloader mode' after first power-on.
    // This command switches the sensor to 'sensor mode'.
    uint8_t rx[1];
    const uint8_t boot_addr = 0x42;
    const uint8_t boot_reg = 0x45;

    // If this fails, the sensor was probably already in 'sensor mode'.
    i2c_read(boot_addr, boot_reg, rx, sizeof(rx));

    // Ignore I2c errors: device may not have been be in bootloader mode..
    i2c_check_and_clear_error();
}

static bool _flowsensor_set_sampling_time(void) {

    // clear old errors (if any)
    i2c_check_and_clear_error();

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

    i2c_write(xfer.slaveAddr, xfer.txBuff, 3);

    const bool error = (i2c_check_and_clear_error());
    if(error) {
        system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS
                | SYSTEM_STATUS_ERROR_SENSOR_FLOW);
    }

    return (!error);
}

static bool _flowsensor_selftest(void) {

    // clear old errors (if any)
    i2c_check_and_clear_error();

    uint8_t rx[1] = {0};
    const uint8_t sensor_addr = 0x55;
    const uint8_t boot_reg = 0x19;
    i2c_read(sensor_addr, boot_reg, rx, sizeof(rx));

    const bool error = i2c_check_and_clear_error();
    if(error) {
        system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS
                | SYSTEM_STATUS_ERROR_SENSOR_FLOW);
    }

    return ((!error) && (rx[0] == sensor_addr));
}

static float _read_sensor(uint8_t data_reg) {
    const uint8_t sensor_addr = 0x55;

    union {
        float value;
        uint8_t bytes[4];
    } conversion;


    // clear old errors (if any)
    i2c_check_and_clear_error();

    i2c_read(sensor_addr, data_reg, conversion.bytes, sizeof(conversion.bytes));
    if(i2c_check_and_clear_error()) {
        system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS
                | SYSTEM_STATUS_ERROR_SENSOR_FLOW);
        return -1.0;
    }
    return conversion.value;
}

static float _read_temp_celcius(void)
{
     return _read_sensor(0x2);
}

