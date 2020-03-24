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
Text Notes 1400 1400 0    118  ~ 24
Pressure sensor 1
$Comp
L power:GND #PWR?
U 1 1 5F5C7632
P 3050 2800
AR Path="/5BF41E5D/5F5C7632" Ref="#PWR?"  Part="1" 
AR Path="/5F5C7632" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C7632" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 3050 2550 50  0001 C CNN
F 1 "GND" H 3055 2627 50  0000 C CNN
F 2 "" H 3050 2800 50  0001 C CNN
F 3 "" H 3050 2800 50  0001 C CNN
	1    3050 2800
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C7639
P 2450 2350
AR Path="/5F5C7639" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C7639" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C7639" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C7639" Ref="C5"  Part="1" 
F 0 "C5" H 2565 2396 50  0000 L CNN
F 1 "1nF" H 2565 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2488 2200 50  0001 C CNN
F 3 "~" H 2450 2350 50  0001 C CNN
F 4 "filter (see MPRLS0001PG0000SA datasheet)" H 2450 2350 50  0001 C CNN "purpose"
	1    2450 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2650 2200 2450 2200
Wire Wire Line
	2650 2300 2650 2500
Wire Wire Line
	2650 2500 2450 2500
NoConn ~ 2800 2800
NoConn ~ 2900 2800
$Comp
L Device:C C?
U 1 1 5F5C7645
P 1600 2900
AR Path="/5F5C7645" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C7645" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C7645" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C7645" Ref="C8"  Part="1" 
F 0 "C8" H 1715 2946 50  0000 L CNN
F 1 "100nF" H 1715 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1638 2750 50  0001 C CNN
F 3 "~" H 1600 2900 50  0001 C CNN
F 4 "decoupling" H 1600 2900 50  0001 C CNN "purpose"
	1    1600 2900
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C764B
P 1600 3050
AR Path="/5BF2E340/5F5C764B" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C764B" Ref="#PWR?"  Part="1" 
AR Path="/5F5C764B" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C764B" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 1600 2800 50  0001 C CNN
F 1 "GND" H 1605 2877 50  0000 C CNN
F 2 "" H 1600 3050 50  0001 C CNN
F 3 "" H 1600 3050 50  0001 C CNN
	1    1600 3050
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F5C7651
P 1400 2750
AR Path="/5F5C7651" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C7651" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 1400 2600 50  0001 C CNN
F 1 "+3.3V" H 1415 2923 50  0000 C CNN
F 2 "" H 1400 2750 50  0001 C CNN
F 3 "" H 1400 2750 50  0001 C CNN
	1    1400 2750
	1    0    0    -1  
$EndComp
Text Label 4450 2000 2    50   ~ 0
PSENSE_1_SPI_~CS~
Wire Wire Line
	3750 2100 4450 2100
Text Label 4450 2100 2    50   ~ 0
PSENSE_SPI_CLK
Wire Wire Line
	3750 2200 4450 2200
Text Label 4450 2200 2    50   ~ 0
PSENSE_SPI_MOSI
Wire Wire Line
	3750 2300 4450 2300
Text Label 4450 2300 2    50   ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	3750 2500 4600 2500
Wire Wire Line
	3750 2600 4450 2600
Text Label 4450 2600 2    50   ~ 0
PSENSE_RESET
$Comp
L Jitter_Components:MPRLS0001PG0000SA U?
U 1 1 5F5C7663
P 3050 2500
AR Path="/5F5C7663" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5C7663" Ref="U1"  Part="1" 
F 0 "U1" H 2150 2200 50  0000 C CNN
F 1 "MPRLS0001PG0000SA" H 2500 2100 50  0000 C CNN
F 2 "Jitter_Footprints:MPRLS0001PG0000SA" H 3150 2500 50  0001 C CNN
F 3 "http://www.honeywellscportal.com//index.php?ci_id=138832" H 3150 2500 50  0001 C CNN
F 4 "480-7100-1-ND" H 3050 2500 50  0001 C CNN "Digikey"
F 5 "MPRLS0001PG0000SA" H 3050 2500 50  0001 C CNN "MPN"
	1    3050 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1400 2750 1600 2750
$Comp
L Jitter_Components:ABPMXXX000XX0XX U?
U 1 1 5F5C76AA
P 3050 3700
AR Path="/5F5C76AA" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5C76AA" Ref="U9"  Part="1" 
F 0 "U9" H 2800 4200 50  0000 L CNN
F 1 "ABPMAND001PG2A3" H 2200 4100 50  0000 L CNN
F 2 "Jitter_Footprints:ABPM+DXXX000XX0XX" H 3150 3600 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/187/honeywell-sensing-basic-board-mount-pressure-abp-s-916690.pdf" H 3150 3700 50  0001 C CNN
F 4 "I2C 0x28" H 2500 3400 50  0000 L CNN "Interface"
F 5 "ABPMAND001PG2A3" H 3050 3700 50  0001 C CNN "MPN"
	1    3050 3700
	-1   0    0    -1  
