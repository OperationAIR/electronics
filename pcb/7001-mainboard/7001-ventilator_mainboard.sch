EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 2
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
P 2850 10800
F 0 "H1" H 2950 10805 50  0000 L CNN
F 1 "DNI (mounting hole)" H 2950 10760 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad_Via" H 2850 10800 50  0001 C CNN
F 3 "~" H 2850 10800 50  0001 C CNN
	1    2850 10800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5C0E807D
P 2850 10900
F 0 "#PWR0119" H 2850 10650 50  0001 C CNN
F 1 "GND" H 2855 10727 50  0000 C CNN
F 2 "" H 2850 10900 50  0001 C CNN
F 3 "" H 2850 10900 50  0001 C CNN
	1    2850 10900
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
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 1100 5250 50  0001 C CNN
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
	1400 5100 1400 4700
Wire Wire Line
	1400 4700 1650 4700
Wire Wire Line
	1250 5100 1400 5100
$Comp
L Device:C C1
U 1 1 5E7810A7
P 1650 4850
AR Path="/5E7810A7" Ref="C1"  Part="1" 
AR Path="/5C03F077/5E7810A7" Ref="C?"  Part="1" 
F 0 "C1" H 1765 4896 50  0000 L CNN
F 1 "100nF" H 1765 4805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1688 4700 50  0001 C CNN
F 3 "~" H 1650 4850 50  0001 C CNN
	1    1650 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5E7810AD
P 1650 5000
AR Path="/5E7810AD" Ref="#PWR0106"  Part="1" 
AR Path="/5C03F077/5E7810AD" Ref="#PWR?"  Part="1" 
F 0 "#PWR0106" H 1650 4750 50  0001 C CNN
F 1 "GND" H 1655 4827 50  0000 C CNN
F 2 "" H 1650 5000 50  0001 C CNN
F 3 "" H 1650 5000 50  0001 C CNN
	1    1650 5000
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
Wire Wire Line
	2350 4700 1650 4700
Connection ~ 1650 4700
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
Text Notes 18550 2750 0    47   ~ 0
TODO\nWith prototype: tune gate resistor value\nHigher = lower EMC, too high = slow response
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 5E795521
P 19800 3300
AR Path="/5BF41E62/5E795521" Ref="Q?"  Part="1" 
AR Path="/5E795521" Ref="Q1"  Part="1" 
F 0 "Q1" H 19450 3150 50  0000 L CNN
F 1 "IRLML6244TRPbF" H 19200 3050 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 20000 3400 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/196/irlml6244pbf-1228275.pdf" H 19800 3300 50  0001 C CNN
F 4 "30mOhm @Vgs < 3V" H 19800 3300 50  0001 C CNN "Rds(on)"
F 5 "sot-23 footprint nmos, Rds(on) ~ 0.1" H 19800 3300 50  0001 C CNN "alternative"
	1    19800 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E795527
P 20000 3550
AR Path="/5BF41E62/5E795527" Ref="#PWR?"  Part="1" 
AR Path="/5E795527" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 20000 3300 50  0001 C CNN
F 1 "GND" H 20005 3377 50  0000 C CNN
F 2 "" H 20000 3550 50  0001 C CNN
F 3 "" H 20000 3550 50  0001 C CNN
	1    20000 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 5E79552E
P 20900 3250
AR Path="/5E79552E" Ref="C19"  Part="1" 
AR Path="/5BF41E62/5E79552E" Ref="C?"  Part="1" 
F 0 "C19" H 21050 3150 50  0000 L CNN
F 1 "2.2nF" H 21050 3050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 20938 3100 50  0001 C CNN
F 3 "~" H 20900 3250 50  0001 C CNN
F 4 "EMC filter" H 20900 3250 50  0001 C CNN "purpose"
	1    20900 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E795534
P 20900 3400
AR Path="/5E795534" Ref="#PWR0109"  Part="1" 
AR Path="/5BF41E62/5E795534" Ref="#PWR?"  Part="1" 
F 0 "#PWR0109" H 20900 3150 50  0001 C CNN
F 1 "GND" H 20905 3227 50  0000 C CNN
F 2 "" H 20900 3400 50  0001 C CNN
F 3 "" H 20900 3400 50  0001 C CNN
	1    20900 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 5E79553B
P 20900 2550
AR Path="/5E79553B" Ref="C17"  Part="1" 
AR Path="/5BF41E62/5E79553B" Ref="C?"  Part="1" 
F 0 "C17" H 20600 2500 50  0000 L CNN
F 1 "2.2nF" H 20600 2400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 20938 2400 50  0001 C CNN
F 3 "~" H 20900 2550 50  0001 C CNN
F 4 "EMC filter" H 20900 2550 50  0001 C CNN "purpose"
	1    20900 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5E795541
P 20900 2700
AR Path="/5E795541" Ref="#PWR0110"  Part="1" 
AR Path="/5BF41E62/5E795541" Ref="#PWR?"  Part="1" 
F 0 "#PWR0110" H 20900 2450 50  0001 C CNN
F 1 "GND" H 20905 2527 50  0000 C CNN
F 2 "" H 20900 2700 50  0001 C CNN
F 3 "" H 20900 2700 50  0001 C CNN
	1    20900 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	21100 2800 21100 2400
Wire Wire Line
	21100 2900 21100 3100
Wire Wire Line
	21100 3100 20900 3100
Connection ~ 20900 2400
Wire Wire Line
	20900 2400 21100 2400
Connection ~ 20900 3100
Wire Wire Line
	19900 3100 20100 3100
$Comp
L Diode:BZT52Bxx D?
U 1 1 5E795552
P 20100 3250
AR Path="/5BF41E62/5E795552" Ref="D?"  Part="1" 
AR Path="/5E795552" Ref="D1"  Part="1" 
F 0 "D1" V 20054 3329 50  0000 L CNN
F 1 "BZT52C10+" V 20145 3329 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 20100 3075 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzt52b2v4.pdf" H 20100 3250 50  0001 C CNN
F 4 "500mW" V 20100 3250 50  0001 C CNN "Power rating"
F 5 "SOD-123 zener: 7.5-10V, Pd >= 500mW" V 20100 3250 50  0001 C CNN "alternative"
F 6 "10V" V 20100 3250 50  0001 C CNN "Zener voltage"
F 7 "fast discharging of inductive load" V 20100 3250 50  0001 C CNN "purpose"
	1    20100 3250
	0    1    1    0   
$EndComp
Connection ~ 20100 3100
Wire Wire Line
	19900 3500 19900 3550
Wire Wire Line
	19900 3550 20000 3550
Wire Wire Line
	20100 3550 20100 3400
Connection ~ 20000 3550
Wire Wire Line
	20000 3550 20100 3550
$Comp
L Device:R R?
U 1 1 5E79555F
P 19300 3300
AR Path="/5BF41E62/5E79555F" Ref="R?"  Part="1" 
AR Path="/5E79555F" Ref="R6"  Part="1" 
F 0 "R6" V 19093 3300 50  0000 C CNN
F 1 "1k" V 19184 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 19230 3300 50  0001 C CNN
F 3 "~" H 19300 3300 50  0001 C CNN
F 4 "EMC: edge rate limiting" V 19300 3300 50  0001 C CNN "purpose"
	1    19300 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	19450 3300 19500 3300
