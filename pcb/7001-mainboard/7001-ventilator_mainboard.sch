EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Overview"
Date "2020-03-21"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5C0E7FF6
P 11350 10500
F 0 "H1" H 11450 10505 50  0000 L CNN
F 1 "DNI (mounting hole)" H 11450 10460 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad_Via" H 11350 10500 50  0001 C CNN
F 3 "~" H 11350 10500 50  0001 C CNN
	1    11350 10500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5C0E807D
P 11350 10600
F 0 "#PWR0119" H 11350 10350 50  0001 C CNN
F 1 "GND" H 11355 10427 50  0000 C CNN
F 2 "" H 11350 10600 50  0001 C CNN
F 3 "" H 11350 10600 50  0001 C CNN
	1    11350 10600
	1    0    0    -1  
$EndComp
Text Label 2350 5300 2    50   ~ 0
USB_DP
Text Label 2350 5400 2    50   ~ 0
USB_DN
$Comp
L Connector:USB_B_Micro J1
U 1 1 5E781095
P 950 5300
AR Path="/5E781095" Ref="J1"  Part="1" 
AR Path="/5C03F077/5E781095" Ref="J?"  Part="1" 
F 0 "J1" H 1005 5767 50  0000 C CNN
F 1 "USB_B_Micro" H 1005 5676 50  0000 C CNN
F 2 "Jitter_Footprints:USB_Micro-B_UJ2-MIBH-4-SMT-TR-67_SMD_Horizontal" H 1100 5250 50  0001 C CNN
F 3 "~" H 1100 5250 50  0001 C CNN
	1    950  5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5E78109B
P 950 5700
AR Path="/5E78109B" Ref="#PWR0105"  Part="1" 
AR Path="/5C03F077/5E78109B" Ref="#PWR?"  Part="1" 
F 0 "#PWR0105" H 950 5450 50  0001 C CNN
F 1 "GND" H 955 5527 50  0000 C CNN
F 2 "" H 950 5700 50  0001 C CNN
F 3 "" H 950 5700 50  0001 C CNN
	1    950  5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  5700 850  5700
Connection ~ 950  5700
NoConn ~ 1250 5500
Wire Wire Line
	1400 5100 1400 4600
Wire Wire Line
	1400 4600 1650 4600
Wire Wire Line
	1250 5100 1400 5100
$Comp
L Device:C C1
U 1 1 5E7810A7
P 1650 4750
AR Path="/5E7810A7" Ref="C1"  Part="1" 
AR Path="/5C03F077/5E7810A7" Ref="C?"  Part="1" 
F 0 "C1" H 1765 4796 50  0000 L CNN
F 1 "100nF" H 1765 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1688 4600 50  0001 C CNN
F 3 "~" H 1650 4750 50  0001 C CNN
	1    1650 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5E7810AD
P 1650 4900
AR Path="/5E7810AD" Ref="#PWR0106"  Part="1" 
AR Path="/5C03F077/5E7810AD" Ref="#PWR?"  Part="1" 
F 0 "#PWR0106" H 1650 4650 50  0001 C CNN
F 1 "GND" H 1655 4727 50  0000 C CNN
F 2 "" H 1650 4900 50  0001 C CNN
F 3 "" H 1650 4900 50  0001 C CNN
	1    1650 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5E7810B4
P 1300 6200
AR Path="/5E7810B4" Ref="#PWR0107"  Part="1" 
AR Path="/5C03F077/5E7810B4" Ref="#PWR?"  Part="1" 
F 0 "#PWR0107" H 1300 5950 50  0001 C CNN
F 1 "GND" H 1305 6027 50  0000 C CNN
F 2 "" H 1300 6200 50  0001 C CNN
F 3 "" H 1300 6200 50  0001 C CNN
	1    1300 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse_Small F?
U 1 1 5E7810BF
P 2050 4600
AR Path="/5C03F077/5E7810BF" Ref="F?"  Part="1" 
AR Path="/5E7810BF" Ref="F1"  Part="1" 
F 0 "F1" H 2050 4693 50  0000 C CNN
F 1 "MCCFB1206TFF/2" H 2050 4694 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" H 2050 4600 50  0001 C CNN
F 3 "~" H 2050 4600 50  0001 C CNN
F 4 "2A" H 2050 4600 50  0001 C CNN "Fuse Current"
F 5 "safety fuse" H 2050 4600 50  0001 C CNN "purpose"
	1    2050 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 4600 1650 4600
Connection ~ 1650 4600
Wire Wire Line
	2150 4600 2300 4600
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5E7810C8
P 2300 4600
AR Path="/5C03F077/5E7810C8" Ref="#FLG?"  Part="1" 
AR Path="/5E7810C8" Ref="#FLG0101"  Part="1" 
F 0 "#FLG0101" H 2300 4675 50  0001 C CNN
F 1 "PWR_FLAG" H 2300 4773 50  0000 C CNN
F 2 "" H 2300 4600 50  0001 C CNN
F 3 "~" H 2300 4600 50  0001 C CNN
	1    2300 4600
	-1   0    0    1   
$EndComp
Connection ~ 2300 4600
Wire Wire Line
	2300 4600 2650 4600
$Comp
L Power_Protection:TPD2E2U06 U?
U 1 1 5E7810D1
P 1700 6200
AR Path="/5C03F077/5E7810D1" Ref="U?"  Part="1" 
AR Path="/5E7810D1" Ref="U2"  Part="1" 
F 0 "U2" V 1654 6429 50  0000 L CNN
F 1 "TPD2E2U06" V 1745 6429 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-553" H 900 5950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpd2e2u06.pdf" H 1500 6400 50  0001 C CNN
F 4 "ESD protection" H 1700 6200 50  0001 C CNN "purpose"
	1    1700 6200
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 6200 1300 6200
NoConn ~ 1800 6500
Wire Wire Line
	1600 6500 1100 6500
Wire Wire Line
	1100 6500 1100 5900
Wire Wire Line
	1100 5900 1600 5900
Text Notes 1050 6800 0    50   ~ 0
ESD protection\n\nSee datasheet for layout
Wire Wire Line
	1250 5300 1800 5300
Wire Wire Line
	1250 5400 1600 5400
Wire Wire Line
	1800 5900 1800 5300
Connection ~ 1800 5300
Wire Wire Line
	1800 5300 2350 5300
Wire Wire Line
	1600 5900 1600 5400
Connection ~ 1600 5900
Connection ~ 1600 5400
Wire Wire Line
	1600 5400 2350 5400
Text Notes 24500 3300 0    47   ~ 0
TODO\nWith prototype: tune gate resistor value\nHigher = lower EMC, too high = slow response
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 5E795521
P 25750 3850
AR Path="/5BF41E62/5E795521" Ref="Q?"  Part="1" 
AR Path="/5E795521" Ref="Q1"  Part="1" 
F 0 "Q1" H 25400 3700 50  0000 L CNN
F 1 "IRLML6244TRPbF" H 25150 3600 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 25950 3950 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/196/irlml6244pbf-1228275.pdf" H 25750 3850 50  0001 C CNN
F 4 "30mOhm @Vgs < 3V" H 25750 3850 50  0001 C CNN "Rds(on)"
F 5 "sot-23 footprint nmos, Rds(on) ~ 0.1" H 25750 3850 50  0001 C CNN "alternative"
	1    25750 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E795527
P 25950 4100
AR Path="/5BF41E62/5E795527" Ref="#PWR?"  Part="1" 
AR Path="/5E795527" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 25950 3850 50  0001 C CNN
F 1 "GND" H 25955 3927 50  0000 C CNN
F 2 "" H 25950 4100 50  0001 C CNN
F 3 "" H 25950 4100 50  0001 C CNN
	1    25950 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 5E79552E
P 26850 3800
AR Path="/5E79552E" Ref="C19"  Part="1" 
AR Path="/5BF41E62/5E79552E" Ref="C?"  Part="1" 
F 0 "C19" H 27000 3700 50  0000 L CNN
F 1 "2.2nF" H 27000 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 26888 3650 50  0001 C CNN
F 3 "~" H 26850 3800 50  0001 C CNN
F 4 "EMC filter" H 26850 3800 50  0001 C CNN "purpose"
	1    26850 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E795534
P 26850 3950
AR Path="/5E795534" Ref="#PWR0109"  Part="1" 
AR Path="/5BF41E62/5E795534" Ref="#PWR?"  Part="1" 
F 0 "#PWR0109" H 26850 3700 50  0001 C CNN
F 1 "GND" H 26855 3777 50  0000 C CNN
F 2 "" H 26850 3950 50  0001 C CNN
F 3 "" H 26850 3950 50  0001 C CNN
	1    26850 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 5E79553B
P 26850 3100
AR Path="/5E79553B" Ref="C17"  Part="1" 
AR Path="/5BF41E62/5E79553B" Ref="C?"  Part="1" 
F 0 "C17" H 26550 3050 50  0000 L CNN
F 1 "2.2nF" H 26550 2950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 26888 2950 50  0001 C CNN
F 3 "~" H 26850 3100 50  0001 C CNN
F 4 "EMC filter" H 26850 3100 50  0001 C CNN "purpose"
	1    26850 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5E795541
P 26850 3250
AR Path="/5E795541" Ref="#PWR0110"  Part="1" 
AR Path="/5BF41E62/5E795541" Ref="#PWR?"  Part="1" 
F 0 "#PWR0110" H 26850 3000 50  0001 C CNN
F 1 "GND" H 26855 3077 50  0000 C CNN
F 2 "" H 26850 3250 50  0001 C CNN
F 3 "" H 26850 3250 50  0001 C CNN
	1    26850 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	27050 3350 27050 2950
Wire Wire Line
	27050 3450 27050 3650
Wire Wire Line
	27050 3650 26850 3650
Connection ~ 26850 2950
Wire Wire Line
	26850 2950 27050 2950
Connection ~ 26850 3650
Wire Wire Line
	25850 3650 26050 3650
$Comp
L Diode:BZT52Bxx D?
U 1 1 5E795552
P 26050 3800
AR Path="/5BF41E62/5E795552" Ref="D?"  Part="1" 
AR Path="/5E795552" Ref="D1"  Part="1" 
F 0 "D1" V 26004 3879 50  0000 L CNN
F 1 "BZT52C10+" V 26095 3879 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 26050 3625 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzt52b2v4.pdf" H 26050 3800 50  0001 C CNN
F 4 "500mW" V 26050 3800 50  0001 C CNN "Power rating"
F 5 "SOD-123 zener: 7.5-10V, Pd >= 500mW" V 26050 3800 50  0001 C CNN "alternative"
F 6 "10V" V 26050 3800 50  0001 C CNN "Zener voltage"
F 7 "fast discharging of inductive load" V 26050 3800 50  0001 C CNN "purpose"
	1    26050 3800
	0    1    1    0   
$EndComp
Connection ~ 26050 3650
Wire Wire Line
	25850 4050 25850 4100
Wire Wire Line
	25850 4100 25950 4100
Wire Wire Line
	26050 4100 26050 3950
Connection ~ 25950 4100
Wire Wire Line
	25950 4100 26050 4100
$Comp
L Device:R R?
U 1 1 5E79555F
P 25250 3850
AR Path="/5BF41E62/5E79555F" Ref="R?"  Part="1" 
AR Path="/5E79555F" Ref="R6"  Part="1" 
F 0 "R6" V 25043 3850 50  0000 C CNN
F 1 "1k" V 25134 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 25180 3850 50  0001 C CNN
F 3 "~" H 25250 3850 50  0001 C CNN
F 4 "EMC: edge rate limiting" V 25250 3850 50  0001 C CNN "purpose"
	1    25250 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	25400 3850 25450 3850