$EndComp
NoConn ~ 2900 4000
$Comp
L power:GND #PWR?
U 1 1 5F5C76B7
P 3050 4000
AR Path="/5BF41E5D/5F5C76B7" Ref="#PWR?"  Part="1" 
AR Path="/5F5C76B7" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C76B7" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 3050 3750 50  0001 C CNN
F 1 "GND" H 3055 3827 50  0000 C CNN
F 2 "" H 3050 4000 50  0001 C CNN
F 3 "" H 3050 4000 50  0001 C CNN
	1    3050 4000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4100 3500 3750 3500
Wire Wire Line
	3750 3600 4100 3600
Connection ~ 2200 4350
$Comp
L power:GND #PWR?
U 1 1 5F5C75CF
P 1700 4650
AR Path="/5BF2E340/5F5C75CF" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C75CF" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75CF" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75CF" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 1700 4400 50  0001 C CNN
F 1 "GND" H 1705 4477 50  0000 C CNN
F 2 "" H 1700 4650 50  0001 C CNN
F 3 "" H 1700 4650 50  0001 C CNN
	1    1700 4650
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C75D6
P 1700 4500
AR Path="/5F5C75D6" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C75D6" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C75D6" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C75D6" Ref="C30"  Part="1" 
F 0 "C30" H 1815 4546 50  0000 L CNN
F 1 "1uF" H 1815 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1738 4350 50  0001 C CNN
F 3 "~" H 1700 4500 50  0001 C CNN
F 4 "decoupling" H 1700 4500 50  0001 C CNN "purpose"
	1    1700 4500
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C75DD
P 2200 4500
AR Path="/5F5C75DD" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C75DD" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C75DD" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C75DD" Ref="C31"  Part="1" 
F 0 "C31" H 2315 4546 50  0000 L CNN
F 1 "100nF" H 2315 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2238 4350 50  0001 C CNN
F 3 "~" H 2200 4500 50  0001 C CNN
F 4 "decoupling" H 2200 4500 50  0001 C CNN "purpose"
	1    2200 4500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C75E3
P 2200 4650
AR Path="/5BF2E340/5F5C75E3" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C75E3" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75E3" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75E3" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 2200 4400 50  0001 C CNN
F 1 "GND" H 2205 4477 50  0000 C CNN
F 2 "" H 2200 4650 50  0001 C CNN
F 3 "" H 2200 4650 50  0001 C CNN
	1    2200 4650
	-1   0    0    -1  
$EndComp
Connection ~ 1700 4350
Wire Wire Line
	1700 4350 2200 4350
$Comp
L power:+5V #PWR?
U 1 1 5F5C761D
P 1550 4350
AR Path="/5BF41E5D/5F5C761D" Ref="#PWR?"  Part="1" 
AR Path="/5F5C761D" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C761D" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 1550 4200 50  0001 C CNN
F 1 "+5V" H 1565 4523 50  0000 C CNN
F 2 "" H 1550 4350 50  0001 C CNN
F 3 "" H 1550 4350 50  0001 C CNN
	1    1550 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 4350 1700 4350
Connection ~ 3200 4750
Wire Wire Line
	3200 4750 3200 5100
Wire Wire Line
	3200 4750 3850 4750
Wire Wire Line
	3850 5100 4250 5100
$Comp
L Connector:TestPoint TP?
U 1 1 5F5C762B
P 4350 5100
AR Path="/5BF2E340/5F5C762B" Ref="TP?"  Part="1" 
AR Path="/5C00B45C/5F5C762B" Ref="TP?"  Part="1" 
AR Path="/5F5C762B" Ref="TP?"  Part="1" 
AR Path="/5F5B6035/5F5C762B" Ref="TP2"  Part="1" 
F 0 "TP2" H 4400 5250 50  0000 L CNN
F 1 "DNI" H 4400 5250 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 4550 5100 50  0001 C CNN
F 3 "~" H 4550 5100 50  0001 C CNN
	1    4350 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4350 2800 4450
Wire Wire Line
	2200 4350 2800 4350
Connection ~ 3850 5100
Text Notes 4350 5550 0    50   ~ 0
Place close to\nADC input
Wire Wire Line
	4250 5100 4350 5100
Connection ~ 4250 5100
Text Notes 5650 5750 2    59   ~ 0
5V to 3V divider.\nRC filter: 40kOhm, 2.2nF: Fc= 1.8Khz\n
$Comp
L Device:C C?
U 1 1 5F5C7616
P 4250 5250
AR Path="/5F5C7616" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C7616" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C7616" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C7616" Ref="C35"  Part="1" 
F 0 "C35" H 4000 5250 50  0000 L CNN
F 1 "2.2nF" H 4000 5150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4288 5100 50  0001 C CNN
F 3 "~" H 4250 5250 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 4250 5250 50  0001 C CNN "purpose"
	1    4250 5250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C760F