$Comp
L power:+6V #PWR?
U 1 1 5E795568
P 20750 2400
AR Path="/5BF41E62/5E795568" Ref="#PWR?"  Part="1" 
AR Path="/5E795568" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 20750 2250 50  0001 C CNN
F 1 "+6V" H 20765 2573 50  0000 C CNN
F 2 "" H 20750 2400 50  0001 C CNN
F 3 "" H 20750 2400 50  0001 C CNN
	1    20750 2400
	1    0    0    -1  
$EndComp
Text Notes 18500 2250 0    118  ~ 24
pwm out?
$Comp
L Connector_Generic_MountingPin:Conn_01x02_MountingPin J?
U 1 1 5E79556F
P 21300 2800
AR Path="/5BF41E62/5E79556F" Ref="J?"  Part="1" 
AR Path="/5E79556F" Ref="J3"  Part="1" 
F 0 "J3" H 21387 2670 50  0000 L CNN
F 1 "Conn_01x02_MountingPin" H 21387 2625 50  0001 L CNN
F 2 "Jitter_Footprints:JST_ZH_S2B-ZR-SM4A-TF_1x02-1MP_P1.5mm_Horizontal" H 21300 2800 50  0001 C CNN
F 3 "~" H 21300 2800 50  0001 C CNN
	1    21300 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E795575
P 21300 3100
AR Path="/5E795575" Ref="#PWR0112"  Part="1" 
AR Path="/5BF41E62/5E795575" Ref="#PWR?"  Part="1" 
F 0 "#PWR0112" H 21300 2850 50  0001 C CNN
F 1 "GND" H 21305 2927 50  0000 C CNN
F 2 "" H 21300 3100 50  0001 C CNN
F 3 "" H 21300 3100 50  0001 C CNN
	1    21300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E79559A
P 21800 3000
AR Path="/5BF41E62/5E79559A" Ref="#PWR?"  Part="1" 
AR Path="/5E79559A" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 21800 2750 50  0001 C CNN
F 1 "GND" H 21805 2827 50  0000 C CNN
F 2 "" H 21800 3000 50  0001 C CNN
F 3 "" H 21800 3000 50  0001 C CNN
	1    21800 3000
	1    0    0    -1  
$EndComp
$Comp
L power:+6V #PWR?
U 1 1 5E7955A0
P 21800 2700
AR Path="/5BF41E62/5E7955A0" Ref="#PWR?"  Part="1" 
AR Path="/5E7955A0" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 21800 2550 50  0001 C CNN
F 1 "+6V" H 21815 2873 50  0000 C CNN
F 2 "" H 21800 2700 50  0001 C CNN
F 3 "" H 21800 2700 50  0001 C CNN
	1    21800 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 5E7955A7
P 21800 2850
AR Path="/5E7955A7" Ref="C18"  Part="1" 
AR Path="/5BF2E340/5E7955A7" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7955A7" Ref="C?"  Part="1" 
AR Path="/5BF41E62/5E7955A7" Ref="C?"  Part="1" 
F 0 "C18" H 21915 2896 50  0000 L CNN
F 1 "1uF" H 21915 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 21838 2700 50  0001 C CNN
F 3 "~" H 21800 2850 50  0001 C CNN
F 4 "decoupling" H 21800 2850 50  0001 C CNN "purpose"
	1    21800 2850
	-1   0    0    -1  
$EndComp
Text Notes 18500 4800 0    59   ~ 0
Pull-down resistors: Actuators should be off by default.\n\nWhen the firmware is not running (for example during an update),\nthe microcontroller pins have a 85uA pull-up current enabled.\nThis would cause the actuators to start running unintentionally,\nWe avoid this by placing a strong pull-down resistor:\nR_pulldown = (0.5V/85uA)  -> R_puldown < 5.6k
$Comp
L Device:R R?
U 1 1 5E7955AF
P 19050 3450
AR Path="/5BF41E62/5E7955AF" Ref="R?"  Part="1" 
AR Path="/5E7955AF" Ref="R7"  Part="1" 
F 0 "R7" V 19250 3450 50  0000 C CNN
F 1 "4.7k" V 19150 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 18980 3450 50  0001 C CNN
F 3 "~" H 19050 3450 50  0001 C CNN
F 4 "pull-down: disable actuator by default" V 19050 3450 50  0001 C CNN "purpose"
	1    19050 3450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7955B5
P 19050 3600
AR Path="/5BF41E62/5E7955B5" Ref="#PWR?"  Part="1" 
AR Path="/5E7955B5" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 19050 3350 50  0001 C CNN
F 1 "GND" H 19055 3427 50  0000 C CNN
F 2 "" H 19050 3600 50  0001 C CNN
F 3 "" H 19050 3600 50  0001 C CNN
	1    19050 3600
	1    0    0    -1  
$EndComp
Connection ~ 19050 3300
Wire Wire Line
	19050 3300 19150 3300
$Comp
L Connector:TestPoint TP?
U 1 1 5E7955CC
P 19500 3100
AR Path="/5BF2E340/5E7955CC" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7955CC" Ref="TP?"  Part="1" 
AR Path="/5E7955CC" Ref="TP10"  Part="1" 
F 0 "TP10" H 19550 3350 50  0000 L CNN
F 1 "valve_2_fet" H 19550 3250 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 19700 3100 50  0001 C CNN
F 3 "~" H 19700 3100 50  0001 C CNN
	1    19500 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	19500 3100 19500 3300
Connection ~ 19500 3300
Wire Wire Line
	19500 3300 19600 3300
Wire Wire Line
	20750 2400 20900 2400
Wire Wire Line
	20100 3100 20900 3100
Wire Wire Line
	4950 8300 4950 8450
$Comp
L power:GND #PWR?
U 1 1 5E7D4AE3
P 4950 8450
AR Path="/5BF2E340/5E7D4AE3" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4AE3" Ref="#PWR0132"  Part="1" 
F 0 "#PWR0132" H 4950 8200 50  0001 C CNN
F 1 "GND" H 4955 8277 50  0000 C CNN
F 2 "" H 4950 8450 50  0001 C CNN
F 3 "" H 4950 8450 50  0001 C CNN
	1    4950 8450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4AE9
P 6950 8100
AR Path="/5BF2E340/5E7D4AE9" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4AE9" Ref="#PWR0133"  Part="1" 
F 0 "#PWR0133" H 6950 7850 50  0001 C CNN
F 1 "GND" H 6955 7927 50  0000 C CNN
F 2 "" H 6950 8100 50  0001 C CNN
F 3 "" H 6950 8100 50  0001 C CNN
	1    6950 8100
	1    0    0    -1  
$EndComp
Text Label 3750 7100 0    50   ~ 0
SWDIO
Text Label 7100 7500 2    50   ~ 0
USB_DN
Text Label 7100 7400 2    50   ~ 0
USB_DP
$Comp
L Device:R R?
U 1 1 5E7D4AF3
P 6150 7400
AR Path="/5BF2E340/5E7D4AF3" Ref="R?"  Part="1" 
AR Path="/5E7D4AF3" Ref="R4"  Part="1" 
F 0 "R4" V 6050 7350 50  0000 L CNN
F 1 "33R" V 6150 7350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 7400 50  0001 C CNN
F 3 "~" H 6150 7400 50  0001 C CNN
	1    6150 7400
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E7D4AF9
P 6150 7500
AR Path="/5BF2E340/5E7D4AF9" Ref="R?"  Part="1" 
AR Path="/5E7D4AF9" Ref="R5"  Part="1" 
F 0 "R5" V 6250 7450 50  0000 L CNN
F 1 "33R" V 6150 7450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 7500 50  0001 C CNN
F 3 "~" H 6150 7500 50  0001 C CNN
	1    6150 7500
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 7500 7100 7500
$Comp
L Device:R R?
U 1 1 5E7D4B03
P 6650 7250
AR Path="/5BF2E340/5E7D4B03" Ref="R?"  Part="1" 
AR Path="/5E7D4B03" Ref="R3"  Part="1" 
F 0 "R3" H 6720 7296 50  0000 L CNN
F 1 "1k5" H 6720 7205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6580 7250 50  0001 C CNN
F 3 "~" H 6650 7250 50  0001 C CNN
	1    6650 7250
	-1   0    0    1   
