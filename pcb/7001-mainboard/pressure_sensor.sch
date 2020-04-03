EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Notes Line
	1250 1100 5700 1100
Text Notes 6050 1600 0    50   ~ 0
Pressure after patient (0-70mbar)
Wire Notes Line
	5900 1100 10350 1100
Text Notes 1400 1600 0    59   ~ 0
Pressure before patient (0-70mbar)
Text Notes 6050 1400 0    118  ~ 24
Pressure sensor 2 (after patient)
Text Notes 1400 1400 0    118  ~ 24
Pressure sensor 1 (before patient)
$Comp
L power:GND #PWR?
U 1 1 5F5C7632
P 2850 2800
AR Path="/5BF41E5D/5F5C7632" Ref="#PWR?"  Part="1" 
AR Path="/5F5C7632" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C7632" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 2850 2550 50  0001 C CNN
F 1 "GND" H 2855 2627 50  0000 C CNN
F 2 "" H 2850 2800 50  0001 C CNN
F 3 "" H 2850 2800 50  0001 C CNN
	1    2850 2800
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C7639
P 2250 2350
AR Path="/5F5C7639" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C7639" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C7639" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C7639" Ref="C5"  Part="1" 
F 0 "C5" H 2365 2396 50  0000 L CNN
F 1 "1nF" H 2365 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2288 2200 50  0001 C CNN
F 3 "~" H 2250 2350 50  0001 C CNN
F 4 "filter (see MPRLS0001PG0000SA datasheet)" H 2250 2350 50  0001 C CNN "purpose"
	1    2250 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 2200 2250 2200
Wire Wire Line
	2450 2300 2450 2500
Wire Wire Line
	2450 2500 2250 2500
NoConn ~ 2600 2800
NoConn ~ 2700 2800
$Comp
L Device:C C?
U 1 1 5F5C7645
P 1700 2000
AR Path="/5F5C7645" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C7645" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C7645" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C7645" Ref="C8"  Part="1" 
F 0 "C8" H 1815 2046 50  0000 L CNN
F 1 "100nF" H 1815 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1738 1850 50  0001 C CNN
F 3 "~" H 1700 2000 50  0001 C CNN
F 4 "decoupling" H 1700 2000 50  0001 C CNN "purpose"
	1    1700 2000
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C764B
P 1700 2150
AR Path="/5BF2E340/5F5C764B" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C764B" Ref="#PWR?"  Part="1" 
AR Path="/5F5C764B" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C764B" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 1700 1900 50  0001 C CNN
F 1 "GND" H 1705 1977 50  0000 C CNN
F 2 "" H 1700 2150 50  0001 C CNN
F 3 "" H 1700 2150 50  0001 C CNN
	1    1700 2150
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F5C7651
P 1500 1850
AR Path="/5F5C7651" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C7651" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 1500 1700 50  0001 C CNN
F 1 "+3.3V" H 1515 2023 50  0000 C CNN
F 2 "" H 1500 1850 50  0001 C CNN
F 3 "" H 1500 1850 50  0001 C CNN
	1    1500 1850
	1    0    0    -1  
$EndComp
Text Label 4250 2000 2    50   ~ 0
PSENSE_1_SPI_~CS~
Wire Wire Line
	3550 2100 4250 2100
Text Label 4250 2100 2    50   ~ 0
PSENSE_SPI_CLK
Wire Wire Line
	3550 2200 4250 2200
Text Label 4250 2200 2    50   ~ 0
PSENSE_SPI_MOSI
Wire Wire Line
	3550 2300 4250 2300
Text Label 4250 2300 2    50   ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	3550 2600 4250 2600
Text Label 4250 2600 2    50   ~ 0
PSENSE_RESET
$Comp
L Jitter_Components:MPRLS0001PG0000SA U?
U 1 1 5F5C7663
P 2850 2500
AR Path="/5F5C7663" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5C7663" Ref="U1"  Part="1" 
F 0 "U1" H 1950 2200 50  0000 C CNN
F 1 "MPRLS0001PG0000SA" H 2300 2100 50  0000 C CNN
F 2 "Jitter_Footprints:MPRLS0001PG0000SA" H 2950 2500 50  0001 C CNN
F 3 "http://www.honeywellscportal.com//index.php?ci_id=138832" H 2950 2500 50  0001 C CNN
F 4 "480-7100-1-ND" H 2850 2500 50  0001 C CNN "Digikey"
F 5 "MPRLS0001PG0000SA" H 2850 2500 50  0001 C CNN "MPN"
	1    2850 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1500 1850 1700 1850