P 4250 5400
AR Path="/5BF2E340/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5F5C760F" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C760F" Ref="#PWR0157"  Part="1" 
F 0 "#PWR0157" H 4250 5150 50  0001 C CNN
F 1 "GND" H 4255 5227 50  0000 C CNN
F 2 "" H 4250 5400 50  0001 C CNN
F 3 "" H 4250 5400 50  0001 C CNN
	1    4250 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F5C7609
P 3850 4900
AR Path="/5BF41E62/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5F5C7609" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5F5C7609" Ref="R1"  Part="1" 
F 0 "R1" V 3643 4900 50  0000 C CNN
F 1 "68k" V 3734 4900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3780 4900 50  0001 C CNN
F 3 "~" H 3850 4900 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 3850 4900 50  0001 C CNN "purpose"
	1    3850 4900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C7602
P 3850 5400
AR Path="/5BF2E340/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5F5C7602" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C7602" Ref="#PWR0158"  Part="1" 
F 0 "#PWR0158" H 3850 5150 50  0001 C CNN
F 1 "GND" H 3855 5227 50  0000 C CNN
F 2 "" H 3850 5400 50  0001 C CNN
F 3 "" H 3850 5400 50  0001 C CNN
	1    3850 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5050 3850 5100
$Comp
L Device:R R?
U 1 1 5F5C75FB
P 3850 5250
AR Path="/5BF41E62/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5F5C75FB" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5F5C75FB" Ref="R20"  Part="1" 
F 0 "R20" V 3643 5250 50  0000 C CNN
F 1 "100k" V 3734 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3780 5250 50  0001 C CNN
F 3 "~" H 3850 5250 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 3850 5250 50  0001 C CNN "purpose"
	1    3850 5250
	-1   0    0    1   
$EndComp
Text Label 3850 4750 2    50   ~ 0
MPVZ5010_1_OUT
$Comp
L power:GND #PWR?
U 1 1 5F5C75F3
P 3200 5400
AR Path="/5BF2E340/5F5C75F3" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5C75F3" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75F3" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75F3" Ref="#PWR0159"  Part="1" 
F 0 "#PWR0159" H 3200 5150 50  0001 C CNN
F 1 "GND" H 3205 5227 50  0000 C CNN
F 2 "" H 3200 5400 50  0001 C CNN
F 3 "" H 3200 5400 50  0001 C CNN
	1    3200 5400
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5C75ED
P 3200 5250
AR Path="/5F5C75ED" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5C75ED" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5C75ED" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5C75ED" Ref="C34"  Part="1" 
F 0 "C34" H 3350 5200 50  0000 L CNN
F 1 "470pF" H 3250 5100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3238 5100 50  0001 C CNN
F 3 "~" H 3200 5250 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 3200 5250 50  0001 C CNN "purpose"
	1    3200 5250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5C75C9
P 2800 5050
AR Path="/5BF41E5D/5F5C75C9" Ref="#PWR?"  Part="1" 
AR Path="/5F5C75C9" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5C75C9" Ref="#PWR0160"  Part="1" 
F 0 "#PWR0160" H 2800 4800 50  0001 C CNN
F 1 "GND" H 2805 4877 50  0000 C CNN
F 2 "" H 2800 5050 50  0001 C CNN
F 3 "" H 2800 5050 50  0001 C CNN
	1    2800 5050
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Pressure:MPXH6115A U?
U 1 1 5F5C75C3
P 2800 4750
AR Path="/5BF41E5D/5F5C75C3" Ref="U?"  Part="1" 
AR Path="/5F5C75C3" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5C75C3" Ref="U11"  Part="1" 
F 0 "U11" H 2650 4450 50  0000 R CNN
F 1 "MPVZ5010GW6U" H 2650 4350 50  0000 R CNN
F 2 "Jitter_Footprints:MPVZ5010GW6U" H 2300 4400 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/302/MPVZ5010G-1127149.pdf" H 2800 5350 50  0001 C CNN
F 4 "MPVZ5010GW6U" H 2800 4750 50  0001 C CNN "MPN"
	1    2800 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3800 4600 2500
Wire Wire Line
	4600 3800 4100 3800
Wire Wire Line
	4700 2500 4600 2500
Connection ~ 4600 2500
Wire Wire Line
	3050 3300 2050 3300
Wire Wire Line
	2050 1850 3050 1850
Text Notes 1400 1600 0    50   ~ 0
Note: place one of the three footprints
Wire Notes Line
	1250 1100 5700 1100
Wire Notes Line
	5700 1100 5700 5800
Wire Notes Line
	5700 5800 1250 5800
Wire Notes Line
	1250 5800 1250 1100