$EndComp
Text Notes 18700 1300 0    101  Italic 20
Actuator control
Wire Wire Line
	4850 8300 4950 8300
Wire Wire Line
	3750 7100 4250 7100
Wire Wire Line
	4250 7800 3750 7800
Text Label 19600 1750 2    50   ~ 0
pwm_1
Text Label 19600 1500 2    50   ~ 0
pwm_2
Text Label 19600 1600 2    50   ~ 0
pwm_3
Text Label 6150 6800 2    50   ~ 0
UART_TX
Wire Notes Line
	18500 1000 20500 1000
Wire Notes Line
	20500 1000 20500 1900
Wire Notes Line
	20500 1900 18500 1900
Wire Notes Line
	18500 1900 18500 1000
$Comp
L power:GND #PWR?
U 1 1 5E7D4B7C
P 6250 8200
AR Path="/5BF2E340/5E7D4B7C" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B7C" Ref="#PWR0135"  Part="1" 
F 0 "#PWR0135" H 6250 7950 50  0001 C CNN
F 1 "GND" H 6255 8027 50  0000 C CNN
F 2 "" H 6250 8200 50  0001 C CNN
F 3 "" H 6250 8200 50  0001 C CNN
	1    6250 8200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4B82
P 6650 8200
AR Path="/5BF2E340/5E7D4B82" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B82" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 6650 7950 50  0001 C CNN
F 1 "GND" H 6655 8027 50  0000 C CNN
F 2 "" H 6650 8200 50  0001 C CNN
F 3 "" H 6650 8200 50  0001 C CNN
	1    6650 8200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 7900 6000 7900
Wire Wire Line
	6000 7900 6000 8600
Wire Wire Line
	6000 8600 6450 8600
Wire Wire Line
	6450 8600 6450 8350
$Comp
L Device:C C12
U 1 1 5E7D4B8D
P 6450 8750
AR Path="/5E7D4B8D" Ref="C12"  Part="1" 
AR Path="/5BF2E340/5E7D4B8D" Ref="C?"  Part="1" 
F 0 "C12" H 6565 8796 50  0000 L CNN
F 1 "18pF" H 6565 8705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6488 8600 50  0001 C CNN
F 3 "~" H 6450 8750 50  0001 C CNN
F 4 "crystal matching (see LPC11u3X datasheet)" H 6450 8750 50  0001 C CNN "purpose"
	1    6450 8750
	1    0    0    -1  
$EndComp
Connection ~ 6450 8600
$Comp
L power:GND #PWR?
U 1 1 5E7D4B94
P 6450 8900
AR Path="/5BF2E340/5E7D4B94" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B94" Ref="#PWR0137"  Part="1" 
F 0 "#PWR0137" H 6450 8650 50  0001 C CNN
F 1 "GND" H 6455 8727 50  0000 C CNN
F 2 "" H 6450 8900 50  0001 C CNN
F 3 "" H 6450 8900 50  0001 C CNN
	1    6450 8900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5E7D4B9B
P 6950 7950
AR Path="/5E7D4B9B" Ref="C10"  Part="1" 
AR Path="/5BF2E340/5E7D4B9B" Ref="C?"  Part="1" 
F 0 "C10" H 7065 7996 50  0000 L CNN
F 1 "18pF" H 7065 7905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6988 7800 50  0001 C CNN
F 3 "~" H 6950 7950 50  0001 C CNN
F 4 "crystal matching (see LPC11u3X datasheet)" H 6950 7950 50  0001 C CNN "purpose"
	1    6950 7950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 7800 6450 8050
Wire Wire Line
	6450 7800 6950 7800
Connection ~ 6450 7800
$Comp
L Device:Crystal_GND24 Y?
U 1 1 5E7D4BA8
P 6450 8200
AR Path="/5BF2E340/5E7D4BA8" Ref="Y?"  Part="1" 
AR Path="/5E7D4BA8" Ref="Y1"  Part="1" 
F 0 "Y1" V 6300 8300 50  0000 L CNN
F 1 "MCSJK-7U-12.00-10-10-80-B-10" V 6750 8350 50  0001 L CNN
F 2 "Crystal:Crystal_SMD_3225-4Pin_3.2x2.5mm" H 6450 8200 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2645227.pdf?_ga=2.101838344.844808790.1542789852-389210046.1542789852" H 6450 8200 50  0001 C CNN
F 4 "10pF" V 6450 8200 50  0001 C CNN "Load capacitance"
F 5 "80 Ohm" V 6450 8200 50  0001 C CNN "ESR"
F 6 "18pF (see LPC11U3XX datasheet)" V 6450 8200 50  0001 C CNN "Required capacitor value"
F 7 "3225-size crystal, ESR<160,see LPC11U3XX datasheet" V 6450 8200 50  0001 C CNN "alternative"
	1    6450 8200
	0    1    1    0   
$EndComp
Text Label 5650 7800 0    50   ~ 0
XTAL_IN
Text Label 5650 7900 0    50   ~ 0
XTAL_OUT
Text Notes 20400 1600 2    50   ~ 0
CT16B0_MAT0
Text Notes 20400 1500 2    50   ~ 0
CT16B0_MAT1
Text Notes 20400 1750 2    50   ~ 0
CT16B1_MAT1
Wire Wire Line
	5650 7800 6450 7800
Wire Wire Line
	5650 6800 6150 6800
Wire Wire Line
	4250 5700 3000 5700
Wire Wire Line
	5150 4600 5600 4600
Connection ~ 5150 4600
$Comp
L power:GND #PWR?
U 1 1 5E7D4C3B
P 5150 4900
AR Path="/5BF2E340/5E7D4C3B" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C3B" Ref="#PWR0139"  Part="1" 
F 0 "#PWR0139" H 5150 4650 50  0001 C CNN
F 1 "GND" H 5155 4727 50  0000 C CNN
F 2 "" H 5150 4900 50  0001 C CNN
F 3 "" H 5150 4900 50  0001 C CNN
	1    5150 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4C41
P 5600 4900
AR Path="/5BF2E340/5E7D4C41" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C41" Ref="#PWR0140"  Part="1" 
F 0 "#PWR0140" H 5600 4650 50  0001 C CNN
F 1 "GND" H 5605 4727 50  0000 C CNN
F 2 "" H 5600 4900 50  0001 C CNN
F 3 "" H 5600 4900 50  0001 C CNN
	1    5600 4900
	1    0    0    -1  