$Comp
L power:+6V #PWR?
U 1 1 5E795568
P 26700 2950
AR Path="/5BF41E62/5E795568" Ref="#PWR?"  Part="1" 
AR Path="/5E795568" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 26700 2800 50  0001 C CNN
F 1 "+6V" H 26715 3123 50  0000 C CNN
F 2 "" H 26700 2950 50  0001 C CNN
F 3 "" H 26700 2950 50  0001 C CNN
	1    26700 2950
	1    0    0    -1  
$EndComp
Text Notes 24450 2800 0    118  ~ 24
pwm out?
$Comp
L Connector_Generic_MountingPin:Conn_01x02_MountingPin J?
U 1 1 5E79556F
P 27250 3350
AR Path="/5BF41E62/5E79556F" Ref="J?"  Part="1" 
AR Path="/5E79556F" Ref="J3"  Part="1" 
F 0 "J3" H 27337 3220 50  0000 L CNN
F 1 "Conn_01x02_MountingPin" H 27337 3175 50  0001 L CNN
F 2 "Jitter_Footprints:JST_ZH_S2B-ZR-SM4A-TF_1x02-1MP_P1.5mm_Horizontal" H 27250 3350 50  0001 C CNN
F 3 "~" H 27250 3350 50  0001 C CNN
	1    27250 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E795575
P 27250 3650
AR Path="/5E795575" Ref="#PWR0112"  Part="1" 
AR Path="/5BF41E62/5E795575" Ref="#PWR?"  Part="1" 
F 0 "#PWR0112" H 27250 3400 50  0001 C CNN
F 1 "GND" H 27255 3477 50  0000 C CNN
F 2 "" H 27250 3650 50  0001 C CNN
F 3 "" H 27250 3650 50  0001 C CNN
	1    27250 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E79559A
P 27750 3550
AR Path="/5BF41E62/5E79559A" Ref="#PWR?"  Part="1" 
AR Path="/5E79559A" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 27750 3300 50  0001 C CNN
F 1 "GND" H 27755 3377 50  0000 C CNN
F 2 "" H 27750 3550 50  0001 C CNN
F 3 "" H 27750 3550 50  0001 C CNN
	1    27750 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+6V #PWR?
U 1 1 5E7955A0
P 27750 3250
AR Path="/5BF41E62/5E7955A0" Ref="#PWR?"  Part="1" 
AR Path="/5E7955A0" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 27750 3100 50  0001 C CNN
F 1 "+6V" H 27765 3423 50  0000 C CNN
F 2 "" H 27750 3250 50  0001 C CNN
F 3 "" H 27750 3250 50  0001 C CNN
	1    27750 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 5E7955A7
P 27750 3400
AR Path="/5E7955A7" Ref="C18"  Part="1" 
AR Path="/5BF2E340/5E7955A7" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7955A7" Ref="C?"  Part="1" 
AR Path="/5BF41E62/5E7955A7" Ref="C?"  Part="1" 
F 0 "C18" H 27865 3446 50  0000 L CNN
F 1 "1uF" H 27865 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 27788 3250 50  0001 C CNN
F 3 "~" H 27750 3400 50  0001 C CNN
F 4 "decoupling" H 27750 3400 50  0001 C CNN "purpose"
	1    27750 3400
	-1   0    0    -1  
$EndComp
Text Notes 24450 5350 0    59   ~ 0
Pull-down resistors: Actuators should be off by default.\n\nWhen the firmware is not running (for example during an update),\nthe microcontroller pins have a 85uA pull-up current enabled.\nThis would cause the actuators to start running unintentionally,\nWe avoid this by placing a strong pull-down resistor:\nR_pulldown = (0.5V/85uA)  -> R_puldown < 5.6k
$Comp
L Device:R R?
U 1 1 5E7955AF
P 25000 4000
AR Path="/5BF41E62/5E7955AF" Ref="R?"  Part="1" 
AR Path="/5E7955AF" Ref="R7"  Part="1" 
F 0 "R7" V 25200 4000 50  0000 C CNN
F 1 "4.7k" V 25100 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 24930 4000 50  0001 C CNN
F 3 "~" H 25000 4000 50  0001 C CNN
F 4 "pull-down: disable actuator by default" V 25000 4000 50  0001 C CNN "purpose"
	1    25000 4000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7955B5
P 25000 4150
AR Path="/5BF41E62/5E7955B5" Ref="#PWR?"  Part="1" 
AR Path="/5E7955B5" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 25000 3900 50  0001 C CNN
F 1 "GND" H 25005 3977 50  0000 C CNN
F 2 "" H 25000 4150 50  0001 C CNN
F 3 "" H 25000 4150 50  0001 C CNN
	1    25000 4150
	1    0    0    -1  
$EndComp
Connection ~ 25000 3850
Wire Wire Line
	25000 3850 25100 3850
$Comp
L Connector:TestPoint TP?
U 1 1 5E7955CC
P 25450 3650
AR Path="/5BF2E340/5E7955CC" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7955CC" Ref="TP?"  Part="1" 
AR Path="/5E7955CC" Ref="TP10"  Part="1" 
F 0 "TP10" H 25500 3900 50  0000 L CNN
F 1 "valve_2_fet" H 25500 3800 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 25650 3650 50  0001 C CNN
F 3 "~" H 25650 3650 50  0001 C CNN
	1    25450 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	25450 3650 25450 3850
Connection ~ 25450 3850
Wire Wire Line
	25450 3850 25550 3850
Wire Wire Line
	26700 2950 26850 2950
Wire Wire Line
	26050 3650 26850 3650
$Comp
L Sensor_Pressure:MPXH6115A U?
U 1 1 5E7AB8E8
P 19550 2100
AR Path="/5BF41E5D/5E7AB8E8" Ref="U?"  Part="1" 
AR Path="/5E7AB8E8" Ref="U1"  Part="1" 
F 0 "U1" H 19120 2146 50  0000 R CNN
F 1 "TODO" H 19120 2055 50  0000 R CNN
F 2 "" H 19050 1750 50  0001 C CNN
F 3 "" H 19550 2700 50  0001 C CNN
	1    19550 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB8EE
P 19550 2400
AR Path="/5BF41E5D/5E7AB8EE" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB8EE" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 19550 2150 50  0001 C CNN
F 1 "GND" H 19555 2227 50  0000 C CNN
F 2 "" H 19550 2400 50  0001 C CNN
F 3 "" H 19550 2400 50  0001 C CNN
	1    19550 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB8F4
P 18850 1500
AR Path="/5BF2E340/5E7AB8F4" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB8F4" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB8F4" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 18850 1250 50  0001 C CNN
F 1 "GND" H 18855 1327 50  0000 C CNN
F 2 "" H 18850 1500 50  0001 C CNN
F 3 "" H 18850 1500 50  0001 C CNN
	1    18850 1500
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5E7AB8FB
P 18850 1350
AR Path="/5E7AB8FB" Ref="C5"  Part="1" 
AR Path="/5BF2E340/5E7AB8FB" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB8FB" Ref="C?"  Part="1" 
F 0 "C5" H 18965 1396 50  0000 L CNN
F 1 "1uF" H 18965 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 18888 1200 50  0001 C CNN
F 3 "~" H 18850 1350 50  0001 C CNN
F 4 "decoupling" H 18850 1350 50  0001 C CNN "purpose"
	1    18850 1350
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5E7AB902
P 19350 1350
AR Path="/5E7AB902" Ref="C6"  Part="1" 
AR Path="/5BF2E340/5E7AB902" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB902" Ref="C?"  Part="1" 
F 0 "C6" H 19465 1396 50  0000 L CNN
F 1 "100nF" H 19465 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 19388 1200 50  0001 C CNN
F 3 "~" H 19350 1350 50  0001 C CNN
F 4 "decoupling" H 19350 1350 50  0001 C CNN "purpose"
	1    19350 1350
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB908
P 19350 1500
AR Path="/5BF2E340/5E7AB908" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB908" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB908" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 19350 1250 50  0001 C CNN
F 1 "GND" H 19355 1327 50  0000 C CNN
F 2 "" H 19350 1500 50  0001 C CNN
F 3 "" H 19350 1500 50  0001 C CNN
	1    19350 1500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	19550 1200 19550 1800
Connection ~ 18850 1200
Wire Wire Line
	18850 1200 19350 1200
Connection ~ 19350 1200
Wire Wire Line
	19350 1200 19550 1200
$Comp
L Device:C C8
U 1 1 5E7AB914
P 20300 2250
AR Path="/5E7AB914" Ref="C8"  Part="1" 
AR Path="/5BF2E340/5E7AB914" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB914" Ref="C?"  Part="1" 
F 0 "C8" H 20415 2296 50  0000 L CNN
F 1 "47pF" H 20415 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 20338 2100 50  0001 C CNN
F 3 "~" H 20300 2250 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 20300 2250 50  0001 C CNN "purpose"
	1    20300 2250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB91A
P 20300 2400
AR Path="/5BF2E340/5E7AB91A" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB91A" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB91A" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 20300 2150 50  0001 C CNN
F 1 "GND" H 20305 2227 50  0000 C CNN
F 2 "" H 20300 2400 50  0001 C CNN
F 3 "" H 20300 2400 50  0001 C CNN
	1    20300 2400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	19950 2100 20300 2100
Connection ~ 20300 2100
Text Label 19950 2100 0    50   ~ 0
pressure_sensor_out
$Comp
L Device:R R?
U 1 1 5E7AB934
P 21400 2600
AR Path="/5BF41E62/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5E7AB934" Ref="R2"  Part="1" 
F 0 "R2" V 21193 2600 50  0000 C CNN
F 1 "100k" V 21284 2600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 21330 2600 50  0001 C CNN
F 3 "~" H 21400 2600 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 21400 2600 50  0001 C CNN "purpose"
	1    21400 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	21400 2400 21400 2450
$Comp
L power:GND #PWR?
U 1 1 5E7AB93C
P 21400 2750
AR Path="/5BF2E340/5E7AB93C" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB93C" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB93C" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB93C" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 21400 2500 50  0001 C CNN
F 1 "GND" H 21405 2577 50  0000 C CNN
F 2 "" H 21400 2750 50  0001 C CNN
F 3 "" H 21400 2750 50  0001 C CNN
	1    21400 2750
	1    0    0    -1  
$EndComp
Text HLabel 22600 2450 2    50   Output ~ 0
pressure_level
$Comp
L Device:R R?
U 1 1 5E7AB944
P 21400 2250
AR Path="/5BF41E62/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5E7AB944" Ref="R1"  Part="1" 
F 0 "R1" V 21193 2250 50  0000 C CNN
F 1 "68k" V 21284 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 21330 2250 50  0001 C CNN
F 3 "~" H 21400 2250 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 21400 2250 50  0001 C CNN "purpose"
	1    21400 2250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB94A
P 22350 2750
AR Path="/5BF2E340/5E7AB94A" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB94A" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB94A" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB94A" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 22350 2500 50  0001 C CNN
F 1 "GND" H 22355 2577 50  0000 C CNN
F 2 "" H 22350 2750 50  0001 C CNN
F 3 "" H 22350 2750 50  0001 C CNN
	1    22350 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5E7AB952