Text Notes 6050 1400 0    118  ~ 24
Pressure sensor 2 (optional)
$Comp
L power:GND #PWR?
U 1 1 5F5FFB40
P 7700 2800
AR Path="/5BF41E5D/5F5FFB40" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFB40" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB40" Ref="#PWR0161"  Part="1" 
F 0 "#PWR0161" H 7700 2550 50  0001 C CNN
F 1 "GND" H 7705 2627 50  0000 C CNN
F 2 "" H 7700 2800 50  0001 C CNN
F 3 "" H 7700 2800 50  0001 C CNN
	1    7700 2800
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5FFB47
P 7100 2350
AR Path="/5F5FFB47" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFB47" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB47" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFB47" Ref="C6"  Part="1" 
F 0 "C6" H 7215 2396 50  0000 L CNN
F 1 "1nF" H 7215 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7138 2200 50  0001 C CNN
F 3 "~" H 7100 2350 50  0001 C CNN
F 4 "filter (see MPRLS0001PG0000SA datasheet)" H 7100 2350 50  0001 C CNN "purpose"
	1    7100 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7300 2200 7100 2200
Wire Wire Line
	7300 2300 7300 2500
Wire Wire Line
	7300 2500 7100 2500
NoConn ~ 7450 2800
NoConn ~ 7550 2800
$Comp
L Device:C C?
U 1 1 5F5FFB53
P 6250 2900
AR Path="/5F5FFB53" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFB53" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB53" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFB53" Ref="C9"  Part="1" 
F 0 "C9" H 6365 2946 50  0000 L CNN
F 1 "100nF" H 6365 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6288 2750 50  0001 C CNN
F 3 "~" H 6250 2900 50  0001 C CNN
F 4 "decoupling" H 6250 2900 50  0001 C CNN "purpose"
	1    6250 2900
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5FFB59
P 6250 3050
AR Path="/5BF2E340/5F5FFB59" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB59" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFB59" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB59" Ref="#PWR0162"  Part="1" 
F 0 "#PWR0162" H 6250 2800 50  0001 C CNN
F 1 "GND" H 6255 2877 50  0000 C CNN
F 2 "" H 6250 3050 50  0001 C CNN
F 3 "" H 6250 3050 50  0001 C CNN
	1    6250 3050
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F5FFB5F
P 6050 2750
AR Path="/5F5FFB5F" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB5F" Ref="#PWR0163"  Part="1" 
F 0 "#PWR0163" H 6050 2600 50  0001 C CNN
F 1 "+3.3V" H 6065 2923 50  0000 C CNN
F 2 "" H 6050 2750 50  0001 C CNN
F 3 "" H 6050 2750 50  0001 C CNN
	1    6050 2750
	1    0    0    -1  
$EndComp
Text Label 9100 2000 2    50   ~ 0
PSENSE_2_SPI_~CS~
Text Label 9100 2100 2    50   ~ 0
PSENSE_SPI_CLK
Text Label 9100 2200 2    50   ~ 0
PSENSE_SPI_MOSI
Text Label 9100 2300 2    50   ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	8400 2500 9250 2500
Wire Wire Line
	8400 2600 9100 2600
Text Label 9100 2600 2    50   ~ 0
PSENSE_RESET
$Comp
L Jitter_Components:MPRLS0001PG0000SA U?
U 1 1 5F5FFB71
P 7700 2500
AR Path="/5F5FFB71" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5FFB71" Ref="U8"  Part="1" 
F 0 "U8" H 6800 2200 50  0000 C CNN
F 1 "MPRLS0001PG0000SA" H 7150 2100 50  0000 C CNN
F 2 "Jitter_Footprints:MPRLS0001PG0000SA" H 7800 2500 50  0001 C CNN
F 3 "" H 7800 2500 50  0001 C CNN
F 4 "MPRLS0001PG0000SA" H 7700 2500 50  0001 C CNN "MPN"
F 5 "480-7100-1-ND" H 7700 2500 50  0001 C CNN "Digikey"
	1    7700 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6050 2750 6250 2750
$Comp
L Jitter_Components:ABPMXXX000XX0XX U?
U 1 1 5F5FFB7C
P 7700 3700
AR Path="/5F5FFB7C" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5FFB7C" Ref="U10"  Part="1" 
F 0 "U10" H 7450 4200 50  0000 L CNN
F 1 "ABPMAND001PG2A3" H 6850 4100 50  0000 L CNN
F 2 "Jitter_Footprints:ABPM+DXXX000XX0XX" H 7800 3600 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/187/honeywell-sensing-basic-board-mount-pressure-abp-s-916690.pdf" H 7800 3700 50  0001 C CNN
F 4 "I2C 0x28" H 7150 3400 50  0000 L CNN "Interface"
F 5 "ABPMAND001PG2A3" H 7700 3700 50  0001 C CNN "MPN"
	1    7700 3700
	-1   0    0    -1  