$EndComp
Connection ~ 5600 4600
$Comp
L Device:C C3
U 1 1 5E7D4C4A
P 5600 4750
AR Path="/5E7D4C4A" Ref="C3"  Part="1" 
AR Path="/5BF2E340/5E7D4C4A" Ref="C?"  Part="1" 
F 0 "C3" H 5715 4796 50  0000 L CNN
F 1 "100nF" H 5715 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5638 4600 50  0001 C CNN
F 3 "~" H 5600 4750 50  0001 C CNN
F 4 "decoupling" H 5600 4750 50  0001 C CNN "purpose"
	1    5600 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E7D4C51
P 5150 4750
AR Path="/5E7D4C51" Ref="C2"  Part="1" 
AR Path="/5BF2E340/5E7D4C51" Ref="C?"  Part="1" 
F 0 "C2" H 5265 4796 50  0000 L CNN
F 1 "100nF" H 5265 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5188 4600 50  0001 C CNN
F 3 "~" H 5150 4750 50  0001 C CNN
F 4 "decoupling" H 5150 4750 50  0001 C CNN "purpose"
	1    5150 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 4600 5150 4600
$Comp
L Device:C C4
U 1 1 5E7D4C59
P 6100 4750
AR Path="/5E7D4C59" Ref="C4"  Part="1" 
AR Path="/5BF2E340/5E7D4C59" Ref="C?"  Part="1" 
F 0 "C4" H 6215 4796 50  0000 L CNN
F 1 "1uF" H 6215 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6138 4600 50  0001 C CNN
F 3 "~" H 6100 4750 50  0001 C CNN
F 4 "decoupling" H 6100 4750 50  0001 C CNN "purpose"
	1    6100 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5600 4250 5600
$Comp
L power:GND #PWR?
U 1 1 5E7D4C61
P 3250 5250
AR Path="/5BF2E340/5E7D4C61" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C61" Ref="#PWR0141"  Part="1" 
F 0 "#PWR0141" H 3250 5000 50  0001 C CNN
F 1 "GND" H 3255 5077 50  0000 C CNN
F 2 "" H 3250 5250 50  0001 C CNN
F 3 "" H 3250 5250 50  0001 C CNN
	1    3250 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5E7D4C69
P 3250 5100
AR Path="/5E7D4C69" Ref="C7"  Part="1" 
AR Path="/5BF2E340/5E7D4C69" Ref="C?"  Part="1" 
F 0 "C7" H 3365 5146 50  0000 L CNN
F 1 "2.2nF" H 3365 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3288 4950 50  0001 C CNN
F 3 "~" H 3250 5100 50  0001 C CNN
F 4 "reset debounce/protection" H 3250 5100 50  0001 C CNN "purpose"
F 5 "rc time must be faster than boot_ISP" H 3250 5100 50  0001 C CNN "Note"
	1    3250 5100
	1    0    0    -1  
$EndComp
Text Label 6150 6700 2    50   ~ 0
UART_RX
Wire Wire Line
	5650 6700 6150 6700
Wire Wire Line
	5650 5600 6150 5600
Wire Wire Line
	5650 5700 6150 5700
Text Label 3400 5700 0    50   ~ 0
~ISP~
Text Notes 3750 5700 0    50   ~ 0
(boot_~ISP~)
Wire Wire Line
	3600 5900 4250 5900
Wire Wire Line
	3600 6000 3600 5900
Wire Wire Line
	3400 6000 3600 6000
Text Notes 3750 5900 0    50   ~ 0
(USB boot)
Text Notes 3750 5600 0    50   ~ 0
(reset)
Text Label 3750 6600 0    50   ~ 0
SWCLK
Wire Wire Line
	4250 6600 3750 6600
$Comp
L power:GND #PWR?
U 1 1 5E7D4C9E
P 6100 4900
AR Path="/5BF2E340/5E7D4C9E" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C9E" Ref="#PWR0143"  Part="1" 
F 0 "#PWR0143" H 6100 4650 50  0001 C CNN
F 1 "GND" H 6105 4727 50  0000 C CNN
F 2 "" H 6100 4900 50  0001 C CNN
F 3 "" H 6100 4900 50  0001 C CNN
	1    6100 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 5300 4450 4600
Connection ~ 4950 8300
Wire Wire Line
	4950 5300 4850 5300
Wire Wire Line
	4850 5300 4450 5300
Connection ~ 4850 5300
$Comp
L MCU_NXP_LPC:LPC11U37FBD48-401_ U?
U 1 1 5E7D4C16
P 4950 6800
AR Path="/5BF2E340/5E7D4C16" Ref="U?"  Part="1" 
AR Path="/5E7D4C16" Ref="U3"  Part="1" 
F 0 "U3" H 4950 8478 50  0000 C CNN
F 1 "LPC11U37FBD48-401_" H 4950 8387 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 5800 8300 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/LPC11U3X.pdf" H 4950 5325 50  0001 C CNN
	1    4950 6800
	1    0    0    -1  
$EndComp
Text Label 18650 3300 0    50   ~ 0
pwm_1
Wire Wire Line
	18650 3300 19050 3300
Text Label 3750 7800 0    50   ~ 0
pwm_1
Text Label 6150 5600 2    50   ~ 0
pwm_3
Text Label 6150 5700 2    50   ~ 0
pwm_2
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5E7D4B23
P 800 8000
AR Path="/5BF2E340/5E7D4B23" Ref="J?"  Part="1" 
AR Path="/5E7D4B23" Ref="J2"  Part="1" 
F 0 "J2" H 800 7600 50  0000 C CNN
F 1 "SWD" H 850 7700 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 800 8000 50  0001 C CNN
F 3 "~" H 800 8000 50  0001 C CNN
	1    800  8000
	-1   0    0    1   
$EndComp
Text Label 1600 8000 0    50   ~ 0
SWCLK
Text Label 1600 7900 0    50   ~ 0
SWDIO
$Comp
L power:GND #PWR?
U 1 1 5E7D4B1B
P 1050 8100
AR Path="/5BF2E340/5E7D4B1B" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B1B" Ref="#PWR0144"  Part="1" 
F 0 "#PWR0144" H 1050 7850 50  0001 C CNN
F 1 "GND" H 1055 7927 50  0000 C CNN
F 2 "" H 1050 8100 50  0001 C CNN
F 3 "" H 1050 8100 50  0001 C CNN
	1    1050 8100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 8000 1850 8000
Wire Wire Line
	1000 8100 1050 8100
Wire Wire Line
	1000 7900 1850 7900
Wire Notes Line
	650  4300 650  6900
Wire Notes Line
	2450 6900 2450 4300
Text Notes 750  4550 0    101  Italic 20
USB
Text Notes 4950 3400 0    50   ~ 0
Jumper Option:\n1-2: power 5V from 24V DC/DC\n2-3: power 5V from USB\nNC: power 5V from Raspberry Pi
Text Notes 18250 600  0    197  ~ 0
Mogelijk handige copy-paste bouwblokjes
Wire Wire Line
	4250 6000 3800 6000
Wire Wire Line
	3800 6100 4250 6100
Text Label 3800 6000 0    50   ~ 0
I2C_SCL
Text Label 3800 6100 0    50   ~ 0
I2C_SDA
Wire Wire Line
	14900 6400 14000 6400
