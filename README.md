# Electronics and firmware for Operation Air Ventilator

![OperationAir PCB](img/pcb_v2.jpg)

The electronics for the Operation Air AIROne is comprised of a custom developed PCB with a LPC11U37 microcontroller stacked on top of a Raspberry Pi 4 (Model B).

This repository contains the electronic designs for the PCB and the accompanying firmware.

The Pi talks to the microcontroller over UART using a [custom binary protocol](firmware/README.md#uart-communication-protocol).

Contact info@interay.com for assembled, tested and programmed ready for use boards.


## License

Copyright (c) 2020 TU Delft. All rights reserved.

Licensed under the [Apache 2.0](LICENSE) license.