$EndComp
NoConn ~ 7550 4000
$Comp
L power:GND #PWR?
U 1 1 5F5FFB83
P 7700 4000
AR Path="/5BF41E5D/5F5FFB83" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFB83" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB83" Ref="#PWR0164"  Part="1" 
F 0 "#PWR0164" H 7700 3750 50  0001 C CNN
F 1 "GND" H 7705 3827 50  0000 C CNN
F 2 "" H 7700 4000 50  0001 C CNN
F 3 "" H 7700 4000 50  0001 C CNN
	1    7700 4000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8750 3500 8400 3500
Wire Wire Line
	8400 3600 8750 3600
Connection ~ 6850 4350
$Comp
L power:GND #PWR?
U 1 1 5F5FFB8E
P 6350 4650
AR Path="/5BF2E340/5F5FFB8E" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB8E" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFB8E" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFB8E" Ref="#PWR0165"  Part="1" 
F 0 "#PWR0165" H 6350 4400 50  0001 C CNN
F 1 "GND" H 6355 4477 50  0000 C CNN
F 2 "" H 6350 4650 50  0001 C CNN
F 3 "" H 6350 4650 50  0001 C CNN
	1    6350 4650
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5FFB95
P 6350 4500
AR Path="/5F5FFB95" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFB95" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB95" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFB95" Ref="C32"  Part="1" 
F 0 "C32" H 6465 4546 50  0000 L CNN
F 1 "1uF" H 6465 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6388 4350 50  0001 C CNN
F 3 "~" H 6350 4500 50  0001 C CNN
F 4 "decoupling" H 6350 4500 50  0001 C CNN "purpose"
	1    6350 4500
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5FFB9C
P 6850 4500
AR Path="/5F5FFB9C" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFB9C" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFB9C" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFB9C" Ref="C33"  Part="1" 
F 0 "C33" H 6965 4546 50  0000 L CNN
F 1 "100nF" H 6965 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6888 4350 50  0001 C CNN
F 3 "~" H 6850 4500 50  0001 C CNN
F 4 "decoupling" H 6850 4500 50  0001 C CNN "purpose"
	1    6850 4500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5FFBA2
P 6850 4650
AR Path="/5BF2E340/5F5FFBA2" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBA2" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFBA2" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFBA2" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 6850 4400 50  0001 C CNN
F 1 "GND" H 6855 4477 50  0000 C CNN
F 2 "" H 6850 4650 50  0001 C CNN
F 3 "" H 6850 4650 50  0001 C CNN
	1    6850 4650
	-1   0    0    -1  
$EndComp
Connection ~ 6350 4350
Wire Wire Line
	6350 4350 6850 4350
$Comp
L power:+5V #PWR?
U 1 1 5F5FFBAA
P 6200 4350
AR Path="/5BF41E5D/5F5FFBAA" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFBAA" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFBAA" Ref="#PWR0167"  Part="1" 
F 0 "#PWR0167" H 6200 4200 50  0001 C CNN
F 1 "+5V" H 6215 4523 50  0000 C CNN
F 2 "" H 6200 4350 50  0001 C CNN
F 3 "" H 6200 4350 50  0001 C CNN
	1    6200 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4350 6350 4350
Connection ~ 7850 4750
Wire Wire Line
	7850 4750 7850 5100
Wire Wire Line
	7850 4750 8500 4750
Wire Wire Line
	8500 5100 8900 5100
Wire Wire Line
	9000 5100 9600 5100
Connection ~ 9000 5100
$Comp
L Connector:TestPoint TP?
U 1 1 5F5FFBB8
P 9000 5100
AR Path="/5BF2E340/5F5FFBB8" Ref="TP?"  Part="1" 
AR Path="/5C00B45C/5F5FFBB8" Ref="TP?"  Part="1" 
AR Path="/5F5FFBB8" Ref="TP?"  Part="1" 
AR Path="/5F5B6035/5F5FFBB8" Ref="TP3"  Part="1" 
F 0 "TP3" H 9050 5250 50  0000 L CNN
F 1 "DNI" H 9050 5250 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 9200 5100 50  0001 C CNN
F 3 "~" H 9200 5100 50  0001 C CNN
	1    9000 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4350 7450 4450
Wire Wire Line
	6850 4350 7450 4350
Connection ~ 8500 5100
Text Notes 9000 5550 0    50   ~ 0
Place close to\nADC input
Wire Wire Line
	8900 5100 9000 5100
Connection ~ 8900 5100
Text Notes 10200 5750 2    59   ~ 0
5V to 3V divider.\nRC filter: 40kOhm, 2.2nF: Fc= 1.8Khz\n
$Comp
L Device:C C?
U 1 1 5F5FFBC6
P 8900 5250
AR Path="/5F5FFBC6" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFBC6" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBC6" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFBC6" Ref="C37"  Part="1" 
F 0 "C37" H 8650 5250 50  0000 L CNN
F 1 "2.2nF" H 8650 5150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8938 5100 50  0001 C CNN
F 3 "~" H 8900 5250 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 8900 5250 50  0001 C CNN "purpose"
	1    8900 5250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5FFBCC