Text Label 13200 6400 0    50   ~ 0
I2C_SCL
Text Label 13200 6500 0    50   ~ 0
I2C_SDA
Text Notes 13200 6850 0    50   ~ 0
NOTE: LPC11u is 5v-tolerant for I2C,\nflow sensors are 5V-based, but allow 2.5V as digital high,\npressure sensor is 3.3V-based, unknown if 5V-tolerant
$Comp
L Device:R R?
U 1 1 5E7905C9
P 14000 6200
AR Path="/5BF2E340/5E7905C9" Ref="R?"  Part="1" 
AR Path="/5E7905C9" Ref="R8"  Part="1" 
F 0 "R8" H 14070 6246 50  0000 L CNN
F 1 "1k5" H 14070 6155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 13930 6200 50  0001 C CNN
F 3 "~" H 14000 6200 50  0001 C CNN
	1    14000 6200
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0146
U 1 1 5E799208
P 6850 7100
F 0 "#PWR0146" H 6850 6950 50  0001 C CNN
F 1 "+3.3V" H 6865 7273 50  0000 C CNN
F 2 "" H 6850 7100 50  0001 C CNN
F 3 "" H 6850 7100 50  0001 C CNN
	1    6850 7100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0147
U 1 1 5E799D40
P 6200 4600
F 0 "#PWR0147" H 6200 4450 50  0001 C CNN
F 1 "+3.3V" H 6215 4773 50  0000 C CNN
F 2 "" H 6200 4600 50  0001 C CNN
F 3 "" H 6200 4600 50  0001 C CNN
	1    6200 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4600 6100 4600
Wire Wire Line
	5600 4600 6100 4600
Connection ~ 6100 4600
$Comp
L power:+3.3V #PWR0148
U 1 1 5E7A0A90
P 3400 6000
F 0 "#PWR0148" H 3400 5850 50  0001 C CNN
F 1 "+3.3V" H 3415 6173 50  0000 C CNN
F 2 "" H 3400 6000 50  0001 C CNN
F 3 "" H 3400 6000 50  0001 C CNN
	1    3400 6000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0149
U 1 1 5E7A322D
P 14800 5850
F 0 "#PWR0149" H 14800 5700 50  0001 C CNN
F 1 "+5V" H 14815 6023 50  0000 C CNN
F 2 "" H 14800 5850 50  0001 C CNN
F 3 "" H 14800 5850 50  0001 C CNN
	1    14800 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E7A3A03
P 14350 6200
AR Path="/5BF2E340/5E7A3A03" Ref="R?"  Part="1" 
AR Path="/5E7A3A03" Ref="R9"  Part="1" 
F 0 "R9" H 14420 6246 50  0000 L CNN
F 1 "1k5" H 14420 6155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 14280 6200 50  0001 C CNN
F 3 "~" H 14350 6200 50  0001 C CNN
	1    14350 6200
	-1   0    0    1   
$EndComp
Connection ~ 14000 6400
Wire Wire Line
	14000 6400 13200 6400
Wire Wire Line
	14000 6350 14000 6400
Wire Wire Line
	13200 6500 14350 6500
Wire Wire Line
	14350 6350 14350 6500
Connection ~ 14350 6500
Wire Wire Line
	14350 6500 14900 6500
Wire Wire Line
	14150 5850 14150 6050
Wire Wire Line
	14150 6050 14000 6050
Wire Wire Line
	14150 6050 14350 6050
Connection ~ 14150 6050
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5E7CEF83
P 2800 5700
AR Path="/5BF2E340/5E7CEF83" Ref="J?"  Part="1" 
AR Path="/5E7CEF83" Ref="J4"  Part="1" 
F 0 "J4" H 2800 5400 50  0000 C CNN
F 1 "DNI" H 2800 5500 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2800 5700 50  0001 C CNN
F 3 "~" H 2800 5700 50  0001 C CNN
	1    2800 5700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7CFA00
P 3000 5800
AR Path="/5BF2E340/5E7CFA00" Ref="#PWR?"  Part="1" 
AR Path="/5E7CFA00" Ref="#PWR0150"  Part="1" 
F 0 "#PWR0150" H 3000 5550 50  0001 C CNN
F 1 "GND" H 3005 5627 50  0000 C CNN
F 2 "" H 3000 5800 50  0001 C CNN
F 3 "" H 3000 5800 50  0001 C CNN
	1    3000 5800
	1    0    0    -1  
$EndComp
Text Label 3400 5600 0    50   ~ 0
~RESET~
Wire Wire Line
	3700 5600 3000 5600
Connection ~ 3700 5600
Wire Wire Line
	3700 4950 3700 5600
Text Notes 700  10750 0    118  ~ 0
TODO\n\n- 24V to 5V DC/DC? Or 5VDC from separate rpi PSU?\n- RPI hat connector + board outline + Mouning holes\n- extra on/off outputs (voltage? maybe relays?)\n- test points\n- I2C addr conflict check\n- ADC in header\n- GPIO header
Wire Wire Line
	1050 7800 1000 7800
$Comp
L power:+5V #PWR08
U 1 1 5E818833
P 7100 2400
F 0 "#PWR08" H 7100 2250 50  0001 C CNN
F 1 "+5V" H 7115 2573 50  0000 C CNN
F 2 "" H 7100 2400 50  0001 C CNN
F 3 "" H 7100 2400 50  0001 C CNN
	1    7100 2400
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5E818998
P 7750 2700
AR Path="/5BF2E340/5E818998" Ref="J?"  Part="1" 
AR Path="/5E818998" Ref="J6"  Part="1" 
F 0 "J6" H 7750 2500 50  0000 C CNN
F 1 "5V out" H 7800 2850 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7750 2700 50  0001 C CNN
F 3 "~" H 7750 2700 50  0001 C CNN
	1    7750 2700
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E81FD71
P 7500 2700
AR Path="/5BF2E340/5E81FD71" Ref="#PWR?"  Part="1" 
AR Path="/5E81FD71" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 7500 2450 50  0001 C CNN
F 1 "GND" H 7505 2527 50  0000 C CNN
F 2 "" H 7500 2700 50  0001 C CNN
F 3 "" H 7500 2700 50  0001 C CNN
	1    7500 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7500 2700 7550 2700
Text Notes 7800 2300 2    50   ~ 0
5V header for\nRPI display
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
	7550 5750 6750 5750
Text Label 6750 5750 0    50   ~ 0
PREG_SPI_~CS~
Wire Wire Line
	7550 5150 6750 5150
Text Label 6750 5150 0    50   ~ 0
PREG_SPI_CLK
Wire Wire Line
	7550 5250 6750 5250
Text Label 6750 5250 0    50   ~ 0
PREG_SPI_MOSI
Wire Wire Line
	7550 5350 6750 5350
Text Label 6750 5350 0    50   ~ 0
PREG_SPI_MISO
Wire Wire Line
	7550 5850 6750 5850
Text Label 6750 5850 0    50   ~ 0
PREG_CLEAR
Text Label 6750 5950 0    50   ~ 0
PREG_OK
Wire Wire Line
	6750 5950 7550 5950
Text Label 6750 6250 0    50   ~ 0
A_PREG_PRESSURE
Wire Wire Line
	6750 6250 7550 6250
Text Notes 6800 5600 0    50   ~ 0
GPIO
Text Notes 6800 5050 0    50   ~ 0
SPI
Text Notes 6750 6150 0    50   ~ 0
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
P 2500 10800
F 0 "H2" H 2600 10805 50  0000 L CNN
F 1 "DNI (mounting hole)" H 2600 10760 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad_Via" H 2500 10800 50  0001 C CNN
F 3 "~" H 2500 10800 50  0001 C CNN
	1    2500 10800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5EAC5855