Text HLabel 4500 2000 2    50   Input ~ 0
PSENSE_1_SPI_~CS~
Wire Wire Line
	3550 2000 4500 2000
Text Notes 4550 2300 0    50   ~ 0
SPI bus shared\nbetween sensor 1/2
Wire Bus Line
	4500 2100 4500 2300
Text HLabel 4500 2500 2    50   Output ~ 0
PSENSE_1_DATA_READY
Connection ~ 1700 1850
Wire Wire Line
	3550 2500 4500 2500
Wire Wire Line
	1700 1850 2850 1850
$Comp
L power:GND #PWR?
U 1 1 5F5FFB40
P 7500 2800
AR Path="/5BF41E5D/5F5FFB40" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFB40" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB40" Ref="#PWR0161"  Part="1" 
F 0 "#PWR0161" H 7500 2550 50  0001 C CNN
F 1 "GND" H 7505 2627 50  0000 C CNN
F 2 "" H 7500 2800 50  0001 C CNN
F 3 "" H 7500 2800 50  0001 C CNN
	1    7500 2800
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5FFB47
P 6900 2350
AR Path="/5F5FFB47" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFB47" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB47" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFB47" Ref="C6"  Part="1" 
F 0 "C6" H 7015 2396 50  0000 L CNN
F 1 "1nF" H 7015 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6938 2200 50  0001 C CNN
F 3 "~" H 6900 2350 50  0001 C CNN
F 4 "filter (see MPRLS0001PG0000SA datasheet)" H 6900 2350 50  0001 C CNN "purpose"
	1    6900 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 2200 6900 2200
Wire Wire Line
	7100 2300 7100 2500
Wire Wire Line
	7100 2500 6900 2500
NoConn ~ 7250 2800
NoConn ~ 7350 2800
$Comp
L Device:C C?
U 1 1 5F5FFB53
P 6350 2000
AR Path="/5F5FFB53" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFB53" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB53" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFB53" Ref="C9"  Part="1" 
F 0 "C9" H 6465 2046 50  0000 L CNN
F 1 "100nF" H 6465 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6388 1850 50  0001 C CNN
F 3 "~" H 6350 2000 50  0001 C CNN
F 4 "decoupling" H 6350 2000 50  0001 C CNN "purpose"
	1    6350 2000
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5FFB59
P 6350 2150
AR Path="/5BF2E340/5F5FFB59" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB59" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFB59" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB59" Ref="#PWR0162"  Part="1" 
F 0 "#PWR0162" H 6350 1900 50  0001 C CNN
F 1 "GND" H 6355 1977 50  0000 C CNN
F 2 "" H 6350 2150 50  0001 C CNN
F 3 "" H 6350 2150 50  0001 C CNN
	1    6350 2150
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F5FFB5F
P 6150 1850
AR Path="/5F5FFB5F" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB5F" Ref="#PWR0163"  Part="1" 
F 0 "#PWR0163" H 6150 1700 50  0001 C CNN
F 1 "+3.3V" H 6165 2023 50  0000 C CNN
F 2 "" H 6150 1850 50  0001 C CNN
F 3 "" H 6150 1850 50  0001 C CNN
	1    6150 1850
	1    0    0    -1  
$EndComp
Text Label 8900 2000 2    50   ~ 0
PSENSE_2_SPI_~CS~
Text Label 8900 2100 2    50   ~ 0
PSENSE_SPI_CLK
Text Label 8900 2200 2    50   ~ 0
PSENSE_SPI_MOSI
Text Label 8900 2300 2    50   ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	8200 2600 8900 2600
Text Label 8900 2600 2    50   ~ 0
PSENSE_RESET
$Comp
L Jitter_Components:MPRLS0001PG0000SA U?
U 1 1 5F5FFB71
P 7500 2500
AR Path="/5F5FFB71" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5FFB71" Ref="U8"  Part="1" 
F 0 "U8" H 6600 2200 50  0000 C CNN
F 1 "MPRLS0001PG0000SA" H 6950 2100 50  0000 C CNN
F 2 "Jitter_Footprints:MPRLS0001PG0000SA" H 7600 2500 50  0001 C CNN
F 3 "https://sensing.honeywell.com/honeywell-sensing-micropressure-board-mount-pressure-mpr-series-datasheet-32332628.pdf" H 7600 2500 50  0001 C CNN
F 4 "MPRLS0001PG0000SA" H 7500 2500 50  0001 C CNN "MPN"
F 5 "480-7100-1-ND" H 7500 2500 50  0001 C CNN "Digikey"
	1    7500 2500
	-1   0    0    -1  