P 8900 5400
AR Path="/5BF2E340/5F5FFBCC" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5F5FFBCC" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBCC" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFBCC" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFBCC" Ref="#PWR0168"  Part="1" 
F 0 "#PWR0168" H 8900 5150 50  0001 C CNN
F 1 "GND" H 8905 5227 50  0000 C CNN
F 2 "" H 8900 5400 50  0001 C CNN
F 3 "" H 8900 5400 50  0001 C CNN
	1    8900 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F5FFBD3
P 8500 4900
AR Path="/5BF41E62/5F5FFBD3" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5F5FFBD3" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5F5FFBD3" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBD3" Ref="R?"  Part="1" 
AR Path="/5F5FFBD3" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5F5FFBD3" Ref="R2"  Part="1" 
F 0 "R2" V 8293 4900 50  0000 C CNN
F 1 "68k" V 8384 4900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8430 4900 50  0001 C CNN
F 3 "~" H 8500 4900 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 8500 4900 50  0001 C CNN "purpose"
	1    8500 4900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5FFBD9
P 8500 5400
AR Path="/5BF2E340/5F5FFBD9" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5F5FFBD9" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBD9" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFBD9" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFBD9" Ref="#PWR0169"  Part="1" 
F 0 "#PWR0169" H 8500 5150 50  0001 C CNN
F 1 "GND" H 8505 5227 50  0000 C CNN
F 2 "" H 8500 5400 50  0001 C CNN
F 3 "" H 8500 5400 50  0001 C CNN
	1    8500 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 5050 8500 5100
$Comp
L Device:R R?
U 1 1 5F5FFBE1
P 8500 5250
AR Path="/5BF41E62/5F5FFBE1" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5F5FFBE1" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5F5FFBE1" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBE1" Ref="R?"  Part="1" 
AR Path="/5F5FFBE1" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5F5FFBE1" Ref="R21"  Part="1" 
F 0 "R21" V 8293 5250 50  0000 C CNN
F 1 "100k" V 8384 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8430 5250 50  0001 C CNN
F 3 "~" H 8500 5250 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 8500 5250 50  0001 C CNN "purpose"
	1    8500 5250
	-1   0    0    1   
$EndComp
Text Label 8500 4750 2    50   ~ 0
MPVZ5010_2_OUT
$Comp
L power:GND #PWR?
U 1 1 5F5FFBE8
P 7850 5400
AR Path="/5BF2E340/5F5FFBE8" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBE8" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFBE8" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFBE8" Ref="#PWR0170"  Part="1" 
F 0 "#PWR0170" H 7850 5150 50  0001 C CNN
F 1 "GND" H 7855 5227 50  0000 C CNN
F 2 "" H 7850 5400 50  0001 C CNN
F 3 "" H 7850 5400 50  0001 C CNN
	1    7850 5400
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F5FFBEF
P 7850 5250
AR Path="/5F5FFBEF" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5F5FFBEF" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5F5FFBEF" Ref="C?"  Part="1" 
AR Path="/5F5B6035/5F5FFBEF" Ref="C36"  Part="1" 
F 0 "C36" H 8000 5200 50  0000 L CNN
F 1 "470pF" H 7900 5100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7888 5100 50  0001 C CNN
F 3 "~" H 7850 5250 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 7850 5250 50  0001 C CNN "purpose"
	1    7850 5250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5FFBF5
P 7450 5050
AR Path="/5BF41E5D/5F5FFBF5" Ref="#PWR?"  Part="1" 
AR Path="/5F5FFBF5" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5F5FFBF5" Ref="#PWR0171"  Part="1" 
F 0 "#PWR0171" H 7450 4800 50  0001 C CNN
F 1 "GND" H 7455 4877 50  0000 C CNN
F 2 "" H 7450 5050 50  0001 C CNN
F 3 "" H 7450 5050 50  0001 C CNN
	1    7450 5050
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Pressure:MPXH6115A U?
U 1 1 5F5FFBFC
P 7450 4750
AR Path="/5BF41E5D/5F5FFBFC" Ref="U?"  Part="1" 
AR Path="/5F5FFBFC" Ref="U?"  Part="1" 
AR Path="/5F5B6035/5F5FFBFC" Ref="U12"  Part="1" 
F 0 "U12" H 7300 4450 50  0000 R CNN
F 1 "MPVZ5010GW6U" H 7300 4350 50  0000 R CNN
F 2 "Jitter_Footprints:MPVZ5010GW6U" H 6950 4400 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/302/MPVZ5010G-1127149.pdf" H 7450 5350 50  0001 C CNN
F 4 "MPVZ5010GW6U" H 7450 4750 50  0001 C CNN "MPN"
	1    7450 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 3800 9250 2500