P 2500 10900
F 0 "#PWR022" H 2500 10650 50  0001 C CNN
F 1 "GND" H 2505 10727 50  0000 C CNN
F 2 "" H 2500 10900 50  0001 C CNN
F 3 "" H 2500 10900 50  0001 C CNN
	1    2500 10900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5EAD36B5
P 15700 3100
AR Path="/5BF2E340/5EAD36B5" Ref="J?"  Part="1" 
AR Path="/5EAD36B5" Ref="J8"  Part="1" 
F 0 "J8" H 15700 2900 50  0000 C CNN
F 1 "PREG_SIGNALS" H 15700 2900 50  0001 C CNN
F 2 "Jitter_Footprints:TerminalBlock_Wurth_WR-TBL_691322110003_1x03_P3.50mm_Horizontal" H 15700 3100 50  0001 C CNN
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
F 0 "J7" H 15700 2150 50  0000 C CNN
F 1 "PREG_PWR" H 15700 2150 50  0001 C CNN
F 2 "Jitter_Footprints:TerminalBlock_Wurth_WR-TBL_691322110002_1x02_P3.50mm_Horizontal" H 15700 2350 50  0001 C CNN
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
	3250 4950 3700 4950
Wire Wire Line
	15450 2100 14850 2100
Wire Wire Line
	15450 2100 15450 2250
Connection ~ 14850 2100
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5EBE6F1F
P 1050 1850
AR Path="/5BF2E340/5EBE6F1F" Ref="J?"  Part="1" 
AR Path="/5EBE6F1F" Ref="J5"  Part="1" 
F 0 "J5" H 1050 1550 50  0000 C CNN
F 1 "24VIN" H 1050 1650 50  0000 C CNN
F 2 "Jitter_Footprints:TerminalBlock_Wurth_WR-TBL_691322110002_1x02_P3.50mm_Horizontal" H 1050 1850 50  0001 C CNN
F 3 "~" H 1050 1850 50  0001 C CNN
	1    1050 1850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EBE6F25
P 1250 2050
AR Path="/5BF2E340/5EBE6F25" Ref="#PWR?"  Part="1" 
AR Path="/5EBE6F25" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 1250 1800 50  0001 C CNN
F 1 "GND" H 1255 1877 50  0000 C CNN
F 2 "" H 1250 2050 50  0001 C CNN
F 3 "" H 1250 2050 50  0001 C CNN
	1    1250 2050
	-1   0    0    -1  
$EndComp
Text Notes 950  1450 0    50   ~ 0
24VDC 3A
$Comp
L Device:CP C22
U 1 1 5EC02FDC
P 1800 1900
F 0 "C22" H 1918 1946 50  0000 L CNN
F 1 "330uF" H 1918 1855 50  0000 L CNN
F 2 "Jitter_Footprints:CP_Elec_12.5x13.5" H 1838 1750 50  0001 C CNN
F 3 "~" H 1800 1900 50  0001 C CNN
F 4 "MAL214699107E3" H 1800 1900 50  0001 C CNN "MPN"
F 5 "generic bulk capacitor (value not determined)" H 1800 1900 50  0001 C CNN "Purpose"
	1    1800 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EC03751
P 1800 2050
AR Path="/5BF2E340/5EC03751" Ref="#PWR?"  Part="1" 
AR Path="/5EC03751" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 1800 1800 50  0001 C CNN
F 1 "GND" H 1805 1877 50  0000 C CNN
F 2 "" H 1800 2050 50  0001 C CNN
F 3 "" H 1800 2050 50  0001 C CNN
	1    1800 2050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	14550 2100 14850 2100
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
	6000 7400 5650 7400
Wire Wire Line
	5650 7500 6000 7500
Text Label 5700 7400 0    50   ~ 0
MCU_DP
Text Label 5700 7500 0    50   ~ 0
MCU_DM
Connection ~ 6650 7400
Wire Wire Line
	6650 7400 7100 7400
Wire Wire Line
	6300 7400 6650 7400
Wire Wire Line
	6850 7100 6650 7100
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
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 2150 3150 50  0001 C CNN
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
Text Notes 950  1350 0    79   ~ 16
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
Text Notes 12850 5600 0    118  ~ 24
Flow sensor
Text Notes 15300 6250 0    197  ~ 0
TODO
Wire Notes Line
	12750 5300 12750 7000
$Comp
L Connector:Raspberry_Pi_2_3 J9
U 1 1 5E78308D
P 8900 2550
F 0 "J9" H 8750 1150 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 9050 1050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical_SMD" H 8900 2550 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 8900 2550 50  0001 C CNN
	1    8900 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1650 7050 1650
Text Label 7050 1650 0    50   ~ 0
UART_RX
Text Label 7050 1750 0    50   ~ 0
UART_TX
Wire Wire Line
	7700 1750 8100 1750
NoConn ~ 9000 1250
NoConn ~ 9100 1250
NoConn ~ 9700 1650
NoConn ~ 9700 1750
NoConn ~ 9700 1950
NoConn ~ 9700 2050
NoConn ~ 9700 2250
NoConn ~ 9700 2350
NoConn ~ 9700 2450
NoConn ~ 9700 2650
NoConn ~ 9700 2750
NoConn ~ 9700 2850
NoConn ~ 9700 2950
NoConn ~ 9700 3050
NoConn ~ 9700 3250
NoConn ~ 9700 3350
NoConn ~ 8100 3250
NoConn ~ 8100 3150
NoConn ~ 8100 3050
NoConn ~ 8100 2950
NoConn ~ 8100 2850
NoConn ~ 8100 2750
NoConn ~ 8100 2550
NoConn ~ 8100 2450
NoConn ~ 8100 2350
NoConn ~ 8100 2150
NoConn ~ 8100 2050
NoConn ~ 8100 1950
Wire Wire Line
	8800 1250 8700 1250
Connection ~ 8700 1250
Wire Wire Line
	8700 1250 8500 1250
$Comp
L Device:C C28
U 1 1 5E95553B
P 8050 1100
AR Path="/5E95553B" Ref="C28"  Part="1" 
AR Path="/5BF2E340/5E95553B" Ref="C?"  Part="1" 
F 0 "C28" H 8165 1146 50  0000 L CNN
F 1 "100nF" H 8165 1055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8088 950 50  0001 C CNN
F 3 "~" H 8050 1100 50  0001 C CNN
F 4 "decoupling" H 8050 1100 50  0001 C CNN "purpose"
	1    8050 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E955EB7
P 8050 1250
AR Path="/5BF2E340/5E955EB7" Ref="#PWR?"  Part="1" 
AR Path="/5E955EB7" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 8050 1000 50  0001 C CNN
F 1 "GND" H 8055 1077 50  0000 C CNN
F 2 "" H 8050 1250 50  0001 C CNN
F 3 "" H 8050 1250 50  0001 C CNN
	1    8050 1250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8500 950  8050 950 
Wire Wire Line
	8500 950  8500 1250
Connection ~ 8050 950 
Wire Wire Line
	8050 950  7900 950 
$Comp
L power:+5V #PWR0151
U 1 1 5E966090
P 7900 950
F 0 "#PWR0151" H 7900 800 50  0001 C CNN
F 1 "+5V" H 7915 1123 50  0000 C CNN
F 2 "" H 7900 950 50  0001 C CNN
F 3 "" H 7900 950 50  0001 C CNN
	1    7900 950 
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E966379
P 8300 3900
AR Path="/5BF2E340/5E966379" Ref="#PWR?"  Part="1" 
AR Path="/5E966379" Ref="#PWR0152"  Part="1" 
F 0 "#PWR0152" H 8300 3650 50  0001 C CNN
F 1 "GND" H 8305 3727 50  0000 C CNN
F 2 "" H 8300 3900 50  0001 C CNN
F 3 "" H 8300 3900 50  0001 C CNN
	1    8300 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8300 3900 8300 3850