P 22350 2600
AR Path="/5E7AB952" Ref="C9"  Part="1" 
AR Path="/5BF2E340/5E7AB952" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB952" Ref="C?"  Part="1" 
F 0 "C9" H 22100 2600 50  0000 L CNN
F 1 "2.2nF" H 22100 2500 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 22388 2450 50  0001 C CNN
F 3 "~" H 22350 2600 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 22350 2600 50  0001 C CNN "purpose"
	1    22350 2600
	-1   0    0    -1  
$EndComp
Text Notes 21400 2000 0    59   ~ 0
5V to 3V divider.\nRC filter: 40kOhm, 2.2nF: Fc= 1.8Khz\n
Text HLabel 18150 1200 0    50   Input ~ 0
+5V
Wire Wire Line
	18150 1200 18350 1200
$Comp
L power:+5V #PWR?
U 1 1 5E7AB95B
P 18350 1200
AR Path="/5BF41E5D/5E7AB95B" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB95B" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 18350 1050 50  0001 C CNN
F 1 "+5V" H 18365 1373 50  0000 C CNN
F 2 "" H 18350 1200 50  0001 C CNN
F 3 "" H 18350 1200 50  0001 C CNN
	1    18350 1200
	1    0    0    -1  
$EndComp
Connection ~ 18350 1200
Wire Wire Line
	18350 1200 18850 1200
Connection ~ 22350 2450
Wire Wire Line
	22350 2450 22600 2450
Text Notes 22450 2900 0    50   ~ 0
Place close to\nADC input
$Comp
L Connector:TestPoint TP?
U 1 1 5E7AB966
P 20900 1900
AR Path="/5BF2E340/5E7AB966" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7AB966" Ref="TP?"  Part="1" 
AR Path="/5BF41E5D/5E7AB966" Ref="TP?"  Part="1" 
AR Path="/5E7AB966" Ref="TP2"  Part="1" 
F 0 "TP2" H 20950 2150 50  0000 L CNN
F 1 "sensor_out" H 20950 2050 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 21100 1900 50  0001 C CNN
F 3 "~" H 21100 1900 50  0001 C CNN
	1    20900 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	20900 1900 20900 2100
$Comp
L Connector:TestPoint TP?
U 1 1 5E7AB96F
P 22050 2450
AR Path="/5BF2E340/5E7AB96F" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7AB96F" Ref="TP?"  Part="1" 
AR Path="/5BF41E5D/5E7AB96F" Ref="TP?"  Part="1" 
AR Path="/5E7AB96F" Ref="TP3"  Part="1" 
F 0 "TP3" H 22100 2700 50  0000 L CNN
F 1 "pressure_level" H 22100 2600 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 22250 2450 50  0001 C CNN
F 3 "~" H 22250 2450 50  0001 C CNN
	1    22050 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	22050 2450 22350 2450
Text HLabel 20050 4650 0    50   Input ~ 0
LED_CLK
$Comp
L power:GND #PWR?
U 1 1 5E7B5E03
P 20900 4750
AR Path="/5BF2E340/5E7B5E03" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E03" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E03" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 20900 4500 50  0001 C CNN
F 1 "GND" H 20905 4577 50  0000 C CNN
F 2 "" H 20900 4750 50  0001 C CNN
F 3 "" H 20900 4750 50  0001 C CNN
	1    20900 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5E7B5E0A
P 21350 4200
AR Path="/5E7B5E0A" Ref="C11"  Part="1" 
AR Path="/5BF2E340/5E7B5E0A" Ref="C?"  Part="1" 
AR Path="/5C0338CC/5E7B5E0A" Ref="C?"  Part="1" 
F 0 "C11" H 21465 4246 50  0000 L CNN
F 1 "100nF" H 21465 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 21388 4050 50  0001 C CNN
F 3 "~" H 21350 4200 50  0001 C CNN
F 4 "decoupling" H 21350 4200 50  0001 C CNN "purpose"
	1    21350 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7B5E10
P 21350 4350
AR Path="/5BF2E340/5E7B5E10" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E10" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E10" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 21350 4100 50  0001 C CNN
F 1 "GND" H 21355 4177 50  0000 C CNN
F 2 "" H 21350 4350 50  0001 C CNN
F 3 "" H 21350 4350 50  0001 C CNN
	1    21350 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E16
P 21350 4050
AR Path="/5BF41E5D/5E7B5E16" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E16" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E16" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 21350 3900 50  0001 C CNN
F 1 "+5V" H 21365 4223 50  0000 C CNN
F 2 "" H 21350 4050 50  0001 C CNN
F 3 "" H 21350 4050 50  0001 C CNN
	1    21350 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	20050 4650 20350 4650
Text Notes 19700 3850 0    59   ~ 12
3V to 5V level shifting
Text Label 22150 5250 0    50   ~ 0
LED_clock_5V
Text Label 22150 5350 0    50   ~ 0
LED_data_5V
$Comp
L 74xGxx:74AHCT1G125 U?
U 1 1 5E7B5E20
P 20850 4650
AR Path="/5C0338CC/5E7B5E20" Ref="U?"  Part="1" 
AR Path="/5E7B5E20" Ref="U5"  Part="1" 
F 0 "U5" H 20750 4300 50  0000 C CNN
F 1 "74AHCT1G125SE" H 20550 4200 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 20850 4650 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1464459.pdf" H 20850 4650 50  0001 C CNN
	1    20850 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	20900 4600 20900 4500
Wire Wire Line
	20900 4500 21000 4500
Wire Wire Line
	20900 4700 20900 4750
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E29
P 21000 4500
AR Path="/5BF41E5D/5E7B5E29" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E29" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E29" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 21000 4350 50  0001 C CNN
F 1 "+5V" H 21015 4673 50  0000 C CNN
F 2 "" H 21000 4500 50  0001 C CNN
F 3 "" H 21000 4500 50  0001 C CNN
	1    21000 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	20850 4450 20850 4150
Wire Wire Line
	20850 4150 20350 4150
Text HLabel 20050 4150 0    50   Input ~ 0
LED_~CS~
Text Label 20450 4150 0    50   ~ 0
LED_~CS~
Text HLabel 20050 5950 0    50   Input ~ 0
LED_MOSI
$Comp
L power:GND #PWR?
U 1 1 5E7B5E34
P 20900 6050
AR Path="/5BF2E340/5E7B5E34" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E34" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E34" Ref="#PWR0128"  Part="1" 
F 0 "#PWR0128" H 20900 5800 50  0001 C CNN
F 1 "GND" H 20905 5877 50  0000 C CNN
F 2 "" H 20900 6050 50  0001 C CNN
F 3 "" H 20900 6050 50  0001 C CNN
	1    20900 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 5E7B5E3B
P 21350 5500
AR Path="/5E7B5E3B" Ref="C16"  Part="1" 
AR Path="/5BF2E340/5E7B5E3B" Ref="C?"  Part="1" 
AR Path="/5C0338CC/5E7B5E3B" Ref="C?"  Part="1" 
F 0 "C16" H 21465 5546 50  0000 L CNN
F 1 "100nF" H 21465 5455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 21388 5350 50  0001 C CNN
F 3 "~" H 21350 5500 50  0001 C CNN
F 4 "decoupling" H 21350 5500 50  0001 C CNN "purpose"
	1    21350 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7B5E41
P 21350 5650
AR Path="/5BF2E340/5E7B5E41" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E41" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E41" Ref="#PWR0129"  Part="1" 
F 0 "#PWR0129" H 21350 5400 50  0001 C CNN
F 1 "GND" H 21355 5477 50  0000 C CNN
F 2 "" H 21350 5650 50  0001 C CNN
F 3 "" H 21350 5650 50  0001 C CNN
	1    21350 5650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E47
P 21350 5350
AR Path="/5BF41E5D/5E7B5E47" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E47" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E47" Ref="#PWR0130"  Part="1" 
F 0 "#PWR0130" H 21350 5200 50  0001 C CNN
F 1 "+5V" H 21365 5523 50  0000 C CNN
F 2 "" H 21350 5350 50  0001 C CNN
F 3 "" H 21350 5350 50  0001 C CNN
	1    21350 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	20050 5950 20350 5950
$Comp
L 74xGxx:74AHCT1G125 U?
U 1 1 5E7B5E4E
P 20850 5950
AR Path="/5C0338CC/5E7B5E4E" Ref="U?"  Part="1" 
AR Path="/5E7B5E4E" Ref="U6"  Part="1" 
F 0 "U6" H 20350 5800 50  0000 C CNN
F 1 "74AHCT1G125SE" H 20550 5700 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 20850 5950 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1464459.pdf" H 20850 5950 50  0001 C CNN
	1    20850 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	20900 5900 20900 5800
Wire Wire Line
	20900 5800 21000 5800
Wire Wire Line
	20900 6000 20900 6050
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E57
P 21000 5800
AR Path="/5BF41E5D/5E7B5E57" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E57" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E57" Ref="#PWR0131"  Part="1" 
F 0 "#PWR0131" H 21000 5650 50  0001 C CNN
F 1 "+5V" H 21015 5973 50  0000 C CNN
F 2 "" H 21000 5800 50  0001 C CNN
F 3 "" H 21000 5800 50  0001 C CNN
	1    21000 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	20850 5750 20850 5450
Wire Wire Line
	20850 5450 20450 5450
Text Label 20450 5450 0    50   ~ 0
LED_~CS~
Wire Wire Line
	21850 4650 21850 5250
Wire Wire Line
	21850 5250 22950 5250
Wire Wire Line
	21100 4650 21800 4650
Wire Wire Line
	21850 5350 21850 5950
Wire Wire Line
	21850 5350 22950 5350
Wire Wire Line
	21100 5950 21800 5950
Wire Notes Line
	22050 3600 19600 3600
Wire Notes Line
	19600 3600 19600 6450
Wire Notes Line
	19600 6450 22050 6450
Wire Notes Line
	22050 6450 22050 3600
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E6A
P 21800 4650
AR Path="/5BF2E340/5E7B5E6A" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E6A" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E6A" Ref="TP?"  Part="1" 
AR Path="/5E7B5E6A" Ref="TP7"  Part="1" 
F 0 "TP7" H 21750 4550 50  0000 R CNN
F 1 "LED_clk_5V" H 21750 4450 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 22000 4650 50  0001 C CNN
F 3 "~" H 22000 4650 50  0001 C CNN
	1    21800 4650
	1    0    0    -1  
$EndComp
Connection ~ 21800 4650
Wire Wire Line
	21800 4650 21850 4650
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E72
P 21800 5950
AR Path="/5BF2E340/5E7B5E72" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E72" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E72" Ref="TP?"  Part="1" 
AR Path="/5E7B5E72" Ref="TP9"  Part="1" 
F 0 "TP9" H 21850 6200 50  0000 L CNN
F 1 "LED_data_5V" H 21850 6100 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 22000 5950 50  0001 C CNN
F 3 "~" H 22000 5950 50  0001 C CNN
	1    21800 5950
	-1   0    0    1   
$EndComp
Connection ~ 21800 5950
Wire Wire Line
	21800 5950 21850 5950
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E7A
P 20350 4150
AR Path="/5BF2E340/5E7B5E7A" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E7A" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E7A" Ref="TP?"  Part="1" 
AR Path="/5E7B5E7A" Ref="TP4"  Part="1" 
F 0 "TP4" H 20400 4400 50  0000 L CNN
F 1 "LED_~CS~" H 20400 4300 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 20550 4150 50  0001 C CNN
F 3 "~" H 20550 4150 50  0001 C CNN
	1    20350 4150
	-1   0    0    1   