$EndComp
Text HLabel 9150 2500 2    50   Output ~ 0
PSENSE_2_DATA_READY
Text HLabel 9150 2000 2    50   Input ~ 0
PSENSE_2_SPI_~CS~
Wire Wire Line
	8200 2000 9150 2000
Text HLabel 9150 2100 2    50   Input ~ 0
PSENSE_SPI_CLK
Text HLabel 9150 2200 2    50   Input ~ 0
PSENSE_SPI_MOSI
Text HLabel 9150 2300 2    50   Output ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	8200 2100 9150 2100
Wire Wire Line
	8200 2200 9150 2200
Wire Wire Line
	8200 2300 9150 2300
Text Label 8350 1800 0    50   ~ 0
PSENSE_RESET
Text HLabel 9150 1800 2    50   Input ~ 0
PSENSE_RESET
Wire Wire Line
	8350 1800 9150 1800
Wire Wire Line
	8200 2500 9150 2500
Connection ~ 6350 1850
Wire Wire Line
	6350 1850 7500 1850
Wire Wire Line
	6150 1850 6350 1850
Wire Notes Line
	5700 1100 5700 3150
Wire Notes Line
	5700 3150 1250 3150
Wire Notes Line
	1250 3150 1250 1100
Wire Notes Line
	5900 1100 5900 3150
Wire Notes Line
	5900 3150 10350 3150
Wire Notes Line
	10350 1100 10350 3150
Wire Notes Line
	1250 3350 5700 3350
Text Notes 1400 3650 0    118  ~ 24
Pressure sensor 3 (weaning)
Text Notes 1400 3850 0    59   ~ 0
Pressure close to patient (0-70mbar)
$Comp
L power:GND #PWR?
U 1 1 5F5C75CF
P 1650 4400
AR Path="/5BF2E340/5F5C75CF" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C75CF" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75CF" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75CF" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 1650 4150 50  0001 C CNN
F 1 "GND" H 1655 4227 50  0000 C CNN
F 2 "" H 1650 4400 50  0001 C CNN
F 3 "" H 1650 4400 50  0001 C CNN
	1    1650 4400
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C75D6
P 1650 4250
AR Path="/5F5C75D6" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C75D6" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C75D6" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C75D6" Ref="C30"  Part="1" 
F 0 "C30" H 1765 4296 50  0000 L CNN
F 1 "1uF" H 1765 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1688 4100 50  0001 C CNN
F 3 "~" H 1650 4250 50  0001 C CNN
F 4 "decoupling" H 1650 4250 50  0001 C CNN "purpose"
	1    1650 4250
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C75DD
P 2150 4250
AR Path="/5F5C75DD" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C75DD" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C75DD" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C75DD" Ref="C31"  Part="1" 
F 0 "C31" H 2265 4296 50  0000 L CNN
F 1 "100nF" H 2265 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2188 4100 50  0001 C CNN
F 3 "~" H 2150 4250 50  0001 C CNN
F 4 "decoupling" H 2150 4250 50  0001 C CNN "purpose"
	1    2150 4250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C75E3
P 2150 4400
AR Path="/5BF2E340/5F5C75E3" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C75E3" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75E3" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75E3" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 2150 4150 50  0001 C CNN
F 1 "GND" H 2155 4227 50  0000 C CNN
F 2 "" H 2150 4400 50  0001 C CNN
F 3 "" H 2150 4400 50  0001 C CNN
	1    2150 4400
	-1   0    0    -1  
$EndComp
Connection ~ 1650 4100
Wire Wire Line
	1650 4100 2150 4100