Wire Wire Line
	8300 3850 8500 3850
Connection ~ 8500 3850
Wire Wire Line
	8500 3850 8600 3850
Connection ~ 8600 3850
Wire Wire Line
	8600 3850 8700 3850
Connection ~ 8700 3850
Wire Wire Line
	8700 3850 8800 3850
Connection ~ 8800 3850
Wire Wire Line
	8800 3850 8900 3850
Connection ~ 8900 3850
Wire Wire Line
	8900 3850 9000 3850
Connection ~ 9000 3850
Wire Wire Line
	9000 3850 9100 3850
Connection ~ 9100 3850
Wire Wire Line
	9100 3850 9200 3850
Wire Bus Line
	6600 4750 6600 6550
Text Notes 6650 4700 0    50   ~ 0
TODO pinswap these:
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5E997A85
P 2150 8000
AR Path="/5BF2E340/5E997A85" Ref="J?"  Part="1" 
AR Path="/5E997A85" Ref="J10"  Part="1" 
F 0 "J10" H 2150 7600 50  0000 C CNN
F 1 "UART" H 2200 7700 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 2150 8000 50  0001 C CNN
F 3 "~" H 2150 8000 50  0001 C CNN
	1    2150 8000
	-1   0    0    1   
$EndComp
Text Label 2800 8000 2    50   ~ 0
UART_TX
Text Label 2800 7900 2    50   ~ 0
UART_RX
$Comp
L power:GND #PWR?
U 1 1 5E999DCE
P 2450 8150
AR Path="/5BF2E340/5E999DCE" Ref="#PWR?"  Part="1" 
AR Path="/5E999DCE" Ref="#PWR0153"  Part="1" 
F 0 "#PWR0153" H 2450 7900 50  0001 C CNN
F 1 "GND" H 2455 7977 50  0000 C CNN
F 2 "" H 2450 8150 50  0001 C CNN
F 3 "" H 2450 8150 50  0001 C CNN
	1    2450 8150
	1    0    0    -1  
$EndComp
$Comp
L Jitter_Components:+3V #PWR?
U 1 1 5E99A0DF
P 2450 7750
AR Path="/5BF2E340/5E99A0DF" Ref="#PWR?"  Part="1" 
AR Path="/5E99A0DF" Ref="#PWR0154"  Part="1" 
F 0 "#PWR0154" H 2450 7600 50  0001 C CNN
F 1 "+3V" H 2465 7923 50  0000 C CNN
F 2 "" H 2450 7750 50  0001 C CNN
F 3 "" H 2450 7750 50  0001 C CNN
	1    2450 7750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2800 7900 2350 7900
Wire Wire Line
	2800 8000 2350 8000
Wire Wire Line
	2450 8150 2450 8100
Wire Wire Line
	2450 8100 2350 8100
Wire Wire Line
	2350 7800 2450 7800
Wire Wire Line
	2450 7800 2450 7750
Text Notes 850  7450 0    118  ~ 24
Debug: SWD + UART
$Comp
L Device:R R?
U 1 1 5EA0574B
P 7550 1650
AR Path="/5BF2E340/5EA0574B" Ref="R?"  Part="1" 
AR Path="/5EA0574B" Ref="R16"  Part="1" 
F 0 "R16" V 7650 1650 50  0000 L CNN
F 1 "0" V 7550 1650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7480 1650 50  0001 C CNN
F 3 "~" H 7550 1650 50  0001 C CNN
	1    7550 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7700 1650 8100 1650
Text Label 7750 1650 0    50   ~ 0
RPI_TX
$Comp
L Device:R R?
U 1 1 5EA3E263
P 7550 1750
AR Path="/5BF2E340/5EA3E263" Ref="R?"  Part="1" 
AR Path="/5EA3E263" Ref="R17"  Part="1" 
F 0 "R17" V 7450 1750 50  0000 L CNN
F 1 "0" V 7550 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7480 1750 50  0001 C CNN
F 3 "~" H 7550 1750 50  0001 C CNN
	1    7550 1750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7400 1750 7050 1750
Text Label 7750 1750 0    50   ~ 0
RPI_RX
Text Label 2350 4700 2    50   ~ 0
USB_VBUS
Wire Wire Line
	4800 3300 4750 3300
Wire Wire Line
	4050 3050 4550 3050
Text Label 4050 3050 0    50   ~ 0
DCDC_5V
Wire Wire Line
	4550 3600 4550 3550
Wire Wire Line
	4050 3600 4550 3600
Text Label 4050 3600 0    50   ~ 0
USB_VBUS
$Comp
L power:+5V #PWR0134
U 1 1 5E7918E8
P 4800 3300
F 0 "#PWR0134" H 4800 3150 50  0001 C CNN
F 1 "+5V" H 4815 3473 50  0000 C CNN
F 2 "" H 4800 3300 50  0001 C CNN
F 3 "" H 4800 3300 50  0001 C CNN
	1    4800 3300
	1    0    0    -1  
$EndComp
$Comp
L Jumper:Jumper_3_Bridged12 JP1
U 1 1 5EA6733B
P 4550 3300
F 0 "JP1" V 4550 3367 50  0000 L CNN
F 1 "5V_jumper" H 4550 3394 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4550 3300 50  0001 C CNN
F 3 "~" H 4550 3300 50  0001 C CNN
	1    4550 3300
	0    -1   1    0   
$EndComp
$Comp
L Device:C C29
U 1 1 5EBA796D
P 7100 2550
AR Path="/5EBA796D" Ref="C29"  Part="1" 
AR Path="/5BF2E340/5EBA796D" Ref="C?"  Part="1" 
F 0 "C29" H 7215 2596 50  0000 L CNN
F 1 "100nF" H 7215 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7138 2400 50  0001 C CNN
F 3 "~" H 7100 2550 50  0001 C CNN
F 4 "decoupling" H 7100 2550 50  0001 C CNN "purpose"
	1    7100 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EBA8B23
P 7100 2700
AR Path="/5BF2E340/5EBA8B23" Ref="#PWR?"  Part="1" 
AR Path="/5EBA8B23" Ref="#PWR0155"  Part="1" 
F 0 "#PWR0155" H 7100 2450 50  0001 C CNN
F 1 "GND" H 7105 2527 50  0000 C CNN
F 2 "" H 7100 2700 50  0001 C CNN
F 3 "" H 7100 2700 50  0001 C CNN
	1    7100 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7100 2400 7500 2400
Wire Wire Line
	7500 2400 7500 2600
Wire Wire Line
	7500 2600 7550 2600
Connection ~ 7100 2400
Wire Notes Line
	6850 700  9900 700 
Wire Notes Line
	9900 700  9900 4200
Wire Notes Line
	9900 4200 6850 4200
Wire Notes Line
	6850 4200 6850 700 
Text Notes 6950 1000 0    118  ~ 24
RPI hat
$Comp
L Device:R R?
U 1 1 5EC779C5
P 14550 5850
AR Path="/5BF2E340/5EC779C5" Ref="R?"  Part="1" 
AR Path="/5EC779C5" Ref="R19"  Part="1" 
F 0 "R19" V 14450 5800 50  0000 L CNN
F 1 "DNI" V 14550 5800 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 14480 5850 50  0001 C CNN
F 3 "~" H 14550 5850 50  0001 C CNN
	1    14550 5850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5EC78136