$EndComp
Connection ~ 20350 4150
Wire Wire Line
	20350 4150 20050 4150
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E82
P 20350 4650
AR Path="/5BF2E340/5E7B5E82" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E82" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E82" Ref="TP?"  Part="1" 
AR Path="/5E7B5E82" Ref="TP6"  Part="1" 
F 0 "TP6" H 20400 4900 50  0000 L CNN
F 1 "LED_CLK" H 20400 4800 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 20550 4650 50  0001 C CNN
F 3 "~" H 20550 4650 50  0001 C CNN
	1    20350 4650
	-1   0    0    1   
$EndComp
Connection ~ 20350 4650
Wire Wire Line
	20350 4650 20550 4650
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E8A
P 20350 5950
AR Path="/5BF2E340/5E7B5E8A" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E8A" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E8A" Ref="TP?"  Part="1" 
AR Path="/5E7B5E8A" Ref="TP8"  Part="1" 
F 0 "TP8" H 20250 6250 50  0000 R CNN
F 1 "LED_MOSI" H 20250 6150 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 20550 5950 50  0001 C CNN
F 3 "~" H 20550 5950 50  0001 C CNN
	1    20350 5950
	1    0    0    -1  
$EndComp
Connection ~ 20350 5950
Wire Wire Line
	20350 5950 20550 5950
Wire Wire Line
	5600 8200 5600 8350
$Comp
L power:GND #PWR?
U 1 1 5E7D4AE3
P 5600 8350
AR Path="/5BF2E340/5E7D4AE3" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4AE3" Ref="#PWR0132"  Part="1" 
F 0 "#PWR0132" H 5600 8100 50  0001 C CNN
F 1 "GND" H 5605 8177 50  0000 C CNN
F 2 "" H 5600 8350 50  0001 C CNN
F 3 "" H 5600 8350 50  0001 C CNN
	1    5600 8350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4AE9
P 7600 8000
AR Path="/5BF2E340/5E7D4AE9" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4AE9" Ref="#PWR0133"  Part="1" 
F 0 "#PWR0133" H 7600 7750 50  0001 C CNN
F 1 "GND" H 7605 7827 50  0000 C CNN
F 2 "" H 7600 8000 50  0001 C CNN
F 3 "" H 7600 8000 50  0001 C CNN
	1    7600 8000
	1    0    0    -1  
$EndComp
Text Label 4400 7000 0    50   ~ 0
SWDIO
Text Label 7750 7400 2    50   ~ 0
USB_DN
Text Label 7750 7300 2    50   ~ 0
USB_DP
$Comp
L Device:R R?
U 1 1 5E7D4AF3
P 6800 7300
AR Path="/5BF2E340/5E7D4AF3" Ref="R?"  Part="1" 
AR Path="/5E7D4AF3" Ref="R4"  Part="1" 
F 0 "R4" V 6700 7250 50  0000 L CNN
F 1 "33R" V 6800 7250 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6730 7300 50  0001 C CNN
F 3 "~" H 6800 7300 50  0001 C CNN
	1    6800 7300
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E7D4AF9
P 6800 7400
AR Path="/5BF2E340/5E7D4AF9" Ref="R?"  Part="1" 
AR Path="/5E7D4AF9" Ref="R5"  Part="1" 
F 0 "R5" V 6900 7350 50  0000 L CNN
F 1 "33R" V 6800 7350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6730 7400 50  0001 C CNN
F 3 "~" H 6800 7400 50  0001 C CNN
	1    6800 7400
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 7400 7750 7400
$Comp
L Device:R R?
U 1 1 5E7D4B03
P 7300 7150
AR Path="/5BF2E340/5E7D4B03" Ref="R?"  Part="1" 
AR Path="/5E7D4B03" Ref="R3"  Part="1" 
F 0 "R3" H 7370 7196 50  0000 L CNN
F 1 "1k5" H 7370 7105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7230 7150 50  0001 C CNN
F 3 "~" H 7300 7150 50  0001 C CNN
	1    7300 7150
	-1   0    0    1   
$EndComp
Text Notes 24650 1850 0    101  Italic 20
Actuator control
Wire Wire Line
	5500 8200 5600 8200
Wire Wire Line
	4400 7000 4900 7000
Wire Wire Line
	4900 7700 4400 7700
Text Label 25550 2300 2    50   ~ 0
pwm_1
Text Label 25550 2050 2    50   ~ 0
pwm_2
Text Label 25550 2150 2    50   ~ 0
pwm_3
Text Label 6800 6700 2    50   ~ 0
UART_TX
Wire Notes Line
	24450 1550 26450 1550
Wire Notes Line
	26450 1550 26450 2450
Wire Notes Line
	26450 2450 24450 2450
Wire Notes Line
	24450 2450 24450 1550
$Comp
L power:GND #PWR?
U 1 1 5E7D4B7C
P 6900 8100
AR Path="/5BF2E340/5E7D4B7C" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B7C" Ref="#PWR0135"  Part="1" 
F 0 "#PWR0135" H 6900 7850 50  0001 C CNN
F 1 "GND" H 6905 7927 50  0000 C CNN
F 2 "" H 6900 8100 50  0001 C CNN
F 3 "" H 6900 8100 50  0001 C CNN
	1    6900 8100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4B82
P 7300 8100
AR Path="/5BF2E340/5E7D4B82" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B82" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 7300 7850 50  0001 C CNN
F 1 "GND" H 7305 7927 50  0000 C CNN
F 2 "" H 7300 8100 50  0001 C CNN
F 3 "" H 7300 8100 50  0001 C CNN
	1    7300 8100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 7800 6650 7800
Wire Wire Line
	6650 7800 6650 8500
Wire Wire Line
	6650 8500 7100 8500
Wire Wire Line
	7100 8500 7100 8250
$Comp
L Device:C C12
U 1 1 5E7D4B8D
P 7100 8650
AR Path="/5E7D4B8D" Ref="C12"  Part="1" 
AR Path="/5BF2E340/5E7D4B8D" Ref="C?"  Part="1" 
F 0 "C12" H 7215 8696 50  0000 L CNN
F 1 "18pF" H 7215 8605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7138 8500 50  0001 C CNN
F 3 "~" H 7100 8650 50  0001 C CNN
F 4 "crystal matching (see LPC11u3X datasheet)" H 7100 8650 50  0001 C CNN "purpose"
	1    7100 8650
	1    0    0    -1  
$EndComp
Connection ~ 7100 8500
$Comp
L power:GND #PWR?
U 1 1 5E7D4B94
P 7100 8800
AR Path="/5BF2E340/5E7D4B94" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B94" Ref="#PWR0137"  Part="1" 
F 0 "#PWR0137" H 7100 8550 50  0001 C CNN
F 1 "GND" H 7105 8627 50  0000 C CNN
F 2 "" H 7100 8800 50  0001 C CNN
F 3 "" H 7100 8800 50  0001 C CNN
	1    7100 8800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5E7D4B9B
P 7600 7850
AR Path="/5E7D4B9B" Ref="C10"  Part="1" 
AR Path="/5BF2E340/5E7D4B9B" Ref="C?"  Part="1" 
F 0 "C10" H 7715 7896 50  0000 L CNN
F 1 "18pF" H 7715 7805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7638 7700 50  0001 C CNN
F 3 "~" H 7600 7850 50  0001 C CNN
F 4 "crystal matching (see LPC11u3X datasheet)" H 7600 7850 50  0001 C CNN "purpose"
	1    7600 7850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 7700 7100 7950
Wire Wire Line
	7100 7700 7600 7700
Connection ~ 7100 7700
$Comp
L Device:Crystal_GND24 Y?
U 1 1 5E7D4BA8
P 7100 8100
AR Path="/5BF2E340/5E7D4BA8" Ref="Y?"  Part="1" 
AR Path="/5E7D4BA8" Ref="Y1"  Part="1" 
F 0 "Y1" V 6950 8200 50  0000 L CNN
F 1 "MCSJK-7U-12.00-10-10-80-B-10" V 7400 8250 50  0001 L CNN
F 2 "Crystal:Crystal_SMD_3225-4Pin_3.2x2.5mm" H 7100 8100 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2645227.pdf?_ga=2.101838344.844808790.1542789852-389210046.1542789852" H 7100 8100 50  0001 C CNN
F 4 "10pF" V 7100 8100 50  0001 C CNN "Load capacitance"
F 5 "80 Ohm" V 7100 8100 50  0001 C CNN "ESR"
F 6 "18pF (see LPC11U3XX datasheet)" V 7100 8100 50  0001 C CNN "Required capacitor value"
F 7 "3225-size crystal, ESR<160,see LPC11U3XX datasheet" V 7100 8100 50  0001 C CNN "alternative"
	1    7100 8100
	0    1    1    0   
$EndComp
Text Label 6300 7700 0    50   ~ 0
XTAL_IN
Text Label 6300 7800 0    50   ~ 0
XTAL_OUT
Text Notes 26350 2150 2    50   ~ 0
CT16B0_MAT0
Text Notes 26350 2050 2    50   ~ 0
CT16B0_MAT1
Text Notes 26350 2300 2    50   ~ 0
CT16B1_MAT1
NoConn ~ 6300 6700
Wire Wire Line
	6300 7700 7100 7700
Wire Wire Line
	6300 6700 6800 6700
Wire Wire Line
	4900 5600 3650 5600
Text Notes 6850 6700 0    50   ~ 0
Optional:\nUART header?
NoConn ~ 6300 6600
Wire Wire Line
	5800 4450 6250 4450
Connection ~ 5800 4450
$Comp
L power:GND #PWR?
U 1 1 5E7D4C3B
P 5800 4750
AR Path="/5BF2E340/5E7D4C3B" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C3B" Ref="#PWR0139"  Part="1" 
F 0 "#PWR0139" H 5800 4500 50  0001 C CNN
F 1 "GND" H 5805 4577 50  0000 C CNN
F 2 "" H 5800 4750 50  0001 C CNN
F 3 "" H 5800 4750 50  0001 C CNN
	1    5800 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4C41
P 6250 4750
AR Path="/5BF2E340/5E7D4C41" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C41" Ref="#PWR0140"  Part="1" 
F 0 "#PWR0140" H 6250 4500 50  0001 C CNN
F 1 "GND" H 6255 4577 50  0000 C CNN
F 2 "" H 6250 4750 50  0001 C CNN
F 3 "" H 6250 4750 50  0001 C CNN
	1    6250 4750
	1    0    0    -1  
$EndComp
Connection ~ 6250 4450
$Comp
L Device:C C3
U 1 1 5E7D4C4A
P 6250 4600
AR Path="/5E7D4C4A" Ref="C3"  Part="1" 
AR Path="/5BF2E340/5E7D4C4A" Ref="C?"  Part="1" 
F 0 "C3" H 6365 4646 50  0000 L CNN
F 1 "100nF" H 6365 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6288 4450 50  0001 C CNN
F 3 "~" H 6250 4600 50  0001 C CNN
F 4 "decoupling" H 6250 4600 50  0001 C CNN "purpose"
	1    6250 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E7D4C51