Wire Wire Line
	9250 3800 8700 3800
Wire Wire Line
	9350 2500 9250 2500
Connection ~ 9250 2500
Wire Wire Line
	7700 3300 6800 3300
Wire Wire Line
	6800 1850 7700 1850
Text Notes 6050 1600 0    50   ~ 0
Note: this is optional. Choose at most one of the three footprints
Wire Notes Line
	5900 1100 10350 1100
Wire Notes Line
	10350 1100 10350 5800
Wire Notes Line
	10350 5800 5900 5800
Wire Notes Line
	5900 5800 5900 1100
Text HLabel 9350 2500 2    50   Output ~ 0
PSENSE_2_DATA_READY
Text HLabel 9350 2000 2    50   Input ~ 0
PSENSE_2_SPI_~CS~
Wire Wire Line
	8400 2000 9350 2000
Text HLabel 9350 2100 2    50   Input ~ 0
PSENSE_SPI_CLK
Text HLabel 9350 2200 2    50   Input ~ 0
PSENSE_SPI_MOSI
Text HLabel 9350 2300 2    50   Output ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	8400 2100 9350 2100
Wire Wire Line
	8400 2200 9350 2200
Wire Wire Line
	8400 2300 9350 2300
Text HLabel 4700 2000 2    50   Input ~ 0
PSENSE_1_SPI_~CS~
Wire Wire Line
	3750 2000 4700 2000
Text Notes 4750 2300 0    50   ~ 0
SPI bus shared\nbetween sensor 1/2
Wire Bus Line
	4700 2100 4700 2300
Text HLabel 4700 2500 2    50   Output ~ 0
PSENSE_1_DATA_READY
Text Label 4400 6700 0    50   ~ 0
P_SCL
Text Label 4950 6800 0    50   ~ 0
P_SDA
Text HLabel 5950 6700 2    50   BiDi ~ 0
I2C_SCL
Wire Wire Line
	5950 6700 5550 6700
Text HLabel 5950 6800 2    50   BiDi ~ 0
I2C_SDA
Wire Wire Line
	5550 6800 5950 6800
Text Notes 4200 3600 0    50   ~ 0
I2C bus\nshared
Wire Bus Line
	4150 3400 4150 3600
Text Notes 7350 3700 2    55   ~ 0
NOTE: if placing (multiple)\nI2C sensors, check for\nduplicate addresses!
Text Notes 2700 3700 2    55   ~ 0
NOTE: if placing (multiple)\nI2C sensors, check for\nduplicate addresses!
Text HLabel 9600 5100 2    50   Output ~ 0
A_PRESSURE_2
Text HLabel 4950 5100 2    50   Output ~ 0
A_PRESSURE_1
Wire Wire Line
	4950 5100 4350 5100
Connection ~ 4350 5100
$Comp
L Device:R R?
U 1 1 5E7A0096
P 6650 2750
AR Path="/5BF2E340/5E7A0096" Ref="R?"  Part="1" 
AR Path="/5E7A0096" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5E7A0096" Ref="R23"  Part="1" 
F 0 "R23" H 6720 2796 50  0000 L CNN
F 1 "0" H 6720 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6580 2750 50  0001 C CNN
F 3 "~" H 6650 2750 50  0001 C CNN
	1    6650 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 1850 6800 2150
Connection ~ 6800 2750
Wire Wire Line
	6800 2750 6800 3300
Wire Wire Line
	6500 2750 6250 2750
Connection ~ 6250 2750
$Comp
L Device:R R?
U 1 1 5E7A5311
P 1900 2750
AR Path="/5BF2E340/5E7A5311" Ref="R?"  Part="1" 
AR Path="/5E7A5311" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5E7A5311" Ref="R22"  Part="1" 
F 0 "R22" H 1970 2796 50  0000 L CNN
F 1 "0" H 1970 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1830 2750 50  0001 C CNN
F 3 "~" H 1900 2750 50  0001 C CNN
	1    1900 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2050 1850 2050 2100
Connection ~ 2050 2750
Wire Wire Line
	2050 2750 2050 3300
Wire Wire Line
	1750 2750 1600 2750
Connection ~ 1600 2750
$Comp
L Device:R R?
U 1 1 5E7A758F
P 8700 3950
AR Path="/5BF2E340/5E7A758F" Ref="R?"  Part="1" 
AR Path="/5E7A758F" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5E7A758F" Ref="R25"  Part="1" 
F 0 "R25" H 8770 3996 50  0000 L CNN
F 1 "DNI" H 8770 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8630 3950 50  0001 C CNN
F 3 "~" H 8700 3950 50  0001 C CNN
	1    8700 3950
	-1   0    0    1   
$EndComp
Connection ~ 8700 3800
Wire Wire Line
	8700 3800 8400 3800
Wire Wire Line
	8700 4100 8700 4750