$Comp
L power:+5V #PWR?
U 1 1 5F5C761D
P 1500 4100
AR Path="/5BF41E5D/5F5C761D" Ref="#PWR?"  Part="1" 
AR Path="/5F5C761D" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C761D" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 1500 3950 50  0001 C CNN
F 1 "+5V" H 1515 4273 50  0000 C CNN
F 2 "" H 1500 4100 50  0001 C CNN
F 3 "" H 1500 4100 50  0001 C CNN
	1    1500 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4100 1650 4100
Connection ~ 3350 4500
Wire Wire Line
	3350 4500 3350 4850
Wire Wire Line
	3350 4500 4000 4500
Wire Wire Line
	4000 4850 4400 4850
Wire Wire Line
	2950 4100 2950 4200
Connection ~ 4000 4850
Text Notes 4500 5300 0    50   ~ 0
Place close to\nADC input
$Comp
L Device:C C?
U 1 1 5F5C7616
P 4400 5000
AR Path="/5F5C7616" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C7616" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C7616" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C7616" Ref="C35"  Part="1" 
F 0 "C35" H 4150 5000 50  0000 L CNN
F 1 "2.2nF" H 4150 4900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4438 4850 50  0001 C CNN
F 3 "~" H 4400 5000 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 4400 5000 50  0001 C CNN "purpose"
	1    4400 5000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C760F
P 4400 5150
AR Path="/5BF2E340/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C760F" Ref="#PWR0157"  Part="1" 
F 0 "#PWR0157" H 4400 4900 50  0001 C CNN
F 1 "GND" H 4405 4977 50  0000 C CNN
F 2 "" H 4400 5150 50  0001 C CNN
F 3 "" H 4400 5150 50  0001 C CNN
	1    4400 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F5C7609
P 4000 4650
AR Path="/5BF41E62/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5F5C7609" Ref="R1"  Part="1" 
F 0 "R1" V 3793 4650 50  0000 C CNN
F 1 "68k" V 3884 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3930 4650 50  0001 C CNN
F 3 "~" H 4000 4650 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 4000 4650 50  0001 C CNN "purpose"
	1    4000 4650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C7602
P 4000 5150
AR Path="/5BF2E340/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C7602" Ref="#PWR0158"  Part="1" 
F 0 "#PWR0158" H 4000 4900 50  0001 C CNN
F 1 "GND" H 4005 4977 50  0000 C CNN
F 2 "" H 4000 5150 50  0001 C CNN
F 3 "" H 4000 5150 50  0001 C CNN
	1    4000 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4800 4000 4850
$Comp
L Device:R R?
U 1 1 5F5C75FB
P 4000 5000
AR Path="/5BF41E62/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5F5C75FB" Ref="R20"  Part="1" 
F 0 "R20" V 3793 5000 50  0000 C CNN
F 1 "100k" V 3884 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3930 5000 50  0001 C CNN
F 3 "~" H 4000 5000 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 4000 5000 50  0001 C CNN "purpose"
	1    4000 5000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C75F3
P 3350 5150
AR Path="/5BF2E340/5F5C75F3" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C75F3" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75F3" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75F3" Ref="#PWR0159"  Part="1" 
F 0 "#PWR0159" H 3350 4900 50  0001 C CNN
F 1 "GND" H 3355 4977 50  0000 C CNN
F 2 "" H 3350 5150 50  0001 C CNN
F 3 "" H 3350 5150 50  0001 C CNN
	1    3350 5150
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C75ED
P 3350 5000
AR Path="/5F5C75ED" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C75ED" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C75ED" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C75ED" Ref="C34"  Part="1" 
F 0 "C34" H 3500 4950 50  0000 L CNN
F 1 "470pF" H 3400 4850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3388 4850 50  0001 C CNN
F 3 "~" H 3350 5000 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 3350 5000 50  0001 C CNN "purpose"
	1    3350 5000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C75C9
P 2950 4800
AR Path="/5BF41E5D/5F5C75C9" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75C9" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75C9" Ref="#PWR0160"  Part="1" 
F 0 "#PWR0160" H 2950 4550 50  0001 C CNN
F 1 "GND" H 2955 4627 50  0000 C CNN
F 2 "" H 2950 4800 50  0001 C CNN
F 3 "" H 2950 4800 50  0001 C CNN
	1    2950 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4100 2950 4100