P 5800 4600
AR Path="/5E7D4C51" Ref="C2"  Part="1" 
AR Path="/5BF2E340/5E7D4C51" Ref="C?"  Part="1" 
F 0 "C2" H 5915 4646 50  0000 L CNN
F 1 "100nF" H 5915 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5838 4450 50  0001 C CNN
F 3 "~" H 5800 4600 50  0001 C CNN
F 4 "decoupling" H 5800 4600 50  0001 C CNN "purpose"
	1    5800 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4450 5800 4450
$Comp
L Device:C C4
U 1 1 5E7D4C59
P 6750 4600
AR Path="/5E7D4C59" Ref="C4"  Part="1" 
AR Path="/5BF2E340/5E7D4C59" Ref="C?"  Part="1" 
F 0 "C4" H 6865 4646 50  0000 L CNN
F 1 "1uF" H 6865 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6788 4450 50  0001 C CNN
F 3 "~" H 6750 4600 50  0001 C CNN
F 4 "decoupling" H 6750 4600 50  0001 C CNN "purpose"
	1    6750 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5500 4900 5500
$Comp
L power:GND #PWR?
U 1 1 5E7D4C61
P 3900 5150
AR Path="/5BF2E340/5E7D4C61" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C61" Ref="#PWR0141"  Part="1" 
F 0 "#PWR0141" H 3900 4900 50  0001 C CNN
F 1 "GND" H 3905 4977 50  0000 C CNN
F 2 "" H 3900 5150 50  0001 C CNN
F 3 "" H 3900 5150 50  0001 C CNN
	1    3900 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5E7D4C69
P 3900 5000
AR Path="/5E7D4C69" Ref="C7"  Part="1" 
AR Path="/5BF2E340/5E7D4C69" Ref="C?"  Part="1" 
F 0 "C7" H 4015 5046 50  0000 L CNN
F 1 "2.2nF" H 4015 4955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3938 4850 50  0001 C CNN
F 3 "~" H 3900 5000 50  0001 C CNN
F 4 "reset debounce/protection" H 3900 5000 50  0001 C CNN "purpose"
F 5 "rc time must be faster than boot_ISP" H 3900 5000 50  0001 C CNN "Note"
	1    3900 5000
	1    0    0    -1  
$EndComp
Text Label 6800 6600 2    50   ~ 0
UART_RX
Wire Wire Line
	6300 6600 6800 6600
Wire Wire Line
	6300 5500 6800 5500
Wire Wire Line
	6300 5600 6800 5600
Text Label 4050 5600 0    50   ~ 0
~ISP~
Text Notes 4400 5600 0    50   ~ 0
(boot_~ISP~)
Wire Wire Line
	4250 5800 4900 5800
Wire Wire Line
	4250 5900 4250 5800
Wire Wire Line
	4050 5900 4250 5900
Text Notes 4400 5800 0    50   ~ 0
(USB boot)
Text Notes 4400 5500 0    50   ~ 0
(reset)
Text Label 4400 6500 0    50   ~ 0
SWCLK
Wire Wire Line
	4900 6500 4400 6500
$Comp
L power:GND #PWR?
U 1 1 5E7D4C9E
P 6750 4750
AR Path="/5BF2E340/5E7D4C9E" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C9E" Ref="#PWR0143"  Part="1" 
F 0 "#PWR0143" H 6750 4500 50  0001 C CNN
F 1 "GND" H 6755 4577 50  0000 C CNN
F 2 "" H 6750 4750 50  0001 C CNN
F 3 "" H 6750 4750 50  0001 C CNN
	1    6750 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 5200 5100 4450
Connection ~ 5600 8200
Wire Wire Line
	5600 5200 5500 5200
Wire Wire Line
	5500 5200 5100 5200
Connection ~ 5500 5200
$Comp
L MCU_NXP_LPC:LPC11U37FBD48-401_ U?
U 1 1 5E7D4C16
P 5600 6700
AR Path="/5BF2E340/5E7D4C16" Ref="U?"  Part="1" 
AR Path="/5E7D4C16" Ref="U3"  Part="1" 
F 0 "U3" H 5600 8378 50  0000 C CNN
F 1 "LPC11U37FBD48-401_" H 5600 8287 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 6450 8200 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/LPC11U3X.pdf" H 5600 5225 50  0001 C CNN
	1    5600 6700
	1    0    0    -1  
$EndComp
Text Label 24600 3850 0    50   ~ 0
pwm_1
Wire Wire Line
	24600 3850 25000 3850
Text Label 4400 7700 0    50   ~ 0
pwm_1
Text Label 6800 5500 2    50   ~ 0
pwm_3
Text Label 6800 5600 2    50   ~ 0
pwm_2
Wire Wire Line
	20300 2100 20900 2100
Wire Wire Line
	22050 2450 21400 2450
Connection ~ 22050 2450
Connection ~ 21400 2450
Wire Wire Line
	20900 2100 21400 2100
Connection ~ 20900 2100
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5E7D4B23
P 1000 8100
AR Path="/5BF2E340/5E7D4B23" Ref="J?"  Part="1" 
AR Path="/5E7D4B23" Ref="J2"  Part="1" 
F 0 "J2" H 1000 7700 50  0000 C CNN
F 1 "SWD" H 1050 7800 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 1000 8100 50  0001 C CNN
F 3 "~" H 1000 8100 50  0001 C CNN
	1    1000 8100
	-1   0    0    1   
$EndComp
Text Label 1800 8100 0    50   ~ 0
SWCLK
Text Label 1800 8000 0    50   ~ 0
SWDIO
$Comp
L power:GND #PWR?
U 1 1 5E7D4B1B
P 1250 8200
AR Path="/5BF2E340/5E7D4B1B" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B1B" Ref="#PWR0144"  Part="1" 
F 0 "#PWR0144" H 1250 7950 50  0001 C CNN
F 1 "GND" H 1255 8027 50  0000 C CNN
F 2 "" H 1250 8200 50  0001 C CNN
F 3 "" H 1250 8200 50  0001 C CNN
	1    1250 8200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 8100 2050 8100
Wire Wire Line
	1200 8200 1250 8200
Wire Wire Line
	1200 8000 2050 8000
Text Notes 2100 7600 2    101  Italic 20
Debugging: SWD\n(optional)
$Comp
L Jitter_Components:+3V #PWR?
U 1 1 5E8F9DF0
P 1250 7900
AR Path="/5BF2E340/5E8F9DF0" Ref="#PWR?"  Part="1" 
AR Path="/5E8F9DF0" Ref="#PWR0145"  Part="1" 
F 0 "#PWR0145" H 1250 7750 50  0001 C CNN
F 1 "+3V" H 1265 8073 50  0000 C CNN
F 2 "" H 1250 7900 50  0001 C CNN
F 3 "" H 1250 7900 50  0001 C CNN
	1    1250 7900
	-1   0    0    -1  
$EndComp
Wire Notes Line
	650  4300 650  6900
Wire Notes Line
	650  6900 3050 6900
Wire Notes Line
	3050 6900 3050 4300
Wire Notes Line
	3050 4300 650  4300
Text Notes 750  4550 0    101  Italic 20
USB
Text Notes 1500 4450 0    50   ~ 0
TODO what current value?
Text Notes 18250 600  0    197  ~ 0
Mogelijk handige copy-paste bouwblokjes
Wire Wire Line
	4900 5900 4450 5900
Wire Wire Line
	4450 6000 4900 6000
Text Label 4450 5900 0    50   ~ 0
I2C_SCL
Text Label 4450 6000 0    50   ~ 0
I2C_SDA
Wire Wire Line
	12400 6250 11500 6250
Text Label 10700 6250 0    50   ~ 0
I2C_SCL
Text Label 10700 6350 0    50   ~ 0
I2C_SDA
Text Notes 10700 6800 0    50   ~ 0
5V-based I2C\n\nNOTE: LPC11u is 5v-tolerant for I2C,\nflow sensors are 5V-based, but allow 2.5V as digital high
$Comp
L Device:R R?
U 1 1 5E7905C9
P 11500 6050
AR Path="/5BF2E340/5E7905C9" Ref="R?"  Part="1" 
AR Path="/5E7905C9" Ref="R8"  Part="1" 
F 0 "R8" H 11570 6096 50  0000 L CNN
F 1 "1k5" H 11570 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 11430 6050 50  0001 C CNN
F 3 "~" H 11500 6050 50  0001 C CNN
	1    11500 6050
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0134
U 1 1 5E7918E8
P 2650 4600
F 0 "#PWR0134" H 2650 4450 50  0001 C CNN
F 1 "+5V" H 2665 4773 50  0000 C CNN
F 2 "" H 2650 4600 50  0001 C CNN
F 3 "" H 2650 4600 50  0001 C CNN
	1    2650 4600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0146
U 1 1 5E799208
P 7500 7000
F 0 "#PWR0146" H 7500 6850 50  0001 C CNN
F 1 "+3.3V" H 7515 7173 50  0000 C CNN
F 2 "" H 7500 7000 50  0001 C CNN
F 3 "" H 7500 7000 50  0001 C CNN
	1    7500 7000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0147
U 1 1 5E799D40
P 6850 4450
F 0 "#PWR0147" H 6850 4300 50  0001 C CNN
F 1 "+3.3V" H 6865 4623 50  0000 C CNN
F 2 "" H 6850 4450 50  0001 C CNN
F 3 "" H 6850 4450 50  0001 C CNN
	1    6850 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4450 6750 4450
Wire Wire Line
	6250 4450 6750 4450
Connection ~ 6750 4450
$Comp
L power:+3.3V #PWR0148
U 1 1 5E7A0A90
P 4050 5900
F 0 "#PWR0148" H 4050 5750 50  0001 C CNN
F 1 "+3.3V" H 4065 6073 50  0000 C CNN
F 2 "" H 4050 5900 50  0001 C CNN
F 3 "" H 4050 5900 50  0001 C CNN
	1    4050 5900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0149
U 1 1 5E7A322D
P 11650 5800
F 0 "#PWR0149" H 11650 5650 50  0001 C CNN
F 1 "+5V" H 11665 5973 50  0000 C CNN
F 2 "" H 11650 5800 50  0001 C CNN
F 3 "" H 11650 5800 50  0001 C CNN
	1    11650 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E7A3A03
P 11850 6050
AR Path="/5BF2E340/5E7A3A03" Ref="R?"  Part="1" 
AR Path="/5E7A3A03" Ref="R9"  Part="1" 
F 0 "R9" H 11920 6096 50  0000 L CNN
F 1 "1k5" H 11920 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 11780 6050 50  0001 C CNN
F 3 "~" H 11850 6050 50  0001 C CNN
	1    11850 6050
	-1   0    0    1   
$EndComp
Connection ~ 11500 6250
Wire Wire Line
	11500 6250 10700 6250
Wire Wire Line
	11500 6200 11500 6250
Wire Wire Line
	10700 6350 11850 6350
Wire Wire Line
	11850 6200 11850 6350
Connection ~ 11850 6350
Wire Wire Line
	11850 6350 12400 6350
Wire Wire Line
	11650 5800 11650 5900
Wire Wire Line
	11650 5900 11500 5900
Wire Wire Line
	11650 5900 11850 5900
Connection ~ 11650 5900
Text Notes 12350 -550 0    118  ~ 24
TODO flow sensor
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5E7CEF83
P 3450 5600
AR Path="/5BF2E340/5E7CEF83" Ref="J?"  Part="1" 
AR Path="/5E7CEF83" Ref="J4"  Part="1" 
F 0 "J4" H 3450 5300 50  0000 C CNN
F 1 "DNI" H 3450 5400 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 3450 5600 50  0001 C CNN
F 3 "~" H 3450 5600 50  0001 C CNN
	1    3450 5600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7CFA00
