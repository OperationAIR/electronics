# Operation Air embedded firmware

Requirements

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