Connection ~ 2150 4100
Wire Notes Line
	5700 3350 5700 5500
Wire Notes Line
	5700 5500 1250 5500
Wire Notes Line
	1250 3350 1250 5500
Connection ~ 4400 4850
Text HLabel 4900 4850 2    50   Output ~ 0
A_PSENSE_3
$Comp
L Connector:TestPoint TP?
U 1 1 5F5C762B
P 4600 4850
AR Path="/5BF2E340/5F5C762B" Ref="TP?"  Part="1" 
AR Path="/5C00B45C/5F5C762B" Ref="TP?"  Part="1" 
AR Path="/5F5C762B" Ref="TP?"  Part="1" 
AR Path="/5F5B6035/5F5C762B" Ref="TP2"  Part="1" 
F 0 "TP2" H 4650 5000 50  0000 L CNN
F 1 "DNI" H 4650 5000 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 4800 4850 50  0001 C CNN
F 3 "~" H 4800 4850 50  0001 C CNN
	1    4600 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4850 4900 4850
Connection ~ 4600 4850
Wire Wire Line
	4400 4850 4600 4850
Text Notes 5450 4600 2    59   ~ 0
5V to 3V divider +\nRC filter: Fc = 1.8Khz\n
Wire Notes Line
	5900 3350 10350 3350
Text Notes 6050 3950 0    59   ~ 0
Pressure vessel between MFC\nand pressure regulator (0.5-1 bar)
$Comp
L power:GND #PWR?
U 1 1 6087D424
P 6300 4500
AR Path="/5BF2E340/6087D424" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/6087D424" Ref="#PWR?"  Part="1" 
AR Path="/6087D424" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/6087D424" Ref="#PWR0164"  Part="1" 
F 0 "#PWR0164" H 6300 4250 50  0001 C CNN
F 1 "GND" H 6305 4327 50  0000 C CNN
F 2 "" H 6300 4500 50  0001 C CNN
F 3 "" H 6300 4500 50  0001 C CNN
	1    6300 4500
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6087D42B
P 6300 4350
AR Path="/6087D42B" Ref="C?"  Part="1" 
AR Path="/5BF2E340/6087D42B" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/6087D42B" Ref="C?"  Part="1" 
AR Path="/5F5B6035/6087D42B" Ref="C32"  Part="1" 
F 0 "C32" H 6415 4396 50  0000 L CNN
F 1 "1uF" H 6415 4305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6338 4200 50  0001 C CNN
F 3 "~" H 6300 4350 50  0001 C CNN
F 4 "decoupling" H 6300 4350 50  0001 C CNN "purpose"
	1    6300 4350
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6087D432
P 6800 4350
AR Path="/6087D432" Ref="C?"  Part="1" 
AR Path="/5BF2E340/6087D432" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/6087D432" Ref="C?"  Part="1" 
AR Path="/5F5B6035/6087D432" Ref="C33"  Part="1" 
F 0 "C33" H 6915 4396 50  0000 L CNN
F 1 "100nF" H 6915 4305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6838 4200 50  0001 C CNN
F 3 "~" H 6800 4350 50  0001 C CNN
F 4 "decoupling" H 6800 4350 50  0001 C CNN "purpose"
	1    6800 4350
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6087D438
P 6800 4500
AR Path="/5BF2E340/6087D438" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/6087D438" Ref="#PWR?"  Part="1" 
AR Path="/6087D438" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/6087D438" Ref="#PWR0165"  Part="1" 
F 0 "#PWR0165" H 6800 4250 50  0001 C CNN
F 1 "GND" H 6805 4327 50  0000 C CNN
F 2 "" H 6800 4500 50  0001 C CNN
F 3 "" H 6800 4500 50  0001 C CNN
	1    6800 4500
	-1   0    0    -1  
$EndComp
Connection ~ 6300 4200
Wire Wire Line
	6300 4200 6800 4200
$Comp
L power:+5V #PWR?
U 1 1 6087D440
P 6150 4200
AR Path="/5BF41E5D/6087D440" Ref="#PWR?"  Part="1" 
AR Path="/6087D440" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/6087D440" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 6150 4050 50  0001 C CNN
F 1 "+5V" H 6165 4373 50  0000 C CNN
F 2 "" H 6150 4200 50  0001 C CNN
F 3 "" H 6150 4200 50  0001 C CNN
	1    6150 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4200 6300 4200