P 3650 5700
AR Path="/5BF2E340/5E7CFA00" Ref="#PWR?"  Part="1" 
AR Path="/5E7CFA00" Ref="#PWR0150"  Part="1" 
F 0 "#PWR0150" H 3650 5450 50  0001 C CNN
F 1 "GND" H 3655 5527 50  0000 C CNN
F 2 "" H 3650 5700 50  0001 C CNN
F 3 "" H 3650 5700 50  0001 C CNN
	1    3650 5700
	1    0    0    -1  
$EndComp
Text Label 4050 5500 0    50   ~ 0
~RESET~
Wire Wire Line
	4350 5500 3650 5500
Connection ~ 4350 5500
Wire Wire Line
	4350 4850 4350 5500
Text Notes 4550 10800 0    118  ~ 0
TODO\n\n- footprints voor sensors\n- extra on/off outputs (voltage? maybe relays?)\n- RPI hat board outline + Mouning holes\n- test points\n- I2C addr conflict check\n- ADC in header\n- GPIO header\n- 24V to 5V DC/DC? Or 5VDC from separate rpi PSU?
Wire Wire Line
	1250 7900 1200 7900
$Comp
L power:+5V #PWR08
U 1 1 5E818833
P 5500 1850
F 0 "#PWR08" H 5500 1700 50  0001 C CNN
F 1 "+5V" H 5515 2023 50  0000 C CNN
F 2 "" H 5500 1850 50  0001 C CNN
F 3 "" H 5500 1850 50  0001 C CNN
	1    5500 1850
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5E818998
P 5850 2000
AR Path="/5BF2E340/5E818998" Ref="J?"  Part="1" 
AR Path="/5E818998" Ref="J6"  Part="1" 
F 0 "J6" H 5850 1650 50  0000 C CNN
F 1 "5V out" H 5900 1750 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 5850 2000 50  0001 C CNN
F 3 "~" H 5850 2000 50  0001 C CNN
	1    5850 2000
	1    0    0    1   
$EndComp
Wire Wire Line
	5650 1900 5500 1900
Wire Wire Line
	5500 1900 5500 1850
$Comp
L power:GND #PWR?
U 1 1 5E81FD71
P 5500 2000
AR Path="/5BF2E340/5E81FD71" Ref="#PWR?"  Part="1" 
AR Path="/5E81FD71" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 5500 1750 50  0001 C CNN
F 1 "GND" H 5505 1827 50  0000 C CNN
F 2 "" H 5500 2000 50  0001 C CNN
F 3 "" H 5500 2000 50  0001 C CNN
	1    5500 2000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5500 2000 5650 2000
Text Notes 5450 1550 0    50   ~ 0
5V out\n(RPI display?)
Text Notes 10250 1000 0    118  ~ 24
Pressure regulator (RP200_C_???)\n
$Comp
L Jitter_Components:AD5410AREZ U7
U 1 1 5E83CBD0
P 12050 3700
F 0 "U7" H 12550 5400 50  0000 C CNN
F 1 "AD5410AREZ" H 12750 5300 50  0000 C CNN
F 2 "Jitter_Footprints:TSSOP-24-1EP_4.4x7.8mm_P0.65mm" H 12050 3700 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/AD5410_5420.pdf" H 12050 3700 50  0001 C CNN
F 4 "AD5410AREZ" H 12800 5439 50  0001 C CNN "MPN"
	1    12050 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C23
U 1 1 5E83E06B
P 13750 2250
AR Path="/5E83E06B" Ref="C23"  Part="1" 
AR Path="/5BF2E340/5E83E06B" Ref="C?"  Part="1" 
F 0 "C23" H 13865 2296 50  0000 L CNN
F 1 "10nF" H 13865 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 13788 2100 50  0001 C CNN
F 3 "~" H 13750 2250 50  0001 C CNN
F 4 "Iout slew rate limit: rise time 0.2ms @ 10nF" H 13750 2250 50  0001 C CNN "purpose"
	1    13750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	13650 2400 13750 2400
Wire Wire Line
	13750 2100 13750 2050
Wire Wire Line
	13750 2050 13200 2050
$Comp
L power:+24V #PWR02
U 1 1 5E84C803
P 14600 1300
F 0 "#PWR02" H 14600 1150 50  0001 C CNN
F 1 "+24V" H 14615 1473 50  0000 C CNN
F 2 "" H 14600 1300 50  0001 C CNN
F 3 "" H 14600 1300 50  0001 C CNN
	1    14600 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C20
U 1 1 5E84D16F
P 13550 1450
AR Path="/5E84D16F" Ref="C20"  Part="1" 
AR Path="/5BF2E340/5E84D16F" Ref="C?"  Part="1" 
F 0 "C20" H 13665 1496 50  0000 L CNN
F 1 "100nF 50V" H 13665 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 13588 1300 50  0001 C CNN
F 3 "~" H 13550 1450 50  0001 C CNN
F 4 "" H 13550 1450 50  0001 C CNN "purpose"
	1    13550 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C21
U 1 1 5E84D777
P 14250 1450
AR Path="/5E84D777" Ref="C21"  Part="1" 
AR Path="/5BF2E340/5E84D777" Ref="C?"  Part="1" 
F 0 "C21" H 14365 1496 50  0000 L CNN
F 1 "10uF 50V" H 14365 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 14288 1300 50  0001 C CNN
F 3 "~" H 14250 1450 50  0001 C CNN
	1    14250 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E85CC2D
P 13550 1600
AR Path="/5BF2E340/5E85CC2D" Ref="#PWR?"  Part="1" 
AR Path="/5E85CC2D" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 13550 1350 50  0001 C CNN
F 1 "GND" H 13555 1427 50  0000 C CNN
F 2 "" H 13550 1600 50  0001 C CNN
F 3 "" H 13550 1600 50  0001 C CNN
	1    13550 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E86A530
P 14250 1600
AR Path="/5BF2E340/5E86A530" Ref="#PWR?"  Part="1" 
AR Path="/5E86A530" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 14250 1350 50  0001 C CNN
F 1 "GND" H 14255 1427 50  0000 C CNN
F 2 "" H 14250 1600 50  0001 C CNN
F 3 "" H 14250 1600 50  0001 C CNN
	1    14250 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	13200 1300 13200 2050
Connection ~ 13200 2050
Connection ~ 13550 1300
Wire Wire Line
	13550 1300 13200 1300
Connection ~ 14250 1300
Wire Wire Line
	14250 1300 14600 1300
Wire Wire Line
	13550 1300 14250 1300
$Comp
L Device:C C15
U 1 1 5E8871AC
P 11850 1450
AR Path="/5E8871AC" Ref="C15"  Part="1" 
AR Path="/5BF2E340/5E8871AC" Ref="C?"  Part="1" 
F 0 "C15" H 11965 1496 50  0000 L CNN
F 1 "100nF" H 11965 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 11888 1300 50  0001 C CNN
F 3 "~" H 11850 1450 50  0001 C CNN
F 4 "" H 11850 1450 50  0001 C CNN "purpose"
	1    11850 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	12350 2050 12350 1300
Wire Wire Line
	12350 1300 11850 1300
Connection ~ 11850 1300
$Comp
L power:GND #PWR?
U 1 1 5E8A49F9
P 11850 1600
AR Path="/5BF2E340/5E8A49F9" Ref="#PWR?"  Part="1" 
AR Path="/5E8A49F9" Ref="#PWR04"  Part="1" 
F 0 "#PWR04" H 11850 1350 50  0001 C CNN
F 1 "GND" H 11855 1427 50  0000 C CNN
F 2 "" H 11850 1600 50  0001 C CNN
F 3 "" H 11850 1600 50  0001 C CNN
	1    11850 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E8A4DB1
P 11400 1600
AR Path="/5BF2E340/5E8A4DB1" Ref="#PWR?"  Part="1" 
AR Path="/5E8A4DB1" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 11400 1350 50  0001 C CNN
F 1 "GND" H 11405 1427 50  0000 C CNN
F 2 "" H 11400 1600 50  0001 C CNN
F 3 "" H 11400 1600 50  0001 C CNN
	1    11400 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 5E8A5CA0
P 11150 1300
F 0 "#PWR01" H 11150 1150 50  0001 C CNN
F 1 "+3.3V" H 11165 1473 50  0000 C CNN
F 2 "" H 11150 1300 50  0001 C CNN
F 3 "" H 11150 1300 50  0001 C CNN
	1    11150 1300
	1    0    0    -1  
$EndComp
NoConn ~ 13650 2500
$Comp
L power:+3.3V #PWR015
U 1 1 5E8C166C
P 10950 2900
F 0 "#PWR015" H 10950 2750 50  0001 C CNN
F 1 "+3.3V" H 10965 3073 50  0000 C CNN
F 2 "" H 10950 2900 50  0001 C CNN
F 3 "" H 10950 2900 50  0001 C CNN
	1    10950 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E8C190F
P 10950 3050
AR Path="/5BF2E340/5E8C190F" Ref="R?"  Part="1" 
AR Path="/5E8C190F" Ref="R10"  Part="1" 
F 0 "R10" H 11020 3096 50  0000 L CNN
F 1 "10k" H 11020 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10880 3050 50  0001 C CNN
F 3 "~" H 10950 3050 50  0001 C CNN
	1    10950 3050
	-1   0    0    1   
$EndComp
Connection ~ 10950 3200
Wire Wire Line
	10950 3200 10350 3200
Wire Wire Line
	10950 3200 11950 3200
Wire Wire Line
	11950 2500 11150 2500
Text Label 11150 2500 0    50   ~ 0
PREG_SPI_~CS~
Wire Wire Line
	11950 2600 11150 2600
Text Label 11150 2600 0    50   ~ 0
PREG_SPI_CLK
Wire Wire Line
	11950 2700 11150 2700
Text Label 11150 2700 0    50   ~ 0
PREG_SPI_MOSI
Wire Wire Line
	11950 2800 11150 2800
Text Label 11150 2800 0    50   ~ 0
PREG_SPI_MISO
Text Label 10350 3200 0    50   ~ 0
PREG_OK
Wire Wire Line
	11950 3000 11150 3000
Text Label 11150 3000 0    50   ~ 0
PREG_CLEAR
$Comp
L Device:R R?
U 1 1 5E9117F5
P 11850 3550
AR Path="/5BF2E340/5E9117F5" Ref="R?"  Part="1" 
AR Path="/5E9117F5" Ref="R11"  Part="1" 
F 0 "R11" H 11920 3596 50  0000 L CNN
F 1 "0" H 11920 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 11780 3550 50  0001 C CNN
F 3 "~" H 11850 3550 50  0001 C CNN
	1    11850 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	11950 3400 11850 3400
Wire Wire Line
	11850 3700 11850 3800
Wire Wire Line
	11850 3800 12050 3800
Connection ~ 12250 3800
Wire Wire Line
	12250 3800 12350 3800
Connection ~ 12350 3800
Wire Wire Line
	12350 3800 12450 3800
Connection ~ 12450 3800
Wire Wire Line
	12450 3800 12550 3800
Connection ~ 12550 3800
Wire Wire Line
	12550 3800 12650 3800
Connection ~ 12650 3800
Wire Wire Line
	12650 3800 12750 3800