P 13900 5850
AR Path="/5BF2E340/5EC78136" Ref="R?"  Part="1" 
AR Path="/5EC78136" Ref="R18"  Part="1" 
F 0 "R18" V 13800 5800 50  0000 L CNN
F 1 "0" V 13900 5850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 13830 5850 50  0001 C CNN
F 3 "~" H 13900 5850 50  0001 C CNN
	1    13900 5850
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0156
U 1 1 5EC78DA1
P 13700 5850
F 0 "#PWR0156" H 13700 5700 50  0001 C CNN
F 1 "+3.3V" H 13715 6023 50  0000 C CNN
F 2 "" H 13700 5850 50  0001 C CNN
F 3 "" H 13700 5850 50  0001 C CNN
	1    13700 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	14050 5850 14150 5850
Connection ~ 14150 5850
Wire Wire Line
	14800 5850 14700 5850
Wire Wire Line
	13700 5850 13750 5850
Text Label 14150 5850 0    50   ~ 0
V_PU
Wire Wire Line
	14150 5850 14400 5850
Wire Wire Line
	8500 5750 7700 5750
Text Label 7700 5750 0    50   ~ 0
PSENSE_1_SPI_~CS~
Wire Wire Line
	8500 5150 7700 5150
Text Label 7700 5150 0    50   ~ 0
PSENSE_SPI_CLK
Wire Wire Line
	8500 5250 7700 5250
Text Label 7700 5250 0    50   ~ 0
PSENSE_SPI_MOSI
Wire Wire Line
	8500 5350 7700 5350
Text Label 7700 5350 0    50   ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	8500 5850 7700 5850
Text Label 7700 5850 0    50   ~ 0
PSENSE_1_DATA_READY
Wire Wire Line
	8500 5950 7700 5950
Text Label 7700 5950 0    50   ~ 0
PSENSE_RESET
Wire Wire Line
	7700 6250 8500 6250
Wire Notes Line
	2450 6900 650  6900
Wire Notes Line
	650  4300 2450 4300
Wire Notes Line
	12750 5300 16350 5300
Wire Notes Line
	16350 5300 16350 7000
Wire Notes Line
	16350 7000 12750 7000
Text Label 8650 5750 0    50   ~ 0
PSENSE_2_SPI_~CS~
Wire Wire Line
	9450 5750 8650 5750
Text Label 8650 5850 0    50   ~ 0
PSENSE_2_DATA_READY
Wire Wire Line
	8650 5850 9500 5850
$Sheet
S 11150 5800 1150 2250
U 5F5B6035
F0 "pressure_sensor" 50
F1 "pressure_sensor.sch" 50
F2 "PSENSE_2_DATA_READY" O L 11150 7400 50 
F3 "PSENSE_2_SPI_~CS~" I L 11150 6000 50 
F4 "PSENSE_SPI_CLK" I L 11150 6200 50 
F5 "PSENSE_SPI_MOSI" I L 11150 6300 50 
F6 "PSENSE_SPI_MISO" O L 11150 6400 50 
F7 "PSENSE_1_DATA_READY" O L 11150 7300 50 
F8 "I2C_SCL" B L 11150 6800 50 
F9 "I2C_SDA" B L 11150 6900 50 
F10 "A_PRESSURE_2" O L 11150 7900 50 
F11 "A_PRESSURE_1" O L 11150 7800 50 
F12 "PSENSE_1_SPI_~CS~" I L 11150 5900 50 
$EndSheet
Text Label 10200 7400 0    50   ~ 0
PSENSE_2_DATA_READY
Wire Wire Line
	10200 7400 11150 7400
Text Label 10200 7300 0    50   ~ 0
PSENSE_1_DATA_READY
Wire Wire Line
	10200 7300 11150 7300
Text Label 10200 6900 0    50   ~ 0
I2C_SDA
Text Label 10200 6800 0    50   ~ 0
I2C_SCL
Wire Wire Line
	10200 6800 11150 6800
Wire Wire Line
	10200 6900 11150 6900
Text Label 10200 6000 0    50   ~ 0
PSENSE_2_SPI_~CS~
Text Label 10200 5900 0    50   ~ 0
PSENSE_1_SPI_~CS~
Text Label 10200 6200 0    50   ~ 0
PSENSE_SPI_CLK
Text Label 10200 6300 0    50   ~ 0
PSENSE_SPI_MOSI
Text Label 10200 6400 0    50   ~ 0
PSENSE_SPI_MISO
Wire Wire Line
	10200 6400 11150 6400
Wire Wire Line
	11150 6300 10200 6300
Wire Wire Line
	10200 6200 11150 6200
Wire Wire Line
	10200 6000 11150 6000
Wire Wire Line
	11150 5900 10200 5900
Text Label 10200 7800 0    50   ~ 0
A_PRESSURE_1
Text Label 7700 6250 0    50   ~ 0
A_PRESSURE_1
Wire Wire Line
	8650 6250 9450 6250
Text Label 8650 6250 0    50   ~ 0
A_PRESSURE_2
Text Label 10200 7900 0    50   ~ 0
A_PRESSURE_1
Wire Wire Line
	10200 7900 11150 7900
Wire Wire Line
	11150 7800 10200 7800
Text Notes 10150 5550 0    118  ~ 24
Pressure sensor(s)
Wire Notes Line
	10100 5300 10100 8150
Wire Notes Line
	10100 8150 12600 8150
Wire Notes Line
	12600 8150 12600 5300
Wire Notes Line
	12600 5300 10100 5300
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5F83CC41
P 1450 1750
F 0 "#FLG0101" H 1450 1825 50  0001 C CNN
F 1 "PWR_FLAG" H 1450 1923 50  0000 C CNN
F 2 "" H 1450 1750 50  0001 C CNN
F 3 "~" H 1450 1750 50  0001 C CNN
	1    1450 1750
	1    0    0    -1  
$EndComp
Connection ~ 1800 1750
Wire Wire Line
	1800 1750 1900 1750
Connection ~ 1450 1750
Wire Wire Line
	1450 1750 1800 1750
Wire Wire Line
	1250 1750 1450 1750
Wire Wire Line
	1250 1850 1250 2050
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5F87F701
P 4750 3300
F 0 "#FLG0102" H 4750 3375 50  0001 C CNN
F 1 "PWR_FLAG" H 4650 3500 50  0000 C CNN
F 2 "" H 4750 3300 50  0001 C CNN
F 3 "~" H 4750 3300 50  0001 C CNN
	1    4750 3300
	-1   0    0    1   
$EndComp
Connection ~ 4750 3300
Wire Wire Line
	4750 3300 4700 3300
$Comp
L Jitter_Components:+3V #PWR?
U 1 1 5F880770
P 1050 7750
AR Path="/5BF2E340/5F880770" Ref="#PWR?"  Part="1" 
AR Path="/5F880770" Ref="#PWR0145"  Part="1" 
F 0 "#PWR0145" H 1050 7600 50  0001 C CNN
F 1 "+3V" H 1065 7923 50  0000 C CNN
F 2 "" H 1050 7750 50  0001 C CNN
F 3 "" H 1050 7750 50  0001 C CNN
	1    1050 7750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1050 7750 1050 7800
$EndSCHEMATC