Wire Wire Line
	8650 4850 9050 4850
$Comp
L Connector:TestPoint TP?
U 1 1 6087D44B
P 9250 4850
AR Path="/5BF2E340/6087D44B" Ref="TP?"  Part="1" 
AR Path="/5C00B45C/6087D44B" Ref="TP?"  Part="1" 
AR Path="/6087D44B" Ref="TP?"  Part="1" 
AR Path="/5F5B6035/6087D44B" Ref="TP3"  Part="1" 
F 0 "TP3" H 9300 5000 50  0000 L CNN
F 1 "DNI" H 9300 5000 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 9450 4850 50  0001 C CNN
F 3 "~" H 9450 4850 50  0001 C CNN
	1    9250 4850
	1    0    0    -1  
$EndComp
Connection ~ 8650 4850
Text Notes 9150 5300 0    50   ~ 0
Place close to\nADC input
$Comp
L Device:C C?
U 1 1 6087D455
P 9050 5000
AR Path="/6087D455" Ref="C?"  Part="1" 
AR Path="/5BF2E340/6087D455" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/6087D455" Ref="C?"  Part="1" 
AR Path="/5F5B6035/6087D455" Ref="C37"  Part="1" 
F 0 "C37" H 8800 5000 50  0000 L CNN
F 1 "2.2nF" H 8800 4900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9088 4850 50  0001 C CNN
F 3 "~" H 9050 5000 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 9050 5000 50  0001 C CNN "purpose"
	1    9050 5000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6087D45B
P 9050 5150
AR Path="/5BF2E340/6087D45B" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/6087D45B" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/6087D45B" Ref="#PWR?"  Part="1" 
AR Path="/6087D45B" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/6087D45B" Ref="#PWR0167"  Part="1" 
F 0 "#PWR0167" H 9050 4900 50  0001 C CNN
F 1 "GND" H 9055 4977 50  0000 C CNN
F 2 "" H 9050 5150 50  0001 C CNN
F 3 "" H 9050 5150 50  0001 C CNN
	1    9050 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6087D462
P 8650 4650
AR Path="/5BF41E62/6087D462" Ref="R?"  Part="1" 
AR Path="/5BF2E340/6087D462" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/6087D462" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/6087D462" Ref="R?"  Part="1" 
AR Path="/6087D462" Ref="R?"  Part="1" 
AR Path="/5F5B6035/6087D462" Ref="R2"  Part="1" 
F 0 "R2" V 8443 4650 50  0000 C CNN
F 1 "68k" V 8534 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8580 4650 50  0001 C CNN
F 3 "~" H 8650 4650 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 8650 4650 50  0001 C CNN "purpose"
	1    8650 4650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6087D468
P 8650 5150
AR Path="/5BF2E340/6087D468" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/6087D468" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/6087D468" Ref="#PWR?"  Part="1" 
AR Path="/6087D468" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/6087D468" Ref="#PWR0168"  Part="1" 
F 0 "#PWR0168" H 8650 4900 50  0001 C CNN
F 1 "GND" H 8655 4977 50  0000 C CNN
F 2 "" H 8650 5150 50  0001 C CNN
F 3 "" H 8650 5150 50  0001 C CNN
	1    8650 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 4800 8650 4850
$Comp
L Device:R R?
U 1 1 6087D470
P 8650 5000
AR Path="/5BF41E62/6087D470" Ref="R?"  Part="1" 
AR Path="/5BF2E340/6087D470" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/6087D470" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/6087D470" Ref="R?"  Part="1" 
AR Path="/6087D470" Ref="R?"  Part="1" 
AR Path="/5F5B6035/6087D470" Ref="R13"  Part="1" 
F 0 "R13" V 8443 5000 50  0000 C CNN
F 1 "100k" V 8534 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8580 5000 50  0001 C CNN
F 3 "~" H 8650 5000 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 8650 5000 50  0001 C CNN "purpose"
	1    8650 5000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6087D477