$Comp
L power:GND #PWR?
U 1 1 5E9231FF
P 12050 3800
AR Path="/5BF2E340/5E9231FF" Ref="#PWR?"  Part="1" 
AR Path="/5E9231FF" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 12050 3550 50  0001 C CNN
F 1 "GND" H 12055 3627 50  0000 C CNN
F 2 "" H 12050 3800 50  0001 C CNN
F 3 "" H 12050 3800 50  0001 C CNN
	1    12050 3800
	1    0    0    -1  
$EndComp
Connection ~ 12050 3800
Wire Wire Line
	12050 3800 12250 3800
NoConn ~ 13250 3800
NoConn ~ 13650 2900
NoConn ~ 13650 2700
$Comp
L power:GND #PWR?
U 1 1 5E947859
P 15450 3250
AR Path="/5BF2E340/5E947859" Ref="#PWR?"  Part="1" 
AR Path="/5E947859" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 15450 3000 50  0001 C CNN
F 1 "GND" H 15455 3077 50  0000 C CNN
F 2 "" H 15450 3250 50  0001 C CNN
F 3 "" H 15450 3250 50  0001 C CNN
	1    15450 3250
	1    0    0    -1  
$EndComp
Text Notes 14700 3000 2    50   ~ 0
4-20mA output
Wire Wire Line
	13650 3300 13750 3300
Wire Wire Line
	13750 3300 13750 3400
Wire Wire Line
	13750 3400 13650 3400
$Comp
L Device:C C26
U 1 1 5E965538
P 13750 3550
AR Path="/5E965538" Ref="C26"  Part="1" 
AR Path="/5BF2E340/5E965538" Ref="C?"  Part="1" 
F 0 "C26" H 13865 3596 50  0000 L CNN
F 1 "100nF" H 13865 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 13788 3400 50  0001 C CNN
F 3 "~" H 13750 3550 50  0001 C CNN
F 4 "" H 13750 3550 50  0001 C CNN "purpose"
	1    13750 3550
	1    0    0    -1  
$EndComp
Connection ~ 13750 3400
$Comp
L power:GND #PWR?
U 1 1 5E965E98
P 13750 3700
AR Path="/5BF2E340/5E965E98" Ref="#PWR?"  Part="1" 
AR Path="/5E965E98" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 13750 3450 50  0001 C CNN
F 1 "GND" H 13755 3527 50  0000 C CNN
F 2 "" H 13750 3700 50  0001 C CNN
F 3 "" H 13750 3700 50  0001 C CNN
	1    13750 3700
	1    0    0    -1  
$EndComp
NoConn ~ 13050 3800
NoConn ~ 12950 3800
Text Label 14700 4400 2    50   ~ 0
I_PREG_FEEDBACK
Wire Wire Line
	14700 4400 13950 4400
$Comp
L Device:R R?
U 1 1 5E983BE1
P 13800 4400
AR Path="/5BF2E340/5E983BE1" Ref="R?"  Part="1" 
AR Path="/5E983BE1" Ref="R13"  Part="1" 
F 0 "R13" V 14000 4400 50  0000 L CNN
F 1 "0" V 13900 4400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 13730 4400 50  0001 C CNN
F 3 "~" H 13800 4400 50  0001 C CNN
	1    13800 4400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E984032
P 13500 4700
AR Path="/5BF2E340/5E984032" Ref="#PWR?"  Part="1" 
AR Path="/5E984032" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 13500 4450 50  0001 C CNN
F 1 "GND" H 13505 4527 50  0000 C CNN
F 2 "" H 13500 4700 50  0001 C CNN
F 3 "" H 13500 4700 50  0001 C CNN
	1    13500 4700
	1    0    0    -1  
$EndComp
Text Notes 14700 4300 2    50   ~ 0
4-20mA input
$Comp
L Device:R R?
U 1 1 5E9C3489
P 13500 4550
AR Path="/5BF2E340/5E9C3489" Ref="R?"  Part="1" 
AR Path="/5E9C3489" Ref="R15"  Part="1" 
F 0 "R15" H 13570 4596 50  0000 L CNN
F 1 "150" H 13570 4505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 13430 4550 50  0001 C CNN
F 3 "~" H 13500 4550 50  0001 C CNN
F 4 "Current-to-voltage scaling" H 13500 4550 50  0001 C CNN "Reason"
	1    13500 4550
	-1   0    0    1   
$EndComp
Wire Wire Line
	13650 4400 13500 4400
Wire Wire Line
	13500 4400 13300 4400
Connection ~ 13500 4400
Text Label 14700 3100 2    50   ~ 0
I_PREG_SETPOINT
Text Label 11450 4400 0    50   ~ 0
A_PREG_PRESSURE
Text Notes 11450 4800 0    50   ~ 0
4-20mA -> 0.6-3.0V\nLowpass filter:\n10k, 10nF = 1.6kHz
$Comp
L Device:R R?
U 1 1 5E9EF82C
P 13150 4400
AR Path="/5BF2E340/5E9EF82C" Ref="R?"  Part="1" 
AR Path="/5E9EF82C" Ref="R12"  Part="1" 
F 0 "R12" V 13350 4400 50  0000 L CNN
F 1 "10k" V 13250 4400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 13080 4400 50  0001 C CNN
F 3 "~" H 13150 4400 50  0001 C CNN
	1    13150 4400
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C27
U 1 1 5E9F9D99
P 12400 4550
AR Path="/5E9F9D99" Ref="C27"  Part="1" 
AR Path="/5BF2E340/5E9F9D99" Ref="C?"  Part="1" 
F 0 "C27" H 12515 4596 50  0000 L CNN
F 1 "10nF" H 12515 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 12438 4400 50  0001 C CNN
F 3 "~" H 12400 4550 50  0001 C CNN
F 4 "Iout slew rate limit: rise time 0.2ms @ 10nF" H 12400 4550 50  0001 C CNN "purpose"
	1    12400 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EA0566C
P 12400 4700
AR Path="/5BF2E340/5EA0566C" Ref="#PWR?"  Part="1" 
AR Path="/5EA0566C" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 12400 4450 50  0001 C CNN
F 1 "GND" H 12405 4527 50  0000 C CNN
F 2 "" H 12400 4700 50  0001 C CNN
F 3 "" H 12400 4700 50  0001 C CNN
	1    12400 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 2100 8950 2100
Text Label 8950 2100 0    50   ~ 0
PREG_SPI_~CS~
Wire Wire Line
	9750 1500 8950 1500
Text Label 8950 1500 0    50   ~ 0
PREG_SPI_CLK
Wire Wire Line
	9750 1600 8950 1600
Text Label 8950 1600 0    50   ~ 0
PREG_SPI_MOSI
Wire Wire Line
	9750 1700 8950 1700
Text Label 8950 1700 0    50   ~ 0
PREG_SPI_MISO
Wire Wire Line
	9750 2200 8950 2200
Text Label 8950 2200 0    50   ~ 0
PREG_CLEAR
Text Label 8950 2300 0    50   ~ 0
PREG_OK
Wire Wire Line
	8950 2300 9750 2300
Text Label 8950 2600 0    50   ~ 0
A_PREG_PRESSURE
Wire Wire Line
	8950 2600 9750 2600
Text Notes 9000 1950 0    50   ~ 0
GPIO
Text Notes 9000 1400 0    50   ~ 0
SPI
Text Notes 8950 2500 0    50   ~ 0
ADC
$Comp
L Device:R R?
U 1 1 5EAAB98D
P 12800 4550
AR Path="/5BF2E340/5EAAB98D" Ref="R?"  Part="1" 
AR Path="/5EAAB98D" Ref="R14"  Part="1" 
F 0 "R14" H 12900 4500 50  0000 L CNN
F 1 "DNI" H 12900 4600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 12730 4550 50  0001 C CNN
F 3 "~" H 12800 4550 50  0001 C CNN
	1    12800 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EAAC162
P 12800 4700
AR Path="/5BF2E340/5EAAC162" Ref="#PWR?"  Part="1" 
AR Path="/5EAAC162" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 12800 4450 50  0001 C CNN
F 1 "GND" H 12805 4527 50  0000 C CNN
F 2 "" H 12800 4700 50  0001 C CNN
F 3 "" H 12800 4700 50  0001 C CNN
	1    12800 4700
	1    0    0    -1  
$EndComp
Connection ~ 12800 4400
Wire Wire Line
	12800 4400 13000 4400
Connection ~ 12400 4400
Wire Wire Line
	12400 4400 11450 4400
Wire Wire Line
	12400 4400 12800 4400
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5EAC584F
P 11000 10500
F 0 "H2" H 11100 10505 50  0000 L CNN
F 1 "DNI (mounting hole)" H 11100 10460 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad_Via" H 11000 10500 50  0001 C CNN
F 3 "~" H 11000 10500 50  0001 C CNN
	1    11000 10500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5EAC5855
P 11000 10600
F 0 "#PWR022" H 11000 10350 50  0001 C CNN
F 1 "GND" H 11005 10427 50  0000 C CNN
F 2 "" H 11000 10600 50  0001 C CNN
F 3 "" H 11000 10600 50  0001 C CNN
	1    11000 10600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5EAD36B5
P 15700 3100
AR Path="/5BF2E340/5EAD36B5" Ref="J?"  Part="1" 
AR Path="/5EAD36B5" Ref="J8"  Part="1" 
F 0 "J8" H 15700 2800 50  0000 C CNN
F 1 "TODO" H 15700 2900 50  0000 C CNN
F 2 "" H 15700 3100 50  0001 C CNN
F 3 "~" H 15700 3100 50  0001 C CNN
	1    15700 3100
	1    0    0    1   
$EndComp
Wire Wire Line
	15450 3250 15450 3200
Wire Wire Line
	15450 3200 15500 3200
Text Label 14850 3000 0    50   ~ 0
I_PREG_FEEDBACK
Wire Wire Line
	14850 3000 15500 3000
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5EB10B69
P 15700 2350
AR Path="/5BF2E340/5EB10B69" Ref="J?"  Part="1" 
AR Path="/5EB10B69" Ref="J7"  Part="1" 
F 0 "J7" H 15700 2050 50  0000 C CNN
F 1 "TODO" H 15700 2150 50  0000 C CNN
F 2 "" H 15700 2350 50  0001 C CNN
F 3 "~" H 15700 2350 50  0001 C CNN
	1    15700 2350
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EB11B37
P 15450 2400
AR Path="/5BF2E340/5EB11B37" Ref="#PWR?"  Part="1" 
AR Path="/5EB11B37" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 15450 2150 50  0001 C CNN
F 1 "GND" H 15455 2227 50  0000 C CNN
F 2 "" H 15450 2400 50  0001 C CNN
F 3 "" H 15450 2400 50  0001 C CNN
	1    15450 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	15450 2400 15450 2350
Wire Wire Line
	15450 2350 15500 2350
$Comp
L Device:C C24
U 1 1 5EB202AF
P 14850 2250
AR Path="/5EB202AF" Ref="C24"  Part="1" 
AR Path="/5BF2E340/5EB202AF" Ref="C?"  Part="1" 
F 0 "C24" H 14965 2296 50  0000 L CNN
F 1 "100nF 50V" H 14965 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 14888 2100 50  0001 C CNN
F 3 "~" H 14850 2250 50  0001 C CNN
F 4 "" H 14850 2250 50  0001 C CNN "purpose"
	1    14850 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EB202B5
