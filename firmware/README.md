# Operation Air embedded firmware

The firmware runs on a LPC11U37 microcontroller.

## Requirements

* [Gnu Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
* CMake
* JTAG/SWD programmer, such as the [Black Magic Probe](https://github.com/blacksphere/blackmagic/wiki) (BMP) , or any OpenOCD compatible device.


## Build

First we need to create a `config.cmake` file in which we can configure our build

```console
cp config.cmake.example config.cmake
```

In `config.cmake` we can configure the BMP if we're using any. On MacOS that would look like:

```
set(BLACKMAGIC_DEV /dev/cu.usbmodemC1DDCDF81)
```

Next we need to create a `build` directory in the project root and run CMake to fetch all dedpendencies and create the makefiles.

```console
mkdir build
cd build
cmake ..
```

The previous part only needs to be done the first time.
Now we're ready to actually compile the project. Inside the `build` directory run

```console
make
```

And to flash

```console
make flash
```


## UART Communication Protocol

The microcontroller communicates with a Raspberry Pi over `uart`. The PCB is designed as a Raspberry Pi Hat and uses the `TXD` and `RXD` pins in the Raspberry Pi header. Note that `Rx` and `Tx` are swapped on the microcontroller side.

![](img/uart_pinout.png)

A binary protocol is used where each command is a unique 4 byte sequence followed by an optional payload.

### Command Overview

| Command             | Description                             | Prefix     | Payload  | Response         |
| -------------       |---------------------------------------- | ---------: | -------  | --------         |
| LedOn               | Turn on status LED (Green)              | 0x55556666 | None     | Log info (ascii) |
| LedOff              | Turn off status LED (Green)             | 0x66667777 | None     | Log info (ascii) |
| NewSettings         | Send and apply new operation settings   | 0x41424344 | Settings | Applied Settings |
| RequestSensorValues | Request current samples for all sensors | 0x22226666 | None     | Sensor Values    |


### Settings

Settings is defined as a struct where each entry is a 16 bit unsigned integer.

```
typedef struct __attribute__((packed)) {
    uint16_t start; // breathing is started
    uint16_t peep; // exhale pressure
    uint16_t frequency; // breathing cycles per minute
    uint16_t ratio; // ratio between inhale exhale
    uint16_t pressure; // inhale pressure
    uint16_t oxygen; // oxygen percentage for mixer
    uint16_t max_pressure_alarm;
    uint16_t min_pressure_alarm;
    uint16_t max_TV_alarm;
    uint16_t min_TV_alarm;
    uint16_t max_fiO2_alarm;
    uint16_t min_fiO2_alarm;
    uint16_t crc;
} OperationSettings;
```

The final entry is a `crc16 usb` checksum with the following specs:

```
CRC16 USB
Poly: 0x8005
Init: 0xFFFF
RefIn: True
RefOut: True
XorOut: 0xFFFF
```


### Sensor Values

//TODO