P 8150 5000
AR Path="/5BF2E340/6087D477" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/6087D477" Ref="#PWR?"  Part="1" 
AR Path="/6087D477" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/6087D477" Ref="#PWR0169"  Part="1" 
F 0 "#PWR0169" H 8150 4750 50  0001 C CNN
F 1 "GND" H 8155 4827 50  0000 C CNN
F 2 "" H 8150 5000 50  0001 C CNN
F 3 "" H 8150 5000 50  0001 C CNN
	1    8150 5000
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6087D47E
P 8150 4850
AR Path="/6087D47E" Ref="C?"  Part="1" 
AR Path="/5BF2E340/6087D47E" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/6087D47E" Ref="C?"  Part="1" 
AR Path="/5F5B6035/6087D47E" Ref="C36"  Part="1" 
F 0 "C36" H 8300 4800 50  0000 L CNN
F 1 "1nF" H 8200 4700 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8188 4700 50  0001 C CNN
F 3 "~" H 8150 4850 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 8150 4850 50  0001 C CNN "purpose"
	1    8150 4850
	-1   0    0    -1  
$EndComp
Wire Notes Line
	10350 3350 10350 5500
Wire Notes Line
	10350 5500 5900 5500
Wire Notes Line
	5900 3350 5900 5500
Text Notes 10100 4600 2    59   ~ 0
5V to 3V divider +\nRC filter: Fc = 1.8Khz\n
Text HLabel 9550 4850 2    50   Output ~ 0
A_MFC_PRESSURE
Connection ~ 9050 4850
Connection ~ 9250 4850
Wire Wire Line
	9250 4850 9550 4850
Wire Wire Line
	9050 4850 9250 4850
Text Notes 6050 3650 0    118  ~ 24
Pressure sensor 4 (MFC output)
Text Label 4000 4500 2    50   ~ 0
MPVZ5010_OUT
$Comp
L Sensor_Pressure:MPXH6115A U?
U 1 1 5F5C75C3
P 2950 4500
AR Path="/5BF41E5D/5F5C75C3" Ref="U?"  Part="1" 
AR Path="/5F5C75C3" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5C75C3" Ref="U11"  Part="1" 
F 0 "U11" H 3150 4850 50  0000 R CNN
F 1 "MPVZ5010GW6U" H 3600 4750 50  0000 R CNN
F 2 "Jitter_Footprints:MPVZ5010GW6U" H 2450 4150 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/302/MPVZ5010G-1127149.pdf" H 2950 5100 50  0001 C CNN
F 4 "MPVZ5010GW6U" H 2950 4500 50  0001 C CNN "MPN"
	1    2950 4500
	1    0    0    -1  
$EndComp
$Comp
L Jitter_Components:ABPDXXX000XXAX5 U9
U 1 1 608AD171
P 7450 4600
F 0 "U9" H 7650 5050 50  0000 R CNN
F 1 "ABPDXXX000XXAX5" H 8250 4950 50  0001 R CNN
F 2 "Jitter_Footprints:ABPDXXX000XX0XX" H 7650 4500 50  0001 C CNN
F 3 "https://sensing.honeywell.com/honeywell-sensing-basic-board-mount-pressure-abp-series-datasheet-32305128.pdf" H 7550 4600 50  0001 C CNN
F 4 "analog" H 7200 4350 50  0001 R CNN "Interface"
F 5 "ABPDANT015PGAA5" H 7900 4950 50  0000 C CNN "MPN"
F 6 " 480-6253-ND" H 7450 4600 50  0001 C CNN "Digikey"
	1    7450 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 608B02BC
P 7450 4900
AR Path="/5BF2E340/608B02BC" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/608B02BC" Ref="#PWR?"  Part="1" 
AR Path="/608B02BC" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/608B02BC" Ref="#PWR0170"  Part="1" 
F 0 "#PWR0170" H 7450 4650 50  0001 C CNN
F 1 "GND" H 7455 4727 50  0000 C CNN
F 2 "" H 7450 4900 50  0001 C CNN
F 3 "" H 7450 4900 50  0001 C CNN
	1    7450 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6800 4200 7450 4200
Connection ~ 6800 4200
NoConn ~ 7750 4900
NoConn ~ 7650 4900
NoConn ~ 7550 4900
Wire Wire Line
	7950 4500 8150 4500
Wire Wire Line
	8150 4700 8150 4500
Connection ~ 8150 4500
Wire Wire Line
	8150 4500 8650 4500
$EndSCHEMATC