P 14850 2400
AR Path="/5BF2E340/5EB202B5" Ref="#PWR?"  Part="1" 
AR Path="/5EB202B5" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 14850 2150 50  0001 C CNN
F 1 "GND" H 14855 2227 50  0000 C CNN
F 2 "" H 14850 2400 50  0001 C CNN
F 3 "" H 14850 2400 50  0001 C CNN
	1    14850 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR07
U 1 1 5EB39194
P 1900 1750
F 0 "#PWR07" H 1900 1600 50  0001 C CNN
F 1 "+24V" H 1915 1923 50  0000 C CNN
F 2 "" H 1900 1750 50  0001 C CNN
F 3 "" H 1900 1750 50  0001 C CNN
	1    1900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	15450 2250 15500 2250
Text Notes 15800 1950 2    50   ~ 0
24VDC 1.5A \nOUTPUT
Text Notes 950  2650 0    79   ~ 16
3.3V LDO
$Comp
L Device:C C14
U 1 1 5EB8C837
P 11400 1450
AR Path="/5EB8C837" Ref="C14"  Part="1" 
AR Path="/5BF2E340/5EB8C837" Ref="C?"  Part="1" 
F 0 "C14" H 11515 1496 50  0000 L CNN
F 1 "10uF" H 11515 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 11438 1300 50  0001 C CNN
F 3 "~" H 11400 1450 50  0001 C CNN
	1    11400 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	11150 1300 11400 1300
Connection ~ 11400 1300
Wire Wire Line
	11400 1300 11850 1300
Wire Wire Line
	3900 4850 4350 4850
Wire Wire Line
	15450 2100 14850 2100
Wire Wire Line
	15450 2100 15450 2250
Connection ~ 14850 2100
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5EBE6F1F
P 1100 2000
AR Path="/5BF2E340/5EBE6F1F" Ref="J?"  Part="1" 
AR Path="/5EBE6F1F" Ref="J5"  Part="1" 
F 0 "J5" H 1100 1700 50  0000 C CNN
F 1 "TODO" H 1100 1800 50  0000 C CNN
F 2 "" H 1100 2000 50  0001 C CNN
F 3 "~" H 1100 2000 50  0001 C CNN
	1    1100 2000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EBE6F25
P 1350 2050
AR Path="/5BF2E340/5EBE6F25" Ref="#PWR?"  Part="1" 
AR Path="/5EBE6F25" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 1350 1800 50  0001 C CNN
F 1 "GND" H 1355 1877 50  0000 C CNN
F 2 "" H 1350 2050 50  0001 C CNN
F 3 "" H 1350 2050 50  0001 C CNN
	1    1350 2050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1350 2050 1350 2000
Wire Wire Line
	1350 2000 1300 2000
Wire Wire Line
	1350 1900 1300 1900
Wire Wire Line
	1350 1750 1350 1900
Text Notes 950  1500 0    50   ~ 0
24VDC 3A
$Comp
L Device:CP C22
U 1 1 5EC02FDC
P 1650 1900
F 0 "C22" H 1768 1946 50  0000 L CNN
F 1 "330uF" H 1768 1855 50  0000 L CNN
F 2 "Jitter_Footprints:CP_Elec_12.5x13.5" H 1688 1750 50  0001 C CNN
F 3 "~" H 1650 1900 50  0001 C CNN
F 4 "MAL214699107E3" H 1650 1900 50  0001 C CNN "MPN"
F 5 "generic bulk capacitor (value not determined)" H 1650 1900 50  0001 C CNN "Purpose"
	1    1650 1900
	1    0    0    -1  
$EndComp
Connection ~ 1650 1750
Wire Wire Line
	1650 1750 1900 1750
$Comp
L power:GND #PWR?
U 1 1 5EC03751
P 1650 2050
AR Path="/5BF2E340/5EC03751" Ref="#PWR?"  Part="1" 
AR Path="/5EC03751" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 1650 1800 50  0001 C CNN
F 1 "GND" H 1655 1877 50  0000 C CNN
F 2 "" H 1650 2050 50  0001 C CNN
F 3 "" H 1650 2050 50  0001 C CNN
	1    1650 2050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	14550 2100 14850 2100
Wire Wire Line
	1350 1750 1650 1750
$Comp
L power:+24V #PWR012
U 1 1 5EC9A4D0
P 14550 2100
F 0 "#PWR012" H 14550 1950 50  0001 C CNN
F 1 "+24V" H 14565 2273 50  0000 C CNN
F 2 "" H 14550 2100 50  0001 C CNN
F 3 "" H 14550 2100 50  0001 C CNN
	1    14550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	13650 3100 15500 3100
Wire Notes Line
	10100 700  15900 700 
Wire Notes Line
	15900 700  15900 5050
Wire Notes Line
	15900 5050 10100 5050
Wire Notes Line
	10100 5050 10100 700 
Wire Wire Line
	6650 7300 6300 7300
Wire Wire Line
	6300 7400 6650 7400
Text Label 6350 7300 0    50   ~ 0
MCU_DP
Text Label 6350 7400 0    50   ~ 0
MCU_DM
Connection ~ 7300 7300
Wire Wire Line
	7300 7300 7750 7300
Wire Wire Line
	6950 7300 7300 7300
Wire Wire Line
	7500 7000 7300 7000
Text Notes 3000 2050 0    79   ~ 16
TODO 24V 1.5A -> 5V3A
Wire Wire Line
	2700 3000 2900 3000
Connection ~ 2700 3000
$Comp
L Connector:TestPoint TP?
U 1 1 5EB90431
P 2700 3000
AR Path="/5BF2E340/5EB90431" Ref="TP?"  Part="1" 
AR Path="/5C00B45C/5EB90431" Ref="TP?"  Part="1" 
AR Path="/5EB90431" Ref="TP5"  Part="1" 
F 0 "TP5" H 2750 3150 50  0000 L CNN
F 1 "5V" H 2750 3150 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 2900 3000 50  0001 C CNN
F 3 "~" H 2900 3000 50  0001 C CNN
	1    2700 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3000 2700 3000
Wire Wire Line
	1300 3000 1650 3000
Connection ~ 1300 3000
$Comp
L Connector:TestPoint TP?
U 1 1 5EB8D8BA
P 1300 3000
AR Path="/5BF2E340/5EB8D8BA" Ref="TP?"  Part="1" 
AR Path="/5C00B45C/5EB8D8BA" Ref="TP?"  Part="1" 
AR Path="/5EB8D8BA" Ref="TP1"  Part="1" 
F 0 "TP1" H 1350 3150 50  0000 L CNN
F 1 "5V" H 1350 3150 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 1500 3000 50  0001 C CNN
F 3 "~" H 1500 3000 50  0001 C CNN
	1    1300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3000 3200 3000
Connection ~ 2900 3000
$Comp
L Device:C C25
U 1 1 5EB8B968
P 2900 3150
AR Path="/5EB8B968" Ref="C25"  Part="1" 
AR Path="/5BF2E340/5EB8B968" Ref="C?"  Part="1" 
F 0 "C25" H 3015 3196 50  0000 L CNN
F 1 "10uF" H 3015 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2938 3000 50  0001 C CNN
F 3 "~" H 2900 3150 50  0001 C CNN
	1    2900 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 3000 1300 3000
Wire Wire Line
	1650 3000 1950 3000
Connection ~ 1650 3000
$Comp
L Regulator_Linear:MCP1825S U4
U 1 1 5EB573F3
P 2250 3000
F 0 "U4" H 2250 3242 50  0000 C CNN
F 1 "MCP1825S" H 2250 3151 50  0000 C CNN
F 2 "" H 2150 3150 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/devicedoc/22056b.pdf" H 2250 3250 50  0001 C CNN
	1    2250 3000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0142
U 1 1 5E793A52
P 3200 3000
F 0 "#PWR0142" H 3200 2850 50  0001 C CNN
F 1 "+3.3V" H 3215 3173 50  0000 C CNN
F 2 "" H 3200 3000 50  0001 C CNN
F 3 "" H 3200 3000 50  0001 C CNN
	1    3200 3000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0138
U 1 1 5E792173
P 1050 3000
F 0 "#PWR0138" H 1050 2850 50  0001 C CNN
F 1 "+5V" H 1065 3173 50  0000 C CNN
F 2 "" H 1050 3000 50  0001 C CNN
F 3 "" H 1050 3000 50  0001 C CNN
	1    1050 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5E77C008
P 1650 3150
AR Path="/5E77C008" Ref="C13"  Part="1" 
AR Path="/5BF2E340/5E77C008" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E77C008" Ref="C?"  Part="1" 
AR Path="/5C00B45C/5E77C008" Ref="C?"  Part="1" 
F 0 "C13" H 1765 3196 50  0000 L CNN
F 1 "4.7uF" H 1765 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1688 3000 50  0001 C CNN
F 3 "~" H 1650 3150 50  0001 C CNN
F 4 "decoupling" H 1650 3150 50  0001 C CNN "purpose"
	1    1650 3150
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E77C001
P 1650 3300
AR Path="/5BF2E340/5E77C001" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E77C001" Ref="#PWR?"  Part="1" 
AR Path="/5C00B45C/5E77C001" Ref="#PWR?"  Part="1" 
AR Path="/5E77C001" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 1650 3050 50  0001 C CNN
F 1 "GND" H 1655 3127 50  0000 C CNN
F 2 "" H 1650 3300 50  0001 C CNN
F 3 "" H 1650 3300 50  0001 C CNN
	1    1650 3300
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E77BFF0
P 2900 3300
AR Path="/5BF2E340/5E77BFF0" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E77BFF0" Ref="#PWR?"  Part="1" 
AR Path="/5C00B45C/5E77BFF0" Ref="#PWR?"  Part="1" 
AR Path="/5E77BFF0" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 2900 3050 50  0001 C CNN
F 1 "GND" H 2905 3127 50  0000 C CNN
F 2 "" H 2900 3300 50  0001 C CNN
F 3 "" H 2900 3300 50  0001 C CNN
	1    2900 3300
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E77BFEA
P 2250 3300
AR Path="/5BF2E340/5E77BFEA" Ref="#PWR?"  Part="1" 
AR Path="/5C00B45C/5E77BFEA" Ref="#PWR?"  Part="1" 
AR Path="/5E77BFEA" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 2250 3050 50  0001 C CNN
F 1 "GND" H 2255 3127 50  0000 C CNN
F 2 "" H 2250 3300 50  0001 C CNN
F 3 "" H 2250 3300 50  0001 C CNN
	1    2250 3300
	1    0    0    -1  
$EndComp
Text Notes 950  1400 0    79   ~ 16
Power Input
Text Notes 950  1100 0    118  ~ 24
Power
Wire Notes Line
	800  800  800  3800
Wire Notes Line
	800  3800 6450 3800
Wire Notes Line
	6450 3800 6450 800 
Wire Notes Line
	6450 800  800  800 
Text Notes 10200 5650 0    118  ~ 24
Flow sensor
Text Notes 10200 7650 0    118  ~ 24
Pressure sensor
Text Notes 11350 8450 0    197  ~ 0
TODO
Text Notes 13300 6550 0    197  ~ 0
TODO
Wire Notes Line
	10100 5350 10100 7050
Wire Notes Line
	10100 7050 15900 7050
Wire Notes Line
	15900 7050 15900 5350
Wire Notes Line
	15900 5350 10100 5350
$EndSCHEMATC