Wire Wire Line
	8700 4750 8500 4750
Connection ~ 8500 4750
$Comp
L Device:R R?
U 1 1 5E7AB07D
P 4100 3950
AR Path="/5BF2E340/5E7AB07D" Ref="R?"  Part="1" 
AR Path="/5E7AB07D" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5E7AB07D" Ref="R24"  Part="1" 
F 0 "R24" H 4170 3996 50  0000 L CNN
F 1 "DNI" H 4170 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4030 3950 50  0001 C CNN
F 3 "~" H 4100 3950 50  0001 C CNN
	1    4100 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4100 4100 4100 4750
Wire Wire Line
	4100 4750 3850 4750
Connection ~ 3850 4750
Connection ~ 4100 3800
Wire Wire Line
	4100 3800 3750 3800
$Comp
L Device:R R?
U 1 1 5E7B1850
P 5400 6700
AR Path="/5BF2E340/5E7B1850" Ref="R?"  Part="1" 
AR Path="/5E7B1850" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5E7B1850" Ref="R27"  Part="1" 
F 0 "R27" H 5470 6746 50  0000 L CNN
F 1 "0" H 5470 6655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5330 6700 50  0001 C CNN
F 3 "~" H 5400 6700 50  0001 C CNN
	1    5400 6700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E7B1DA5
P 5400 6800
AR Path="/5BF2E340/5E7B1DA5" Ref="R?"  Part="1" 
AR Path="/5E7B1DA5" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5E7B1DA5" Ref="R28"  Part="1" 
F 0 "R28" H 5470 6846 50  0000 L CNN
F 1 "0" H 5470 6755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5330 6800 50  0001 C CNN
F 3 "~" H 5400 6800 50  0001 C CNN
	1    5400 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	4950 6800 5250 6800
Wire Wire Line
	4400 6700 4850 6700
Text Label 4100 3600 2    50   ~ 0
P_SCL
Text Label 4100 3500 2    50   ~ 0
P_SDA
Text Label 8750 3500 2    50   ~ 0
P_SDA
Text Label 8750 3600 2    50   ~ 0
P_SCL
$Comp
L Device:R R?
U 1 1 5E7B6BB2
P 4850 6550
AR Path="/5BF2E340/5E7B6BB2" Ref="R?"  Part="1" 
AR Path="/5E7B6BB2" Ref="R?"  Part="1" 
AR Path="/5F5B6035/5E7B6BB2" Ref="R26"  Part="1" 
F 0 "R26" H 4920 6596 50  0000 L CNN
F 1 "DNI" H 4920 6505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4780 6550 50  0001 C CNN
F 3 "~" H 4850 6550 50  0001 C CNN
	1    4850 6550
	1    0    0    -1  
$EndComp
Connection ~ 4850 6700
Wire Wire Line
	4850 6700 5250 6700
$Comp
L power:+5V #PWR?
U 1 1 5E7B8980
P 4850 6400
AR Path="/5BF41E5D/5E7B8980" Ref="#PWR?"  Part="1" 
AR Path="/5E7B8980" Ref="#PWR?"  Part="1" 
AR Path="/5F5B6035/5E7B8980" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 4850 6250 50  0001 C CNN
F 1 "+5V" H 4865 6573 50  0000 C CNN
F 2 "" H 4850 6400 50  0001 C CNN
F 3 "" H 4850 6400 50  0001 C CNN
	1    4850 6400
	1    0    0    -1  
$EndComp
Text Notes 4350 7200 0    50   ~ 0
ABP I2c version: U9, R24=DNI, R22,R27,R28=0\nABP analog version: R22,R26,R24=0, R27-28=DNI
Text Label 8550 1800 0    50   ~ 0
PSENSE_RESET
Text HLabel 9350 1800 2    50   Input ~ 0
PSENSE_RESET
Wire Wire Line
	8550 1800 9350 1800
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 6074E056
P 6800 2150
F 0 "#FLG0103" H 6800 2225 50  0001 C CNN
F 1 "PWR_FLAG" V 6800 2277 50  0000 L CNN
F 2 "" H 6800 2150 50  0001 C CNN
F 3 "~" H 6800 2150 50  0001 C CNN
	1    6800 2150
	0    -1   -1   0   
$EndComp
Connection ~ 6800 1850
Connection ~ 6800 2150
Wire Wire Line
	6800 2150 6800 2750
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 6074F209
P 2050 2100
F 0 "#FLG0104" H 2050 2175 50  0001 C CNN
F 1 "PWR_FLAG" V 2050 2227 50  0000 L CNN
F 2 "" H 2050 2100 50  0001 C CNN
F 3 "~" H 2050 2100 50  0001 C CNN
	1    2050 2100
	0    -1   -1   0   
$EndComp
Connection ~ 2050 2100
Wire Wire Line
	2050 2100 2050 2750
$EndSCHEMATC
