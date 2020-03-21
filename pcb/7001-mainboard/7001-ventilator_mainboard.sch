EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Overview"
Date "2018-12-11"
Rev "2.0"
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
F 2 "MountingHole:MountingHole_2.7mm_Pad_Via" H 11350 10500 50  0001 C CNN
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
Text HLabel 2950 5600 2    50   Output ~ 0
+3V
$Comp
L Regulator_Linear:MIC5501-3.0YM5 U?
U 1 1 5E77BFE3
P 2050 5700
AR Path="/5C00B45C/5E77BFE3" Ref="U?"  Part="1" 
AR Path="/5E77BFE3" Ref="U?"  Part="1" 
F 0 "U?" H 2050 6067 50  0000 C CNN
F 1 "MIC5501-3.0YM5" H 2050 5976 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 2050 5300 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/MIC550X.pdf" H 1800 5950 50  0001 C CNN
F 4 "NCP551SN30T1G (lower Iq, slightly more expensive)" H 2050 5700 50  0001 C CNN "alternative"
F 5 "Most 3V sot23-5 LDOs are footprint compatible" H 2050 5700 50  0001 C CNN "Note"
	1    2050 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 5600 1450 5600
$Comp
L power:GND #PWR?
U 1 1 5E77BFEA
P 2050 6000
AR Path="/5BF2E340/5E77BFEA" Ref="#PWR?"  Part="1" 
AR Path="/5C00B45C/5E77BFEA" Ref="#PWR?"  Part="1" 
AR Path="/5E77BFEA" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2050 5750 50  0001 C CNN
F 1 "GND" H 2055 5827 50  0000 C CNN
F 2 "" H 2050 6000 50  0001 C CNN
F 3 "" H 2050 6000 50  0001 C CNN
	1    2050 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E77BFF0
P 2800 5900
AR Path="/5BF2E340/5E77BFF0" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E77BFF0" Ref="#PWR?"  Part="1" 
AR Path="/5C00B45C/5E77BFF0" Ref="#PWR?"  Part="1" 
AR Path="/5E77BFF0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2800 5650 50  0001 C CNN
F 1 "GND" H 2805 5727 50  0000 C CNN
F 2 "" H 2800 5900 50  0001 C CNN
F 3 "" H 2800 5900 50  0001 C CNN
	1    2800 5900
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E77BFF7
P 2800 5750
AR Path="/5E77BFF7" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E77BFF7" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E77BFF7" Ref="C?"  Part="1" 
AR Path="/5C00B45C/5E77BFF7" Ref="C?"  Part="1" 
F 0 "C?" H 2915 5796 50  0000 L CNN
F 1 "1uF" H 2915 5705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2838 5600 50  0001 C CNN
F 3 "~" H 2800 5750 50  0001 C CNN
F 4 "decoupling" H 2800 5750 50  0001 C CNN "purpose"
	1    2800 5750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1650 5800 1650 5600
Connection ~ 1650 5600
Text Notes 800  6450 0    101  Italic 20
3V LDO
Text Notes 800  6700 0    50   ~ 0
3V is used as the supply voltage for the microcontroller.\nThis LDO is always-on.
$Comp
L power:GND #PWR?
U 1 1 5E77C001
P 1000 5900
AR Path="/5BF2E340/5E77C001" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E77C001" Ref="#PWR?"  Part="1" 
AR Path="/5C00B45C/5E77C001" Ref="#PWR?"  Part="1" 
AR Path="/5E77C001" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1000 5650 50  0001 C CNN
F 1 "GND" H 1005 5727 50  0000 C CNN
F 2 "" H 1000 5900 50  0001 C CNN
F 3 "" H 1000 5900 50  0001 C CNN
	1    1000 5900
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E77C008
P 1000 5750
AR Path="/5E77C008" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E77C008" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E77C008" Ref="C?"  Part="1" 
AR Path="/5C00B45C/5E77C008" Ref="C?"  Part="1" 
F 0 "C?" H 1115 5796 50  0000 L CNN
F 1 "1uF" H 1115 5705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1038 5600 50  0001 C CNN
F 3 "~" H 1000 5750 50  0001 C CNN
F 4 "decoupling" H 1000 5750 50  0001 C CNN "purpose"
	1    1000 5750
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E77C010
P 1450 5750
AR Path="/5E77C010" Ref="C?"  Part="1" 
AR Path="/5BF41E62/5E77C010" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E77C010" Ref="C?"  Part="1" 
AR Path="/5BF3D3D9/5E77C010" Ref="C?"  Part="1" 
AR Path="/5C00B45C/5E77C010" Ref="C?"  Part="1" 
F 0 "C?" V 1200 5650 50  0000 L CNN
F 1 "100nF" V 1300 5600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1488 5600 50  0001 C CNN
F 3 "" H 1450 5750 50  0001 C CNN
F 4 "16V" H 1450 5750 50  0001 C CNN "Voltage rating"
F 5 "decoupling" H 1450 5750 50  0001 C CNN "purpose"
	1    1450 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E77C016
P 1450 5900
AR Path="/5BF2E340/5E77C016" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5E77C016" Ref="#PWR?"  Part="1" 
AR Path="/5C00B45C/5E77C016" Ref="#PWR?"  Part="1" 
AR Path="/5E77C016" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1450 5650 50  0001 C CNN
F 1 "GND" H 1455 5727 50  0000 C CNN
F 2 "" H 1450 5900 50  0001 C CNN
F 3 "" H 1450 5900 50  0001 C CNN
	1    1450 5900
	-1   0    0    -1  
$EndComp
Connection ~ 1450 5600
Connection ~ 2800 5600
Wire Wire Line
	2800 5600 2950 5600
Wire Wire Line
	750  5600 1000 5600
Connection ~ 1000 5600
Wire Wire Line
	1000 5600 1450 5600
Wire Wire Line
	2450 5600 2600 5600
$Comp
L Connector:TestPoint TP?
U 1 1 5E77C023
P 2600 5600
AR Path="/5BF2E340/5E77C023" Ref="TP?"  Part="1" 
AR Path="/5C00B45C/5E77C023" Ref="TP?"  Part="1" 
AR Path="/5E77C023" Ref="TP?"  Part="1" 
F 0 "TP?" H 2650 5850 50  0000 L CNN
F 1 "3V" H 2650 5750 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 2800 5600 50  0001 C CNN
F 3 "~" H 2800 5600 50  0001 C CNN
	1    2600 5600
	1    0    0    -1  
$EndComp
Connection ~ 2600 5600
Wire Wire Line
	2600 5600 2800 5600
Text Label 2350 1800 2    50   ~ 0
USB_DP
Text Label 2350 1900 2    50   ~ 0
USB_DN
$Comp
L Connector:USB_B_Micro J?
U 1 1 5E781095
P 950 1800
AR Path="/5E781095" Ref="J?"  Part="1" 
AR Path="/5C03F077/5E781095" Ref="J?"  Part="1" 
F 0 "J?" H 1005 2267 50  0000 C CNN
F 1 "USB_B_Micro" H 1005 2176 50  0000 C CNN
F 2 "Jitter_Footprints:USB_Micro-B_UJ2-MIBH-4-SMT-TR-67_SMD_Horizontal" H 1100 1750 50  0001 C CNN
F 3 "~" H 1100 1750 50  0001 C CNN
	1    950  1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E78109B
P 950 2200
AR Path="/5E78109B" Ref="#PWR?"  Part="1" 
AR Path="/5C03F077/5E78109B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 950 1950 50  0001 C CNN
F 1 "GND" H 955 2027 50  0000 C CNN
F 2 "" H 950 2200 50  0001 C CNN
F 3 "" H 950 2200 50  0001 C CNN
	1    950  2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2200 850  2200
Connection ~ 950  2200
NoConn ~ 1250 2000
Wire Wire Line
	1400 1600 1400 1100
Wire Wire Line
	1400 1100 1650 1100
Wire Wire Line
	1250 1600 1400 1600
$Comp
L Device:C C?
U 1 1 5E7810A7
P 1650 1250
AR Path="/5E7810A7" Ref="C?"  Part="1" 
AR Path="/5C03F077/5E7810A7" Ref="C?"  Part="1" 
F 0 "C?" H 1765 1296 50  0000 L CNN
F 1 "100nF" H 1765 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1688 1100 50  0001 C CNN
F 3 "~" H 1650 1250 50  0001 C CNN
	1    1650 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7810AD
P 1650 1400
AR Path="/5E7810AD" Ref="#PWR?"  Part="1" 
AR Path="/5C03F077/5E7810AD" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1650 1150 50  0001 C CNN
F 1 "GND" H 1655 1227 50  0000 C CNN
F 2 "" H 1650 1400 50  0001 C CNN
F 3 "" H 1650 1400 50  0001 C CNN
	1    1650 1400
	1    0    0    -1  
$EndComp
Text Label 2400 1100 0    50   ~ 0
Vbus
$Comp
L power:GND #PWR?
U 1 1 5E7810B4
P 1300 2700
AR Path="/5E7810B4" Ref="#PWR?"  Part="1" 
AR Path="/5C03F077/5E7810B4" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1300 2450 50  0001 C CNN
F 1 "GND" H 1305 2527 50  0000 C CNN
F 2 "" H 1300 2700 50  0001 C CNN
F 3 "" H 1300 2700 50  0001 C CNN
	1    1300 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse_Small F?
U 1 1 5E7810BF
P 2050 1100
AR Path="/5C03F077/5E7810BF" Ref="F?"  Part="1" 
AR Path="/5E7810BF" Ref="F?"  Part="1" 
F 0 "F?" H 2050 1193 50  0000 C CNN
F 1 "MCCFB1206TFF/2" H 2050 1194 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" H 2050 1100 50  0001 C CNN
F 3 "~" H 2050 1100 50  0001 C CNN
F 4 "2A" H 2050 1100 50  0001 C CNN "Fuse Current"
F 5 "safety fuse" H 2050 1100 50  0001 C CNN "purpose"
	1    2050 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1100 1650 1100
Connection ~ 1650 1100
Wire Wire Line
	2150 1100 2300 1100
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5E7810C8
P 2300 1100
AR Path="/5C03F077/5E7810C8" Ref="#FLG?"  Part="1" 
AR Path="/5E7810C8" Ref="#FLG?"  Part="1" 
F 0 "#FLG?" H 2300 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 2300 1273 50  0000 C CNN
F 2 "" H 2300 1100 50  0001 C CNN
F 3 "~" H 2300 1100 50  0001 C CNN
	1    2300 1100
	-1   0    0    1   
$EndComp
Connection ~ 2300 1100
Wire Wire Line
	2300 1100 2650 1100
$Comp
L Power_Protection:TPD2E2U06 U?
U 1 1 5E7810D1
P 1700 2700
AR Path="/5C03F077/5E7810D1" Ref="U?"  Part="1" 
AR Path="/5E7810D1" Ref="U?"  Part="1" 
F 0 "U?" V 1654 2929 50  0000 L CNN
F 1 "TPD2E2U06" V 1745 2929 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-553" H 900 2450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpd2e2u06.pdf" H 1500 2900 50  0001 C CNN
F 4 "ESD protection" H 1700 2700 50  0001 C CNN "purpose"
	1    1700 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 2700 1300 2700
NoConn ~ 1800 3000
Wire Wire Line
	1600 3000 1100 3000
Wire Wire Line
	1100 3000 1100 2400
Wire Wire Line
	1100 2400 1600 2400
Text Notes 1050 3300 0    50   ~ 0
ESD protection\n\nSee datasheet for layout
Wire Wire Line
	1250 1800 1800 1800
Wire Wire Line
	1250 1900 1600 1900
Wire Wire Line
	1800 2400 1800 1800
Connection ~ 1800 1800
Wire Wire Line
	1800 1800 2350 1800
Wire Wire Line
	1600 2400 1600 1900
Connection ~ 1600 2400
Connection ~ 1600 1900
Wire Wire Line
	1600 1900 2350 1900
Text Notes 16850 10250 0    47   ~ 0
TODO\nWith prototype: tune gate resistor value\nHigher = lower EMC, too high = slow response
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 5E795521
P 18100 10800
AR Path="/5BF41E62/5E795521" Ref="Q?"  Part="1" 
AR Path="/5E795521" Ref="Q?"  Part="1" 
F 0 "Q?" H 17750 10650 50  0000 L CNN
F 1 "IRLML6244TRPbF" H 17500 10550 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 18300 10900 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/196/irlml6244pbf-1228275.pdf" H 18100 10800 50  0001 C CNN
F 4 "30mOhm @Vgs < 3V" H 18100 10800 50  0001 C CNN "Rds(on)"
F 5 "sot-23 footprint nmos, Rds(on) ~ 0.1" H 18100 10800 50  0001 C CNN "alternative"
	1    18100 10800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E795527
P 18300 11050
AR Path="/5BF41E62/5E795527" Ref="#PWR?"  Part="1" 
AR Path="/5E795527" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18300 10800 50  0001 C CNN
F 1 "GND" H 18305 10877 50  0000 C CNN
F 2 "" H 18300 11050 50  0001 C CNN
F 3 "" H 18300 11050 50  0001 C CNN
	1    18300 11050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E79552E
P 19200 10750
AR Path="/5E79552E" Ref="C?"  Part="1" 
AR Path="/5BF41E62/5E79552E" Ref="C?"  Part="1" 
F 0 "C?" H 19350 10650 50  0000 L CNN
F 1 "2.2nF" H 19350 10550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 19238 10600 50  0001 C CNN
F 3 "~" H 19200 10750 50  0001 C CNN
F 4 "EMC filter" H 19200 10750 50  0001 C CNN "purpose"
	1    19200 10750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E795534
P 19200 10900
AR Path="/5E795534" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E62/5E795534" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 19200 10650 50  0001 C CNN
F 1 "GND" H 19205 10727 50  0000 C CNN
F 2 "" H 19200 10900 50  0001 C CNN
F 3 "" H 19200 10900 50  0001 C CNN
	1    19200 10900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E79553B
P 19200 10050
AR Path="/5E79553B" Ref="C?"  Part="1" 
AR Path="/5BF41E62/5E79553B" Ref="C?"  Part="1" 
F 0 "C?" H 18900 10000 50  0000 L CNN
F 1 "2.2nF" H 18900 9900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 19238 9900 50  0001 C CNN
F 3 "~" H 19200 10050 50  0001 C CNN
F 4 "EMC filter" H 19200 10050 50  0001 C CNN "purpose"
	1    19200 10050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E795541
P 19200 10200
AR Path="/5E795541" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E62/5E795541" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 19200 9950 50  0001 C CNN
F 1 "GND" H 19205 10027 50  0000 C CNN
F 2 "" H 19200 10200 50  0001 C CNN
F 3 "" H 19200 10200 50  0001 C CNN
	1    19200 10200
	1    0    0    -1  
$EndComp
Wire Wire Line
	19400 10300 19400 9900
Wire Wire Line
	19400 10400 19400 10600
Wire Wire Line
	19400 10600 19200 10600
Connection ~ 19200 9900
Wire Wire Line
	19200 9900 19400 9900
Connection ~ 19200 10600
Wire Wire Line
	18200 10600 18400 10600
$Comp
L Diode:BZT52Bxx D?
U 1 1 5E795552
P 18400 10750
AR Path="/5BF41E62/5E795552" Ref="D?"  Part="1" 
AR Path="/5E795552" Ref="D?"  Part="1" 
F 0 "D?" V 18354 10829 50  0000 L CNN
F 1 "BZT52C10+" V 18445 10829 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 18400 10575 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzt52b2v4.pdf" H 18400 10750 50  0001 C CNN
F 4 "500mW" V 18400 10750 50  0001 C CNN "Power rating"
F 5 "SOD-123 zener: 7.5-10V, Pd >= 500mW" V 18400 10750 50  0001 C CNN "alternative"
F 6 "10V" V 18400 10750 50  0001 C CNN "Zener voltage"
F 7 "fast discharging of inductive load" V 18400 10750 50  0001 C CNN "purpose"
	1    18400 10750
	0    1    1    0   
$EndComp
Connection ~ 18400 10600
Wire Wire Line
	18200 11000 18200 11050
Wire Wire Line
	18200 11050 18300 11050
Wire Wire Line
	18400 11050 18400 10900
Connection ~ 18300 11050
Wire Wire Line
	18300 11050 18400 11050
$Comp
L Device:R R?
U 1 1 5E79555F
P 17600 10800
AR Path="/5BF41E62/5E79555F" Ref="R?"  Part="1" 
AR Path="/5E79555F" Ref="R?"  Part="1" 
F 0 "R?" V 17393 10800 50  0000 C CNN
F 1 "1k" V 17484 10800 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 17530 10800 50  0001 C CNN
F 3 "~" H 17600 10800 50  0001 C CNN
F 4 "EMC: edge rate limiting" V 17600 10800 50  0001 C CNN "purpose"
	1    17600 10800
	0    1    1    0   
$EndComp
Wire Wire Line
	17750 10800 17800 10800
$Comp
L power:+6V #PWR?
U 1 1 5E795568
P 19050 9900
AR Path="/5BF41E62/5E795568" Ref="#PWR?"  Part="1" 
AR Path="/5E795568" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 19050 9750 50  0001 C CNN
F 1 "+6V" H 19065 10073 50  0000 C CNN
F 2 "" H 19050 9900 50  0001 C CNN
F 3 "" H 19050 9900 50  0001 C CNN
	1    19050 9900
	1    0    0    -1  
$EndComp
Text Notes 16800 9750 0    118  ~ 24
pwm out?
$Comp
L Connector_Generic_MountingPin:Conn_01x02_MountingPin J?
U 1 1 5E79556F
P 19600 10300
AR Path="/5BF41E62/5E79556F" Ref="J?"  Part="1" 
AR Path="/5E79556F" Ref="J?"  Part="1" 
F 0 "J?" H 19687 10170 50  0000 L CNN
F 1 "Conn_01x02_MountingPin" H 19687 10125 50  0001 L CNN
F 2 "Jitter_Footprints:JST_ZH_S2B-ZR-SM4A-TF_1x02-1MP_P1.5mm_Horizontal" H 19600 10300 50  0001 C CNN
F 3 "~" H 19600 10300 50  0001 C CNN
	1    19600 10300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E795575
P 19600 10600
AR Path="/5E795575" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E62/5E795575" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 19600 10350 50  0001 C CNN
F 1 "GND" H 19605 10427 50  0000 C CNN
F 2 "" H 19600 10600 50  0001 C CNN
F 3 "" H 19600 10600 50  0001 C CNN
	1    19600 10600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E79559A
P 20100 10500
AR Path="/5BF41E62/5E79559A" Ref="#PWR?"  Part="1" 
AR Path="/5E79559A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 20100 10250 50  0001 C CNN
F 1 "GND" H 20105 10327 50  0000 C CNN
F 2 "" H 20100 10500 50  0001 C CNN
F 3 "" H 20100 10500 50  0001 C CNN
	1    20100 10500
	1    0    0    -1  
$EndComp
$Comp
L power:+6V #PWR?
U 1 1 5E7955A0
P 20100 10200
AR Path="/5BF41E62/5E7955A0" Ref="#PWR?"  Part="1" 
AR Path="/5E7955A0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 20100 10050 50  0001 C CNN
F 1 "+6V" H 20115 10373 50  0000 C CNN
F 2 "" H 20100 10200 50  0001 C CNN
F 3 "" H 20100 10200 50  0001 C CNN
	1    20100 10200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7955A7
P 20100 10350
AR Path="/5E7955A7" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7955A7" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7955A7" Ref="C?"  Part="1" 
AR Path="/5BF41E62/5E7955A7" Ref="C?"  Part="1" 
F 0 "C?" H 20215 10396 50  0000 L CNN
F 1 "1uF" H 20215 10305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 20138 10200 50  0001 C CNN
F 3 "~" H 20100 10350 50  0001 C CNN
F 4 "decoupling" H 20100 10350 50  0001 C CNN "purpose"
	1    20100 10350
	-1   0    0    -1  
$EndComp
Text Notes 16800 12300 0    59   ~ 0
Pull-down resistors: Actuators should be off by default.\n\nWhen the firmware is not running (for example during an update),\nthe microcontroller pins have a 85uA pull-up current enabled.\nThis would cause the actuators to start running unintentionally,\nWe avoid this by placing a strong pull-down resistor:\nR_pulldown = (0.5V/85uA)  -> R_puldown < 5.6k
$Comp
L Device:R R?
U 1 1 5E7955AF
P 17350 10950
AR Path="/5BF41E62/5E7955AF" Ref="R?"  Part="1" 
AR Path="/5E7955AF" Ref="R?"  Part="1" 
F 0 "R?" V 17550 10950 50  0000 C CNN
F 1 "4.7k" V 17450 10950 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 17280 10950 50  0001 C CNN
F 3 "~" H 17350 10950 50  0001 C CNN
F 4 "pull-down: disable actuator by default" V 17350 10950 50  0001 C CNN "purpose"
	1    17350 10950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7955B5
P 17350 11100
AR Path="/5BF41E62/5E7955B5" Ref="#PWR?"  Part="1" 
AR Path="/5E7955B5" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 17350 10850 50  0001 C CNN
F 1 "GND" H 17355 10927 50  0000 C CNN
F 2 "" H 17350 11100 50  0001 C CNN
F 3 "" H 17350 11100 50  0001 C CNN
	1    17350 11100
	1    0    0    -1  
$EndComp
Connection ~ 17350 10800
Wire Wire Line
	17350 10800 17450 10800
$Comp
L Connector:TestPoint TP?
U 1 1 5E7955CC
P 17800 10600
AR Path="/5BF2E340/5E7955CC" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7955CC" Ref="TP?"  Part="1" 
AR Path="/5E7955CC" Ref="TP?"  Part="1" 
F 0 "TP?" H 17850 10850 50  0000 L CNN
F 1 "valve_2_fet" H 17850 10750 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 18000 10600 50  0001 C CNN
F 3 "~" H 18000 10600 50  0001 C CNN
	1    17800 10600
	1    0    0    -1  
$EndComp
Wire Wire Line
	17800 10600 17800 10800
Connection ~ 17800 10800
Wire Wire Line
	17800 10800 17900 10800
Wire Wire Line
	19050 9900 19200 9900
Wire Wire Line
	18400 10600 19200 10600
$Comp
L Sensor_Pressure:MPXH6115A U?
U 1 1 5E7AB8E8
P 17950 2200
AR Path="/5BF41E5D/5E7AB8E8" Ref="U?"  Part="1" 
AR Path="/5E7AB8E8" Ref="U?"  Part="1" 
F 0 "U?" H 17520 2246 50  0000 R CNN
F 1 "TODO" H 17520 2155 50  0000 R CNN
F 2 "" H 17450 1850 50  0001 C CNN
F 3 "" H 17950 2800 50  0001 C CNN
	1    17950 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB8EE
P 17950 2500
AR Path="/5BF41E5D/5E7AB8EE" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB8EE" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 17950 2250 50  0001 C CNN
F 1 "GND" H 17955 2327 50  0000 C CNN
F 2 "" H 17950 2500 50  0001 C CNN
F 3 "" H 17950 2500 50  0001 C CNN
	1    17950 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB8F4
P 17250 1600
AR Path="/5BF2E340/5E7AB8F4" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB8F4" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB8F4" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 17250 1350 50  0001 C CNN
F 1 "GND" H 17255 1427 50  0000 C CNN
F 2 "" H 17250 1600 50  0001 C CNN
F 3 "" H 17250 1600 50  0001 C CNN
	1    17250 1600
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7AB8FB
P 17250 1450
AR Path="/5E7AB8FB" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7AB8FB" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB8FB" Ref="C?"  Part="1" 
F 0 "C?" H 17365 1496 50  0000 L CNN
F 1 "1uF" H 17365 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 17288 1300 50  0001 C CNN
F 3 "~" H 17250 1450 50  0001 C CNN
F 4 "decoupling" H 17250 1450 50  0001 C CNN "purpose"
	1    17250 1450
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7AB902
P 17750 1450
AR Path="/5E7AB902" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7AB902" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB902" Ref="C?"  Part="1" 
F 0 "C?" H 17865 1496 50  0000 L CNN
F 1 "100nF" H 17865 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 17788 1300 50  0001 C CNN
F 3 "~" H 17750 1450 50  0001 C CNN
F 4 "decoupling" H 17750 1450 50  0001 C CNN "purpose"
	1    17750 1450
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB908
P 17750 1600
AR Path="/5BF2E340/5E7AB908" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB908" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB908" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 17750 1350 50  0001 C CNN
F 1 "GND" H 17755 1427 50  0000 C CNN
F 2 "" H 17750 1600 50  0001 C CNN
F 3 "" H 17750 1600 50  0001 C CNN
	1    17750 1600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	17950 1300 17950 1900
Connection ~ 17250 1300
Wire Wire Line
	17250 1300 17750 1300
Connection ~ 17750 1300
Wire Wire Line
	17750 1300 17950 1300
$Comp
L Device:C C?
U 1 1 5E7AB914
P 18700 2350
AR Path="/5E7AB914" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7AB914" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB914" Ref="C?"  Part="1" 
F 0 "C?" H 18815 2396 50  0000 L CNN
F 1 "47pF" H 18815 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 18738 2200 50  0001 C CNN
F 3 "~" H 18700 2350 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 18700 2350 50  0001 C CNN "purpose"
	1    18700 2350
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB91A
P 18700 2500
AR Path="/5BF2E340/5E7AB91A" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB91A" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB91A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18700 2250 50  0001 C CNN
F 1 "GND" H 18705 2327 50  0000 C CNN
F 2 "" H 18700 2500 50  0001 C CNN
F 3 "" H 18700 2500 50  0001 C CNN
	1    18700 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	18350 2200 18700 2200
Connection ~ 18700 2200
Text Label 18350 2200 0    50   ~ 0
pressure_sensor_out
$Comp
L Device:R R?
U 1 1 5E7AB934
P 19800 2700
AR Path="/5BF41E62/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5E7AB934" Ref="R?"  Part="1" 
AR Path="/5E7AB934" Ref="R?"  Part="1" 
F 0 "R?" V 19593 2700 50  0000 C CNN
F 1 "100k" V 19684 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 19730 2700 50  0001 C CNN
F 3 "~" H 19800 2700 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 19800 2700 50  0001 C CNN "purpose"
	1    19800 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	19800 2500 19800 2550
$Comp
L power:GND #PWR?
U 1 1 5E7AB93C
P 19800 2850
AR Path="/5BF2E340/5E7AB93C" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB93C" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB93C" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB93C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 19800 2600 50  0001 C CNN
F 1 "GND" H 19805 2677 50  0000 C CNN
F 2 "" H 19800 2850 50  0001 C CNN
F 3 "" H 19800 2850 50  0001 C CNN
	1    19800 2850
	1    0    0    -1  
$EndComp
Text HLabel 21000 2550 2    50   Output ~ 0
pressure_level
$Comp
L Device:R R?
U 1 1 5E7AB944
P 19800 2350
AR Path="/5BF41E62/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5BF2E340/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5BF41E5D/5E7AB944" Ref="R?"  Part="1" 
AR Path="/5E7AB944" Ref="R?"  Part="1" 
F 0 "R?" V 19593 2350 50  0000 C CNN
F 1 "68k" V 19684 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 19730 2350 50  0001 C CNN
F 3 "~" H 19800 2350 50  0001 C CNN
F 4 "voltage divider: pressure to mcu (5V to 3V max)" V 19800 2350 50  0001 C CNN "purpose"
	1    19800 2350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AB94A
P 20750 2850
AR Path="/5BF2E340/5E7AB94A" Ref="#PWR?"  Part="1" 
AR Path="/5BF3D3D9/5E7AB94A" Ref="#PWR?"  Part="1" 
AR Path="/5BF41E5D/5E7AB94A" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB94A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 20750 2600 50  0001 C CNN
F 1 "GND" H 20755 2677 50  0000 C CNN
F 2 "" H 20750 2850 50  0001 C CNN
F 3 "" H 20750 2850 50  0001 C CNN
	1    20750 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7AB952
P 20750 2700
AR Path="/5E7AB952" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7AB952" Ref="C?"  Part="1" 
AR Path="/5BF41E5D/5E7AB952" Ref="C?"  Part="1" 
F 0 "C?" H 20500 2700 50  0000 L CNN
F 1 "2.2nF" H 20500 2600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 20788 2550 50  0001 C CNN
F 3 "~" H 20750 2700 50  0001 C CNN
F 4 "filter (see MPXH sensor datasheet)" H 20750 2700 50  0001 C CNN "purpose"
	1    20750 2700
	-1   0    0    -1  
$EndComp
Text Notes 19800 2100 0    59   ~ 0
5V to 3V divider.\nRC filter: 40kOhm, 2.2nF: Fc= 1.8Khz\n
Text HLabel 16550 1300 0    50   Input ~ 0
+5V
Wire Wire Line
	16550 1300 16750 1300
$Comp
L power:+5V #PWR?
U 1 1 5E7AB95B
P 16750 1300
AR Path="/5BF41E5D/5E7AB95B" Ref="#PWR?"  Part="1" 
AR Path="/5E7AB95B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 16750 1150 50  0001 C CNN
F 1 "+5V" H 16765 1473 50  0000 C CNN
F 2 "" H 16750 1300 50  0001 C CNN
F 3 "" H 16750 1300 50  0001 C CNN
	1    16750 1300
	1    0    0    -1  
$EndComp
Connection ~ 16750 1300
Wire Wire Line
	16750 1300 17250 1300
Connection ~ 20750 2550
Wire Wire Line
	20750 2550 21000 2550
Text Notes 20850 3000 0    50   ~ 0
Place close to\nADC input
$Comp
L Connector:TestPoint TP?
U 1 1 5E7AB966
P 19300 2000
AR Path="/5BF2E340/5E7AB966" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7AB966" Ref="TP?"  Part="1" 
AR Path="/5BF41E5D/5E7AB966" Ref="TP?"  Part="1" 
AR Path="/5E7AB966" Ref="TP?"  Part="1" 
F 0 "TP?" H 19350 2250 50  0000 L CNN
F 1 "sensor_out" H 19350 2150 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 19500 2000 50  0001 C CNN
F 3 "~" H 19500 2000 50  0001 C CNN
	1    19300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	19300 2000 19300 2200
$Comp
L Connector:TestPoint TP?
U 1 1 5E7AB96F
P 20450 2550
AR Path="/5BF2E340/5E7AB96F" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7AB96F" Ref="TP?"  Part="1" 
AR Path="/5BF41E5D/5E7AB96F" Ref="TP?"  Part="1" 
AR Path="/5E7AB96F" Ref="TP?"  Part="1" 
F 0 "TP?" H 20500 2800 50  0000 L CNN
F 1 "pressure_level" H 20500 2700 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 20650 2550 50  0001 C CNN
F 3 "~" H 20650 2550 50  0001 C CNN
	1    20450 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	20450 2550 20750 2550
Text HLabel 17200 5800 0    50   Input ~ 0
LED_CLK
$Comp
L power:GND #PWR?
U 1 1 5E7B5E03
P 18050 5900
AR Path="/5BF2E340/5E7B5E03" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E03" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E03" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18050 5650 50  0001 C CNN
F 1 "GND" H 18055 5727 50  0000 C CNN
F 2 "" H 18050 5900 50  0001 C CNN
F 3 "" H 18050 5900 50  0001 C CNN
	1    18050 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7B5E0A
P 18500 5350
AR Path="/5E7B5E0A" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7B5E0A" Ref="C?"  Part="1" 
AR Path="/5C0338CC/5E7B5E0A" Ref="C?"  Part="1" 
F 0 "C?" H 18615 5396 50  0000 L CNN
F 1 "100nF" H 18615 5305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 18538 5200 50  0001 C CNN
F 3 "~" H 18500 5350 50  0001 C CNN
F 4 "decoupling" H 18500 5350 50  0001 C CNN "purpose"
	1    18500 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7B5E10
P 18500 5500
AR Path="/5BF2E340/5E7B5E10" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E10" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E10" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18500 5250 50  0001 C CNN
F 1 "GND" H 18505 5327 50  0000 C CNN
F 2 "" H 18500 5500 50  0001 C CNN
F 3 "" H 18500 5500 50  0001 C CNN
	1    18500 5500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E16
P 18500 5200
AR Path="/5BF41E5D/5E7B5E16" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E16" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E16" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18500 5050 50  0001 C CNN
F 1 "+5V" H 18515 5373 50  0000 C CNN
F 2 "" H 18500 5200 50  0001 C CNN
F 3 "" H 18500 5200 50  0001 C CNN
	1    18500 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	17200 5800 17500 5800
Text Notes 16850 5000 0    59   ~ 12
3V to 5V level shifting
Text Label 19300 6400 0    50   ~ 0
LED_clock_5V
Text Label 19300 6500 0    50   ~ 0
LED_data_5V
$Comp
L 74xGxx:74AHCT1G125 U?
U 1 1 5E7B5E20
P 18000 5800
AR Path="/5C0338CC/5E7B5E20" Ref="U?"  Part="1" 
AR Path="/5E7B5E20" Ref="U?"  Part="1" 
F 0 "U?" H 17900 5450 50  0000 C CNN
F 1 "74AHCT1G125SE" H 17700 5350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 18000 5800 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1464459.pdf" H 18000 5800 50  0001 C CNN
	1    18000 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	18050 5750 18050 5650
Wire Wire Line
	18050 5650 18150 5650
Wire Wire Line
	18050 5850 18050 5900
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E29
P 18150 5650
AR Path="/5BF41E5D/5E7B5E29" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E29" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E29" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18150 5500 50  0001 C CNN
F 1 "+5V" H 18165 5823 50  0000 C CNN
F 2 "" H 18150 5650 50  0001 C CNN
F 3 "" H 18150 5650 50  0001 C CNN
	1    18150 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	18000 5600 18000 5300
Wire Wire Line
	18000 5300 17500 5300
Text HLabel 17200 5300 0    50   Input ~ 0
LED_~CS~
Text Label 17600 5300 0    50   ~ 0
LED_~CS~
Text HLabel 17200 7100 0    50   Input ~ 0
LED_MOSI
$Comp
L power:GND #PWR?
U 1 1 5E7B5E34
P 18050 7200
AR Path="/5BF2E340/5E7B5E34" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E34" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E34" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18050 6950 50  0001 C CNN
F 1 "GND" H 18055 7027 50  0000 C CNN
F 2 "" H 18050 7200 50  0001 C CNN
F 3 "" H 18050 7200 50  0001 C CNN
	1    18050 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7B5E3B
P 18500 6650
AR Path="/5E7B5E3B" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7B5E3B" Ref="C?"  Part="1" 
AR Path="/5C0338CC/5E7B5E3B" Ref="C?"  Part="1" 
F 0 "C?" H 18615 6696 50  0000 L CNN
F 1 "100nF" H 18615 6605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 18538 6500 50  0001 C CNN
F 3 "~" H 18500 6650 50  0001 C CNN
F 4 "decoupling" H 18500 6650 50  0001 C CNN "purpose"
	1    18500 6650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7B5E41
P 18500 6800
AR Path="/5BF2E340/5E7B5E41" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E41" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E41" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18500 6550 50  0001 C CNN
F 1 "GND" H 18505 6627 50  0000 C CNN
F 2 "" H 18500 6800 50  0001 C CNN
F 3 "" H 18500 6800 50  0001 C CNN
	1    18500 6800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E47
P 18500 6500
AR Path="/5BF41E5D/5E7B5E47" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E47" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E47" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18500 6350 50  0001 C CNN
F 1 "+5V" H 18515 6673 50  0000 C CNN
F 2 "" H 18500 6500 50  0001 C CNN
F 3 "" H 18500 6500 50  0001 C CNN
	1    18500 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	17200 7100 17500 7100
$Comp
L 74xGxx:74AHCT1G125 U?
U 1 1 5E7B5E4E
P 18000 7100
AR Path="/5C0338CC/5E7B5E4E" Ref="U?"  Part="1" 
AR Path="/5E7B5E4E" Ref="U?"  Part="1" 
F 0 "U?" H 17500 6950 50  0000 C CNN
F 1 "74AHCT1G125SE" H 17700 6850 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 18000 7100 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1464459.pdf" H 18000 7100 50  0001 C CNN
	1    18000 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	18050 7050 18050 6950
Wire Wire Line
	18050 6950 18150 6950
Wire Wire Line
	18050 7150 18050 7200
$Comp
L power:+5V #PWR?
U 1 1 5E7B5E57
P 18150 6950
AR Path="/5BF41E5D/5E7B5E57" Ref="#PWR?"  Part="1" 
AR Path="/5C0338CC/5E7B5E57" Ref="#PWR?"  Part="1" 
AR Path="/5E7B5E57" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 18150 6800 50  0001 C CNN
F 1 "+5V" H 18165 7123 50  0000 C CNN
F 2 "" H 18150 6950 50  0001 C CNN
F 3 "" H 18150 6950 50  0001 C CNN
	1    18150 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	18000 6900 18000 6600
Wire Wire Line
	18000 6600 17600 6600
Text Label 17600 6600 0    50   ~ 0
LED_~CS~
Wire Wire Line
	19000 5800 19000 6400
Wire Wire Line
	19000 6400 20100 6400
Wire Wire Line
	18250 5800 18950 5800
Wire Wire Line
	19000 6500 19000 7100
Wire Wire Line
	19000 6500 20100 6500
Wire Wire Line
	18250 7100 18950 7100
Wire Notes Line
	19200 4750 16750 4750
Wire Notes Line
	16750 4750 16750 7600
Wire Notes Line
	16750 7600 19200 7600
Wire Notes Line
	19200 7600 19200 4750
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E6A
P 18950 5800
AR Path="/5BF2E340/5E7B5E6A" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E6A" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E6A" Ref="TP?"  Part="1" 
AR Path="/5E7B5E6A" Ref="TP?"  Part="1" 
F 0 "TP?" H 18900 5700 50  0000 R CNN
F 1 "LED_clk_5V" H 18900 5600 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 19150 5800 50  0001 C CNN
F 3 "~" H 19150 5800 50  0001 C CNN
	1    18950 5800
	1    0    0    -1  
$EndComp
Connection ~ 18950 5800
Wire Wire Line
	18950 5800 19000 5800
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E72
P 18950 7100
AR Path="/5BF2E340/5E7B5E72" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E72" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E72" Ref="TP?"  Part="1" 
AR Path="/5E7B5E72" Ref="TP?"  Part="1" 
F 0 "TP?" H 19000 7350 50  0000 L CNN
F 1 "LED_data_5V" H 19000 7250 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 19150 7100 50  0001 C CNN
F 3 "~" H 19150 7100 50  0001 C CNN
	1    18950 7100
	-1   0    0    1   
$EndComp
Connection ~ 18950 7100
Wire Wire Line
	18950 7100 19000 7100
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E7A
P 17500 5300
AR Path="/5BF2E340/5E7B5E7A" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E7A" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E7A" Ref="TP?"  Part="1" 
AR Path="/5E7B5E7A" Ref="TP?"  Part="1" 
F 0 "TP?" H 17550 5550 50  0000 L CNN
F 1 "LED_~CS~" H 17550 5450 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 17700 5300 50  0001 C CNN
F 3 "~" H 17700 5300 50  0001 C CNN
	1    17500 5300
	-1   0    0    1   
$EndComp
Connection ~ 17500 5300
Wire Wire Line
	17500 5300 17200 5300
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E82
P 17500 5800
AR Path="/5BF2E340/5E7B5E82" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E82" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E82" Ref="TP?"  Part="1" 
AR Path="/5E7B5E82" Ref="TP?"  Part="1" 
F 0 "TP?" H 17550 6050 50  0000 L CNN
F 1 "LED_CLK" H 17550 5950 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 17700 5800 50  0001 C CNN
F 3 "~" H 17700 5800 50  0001 C CNN
	1    17500 5800
	-1   0    0    1   
$EndComp
Connection ~ 17500 5800
Wire Wire Line
	17500 5800 17700 5800
$Comp
L Connector:TestPoint TP?
U 1 1 5E7B5E8A
P 17500 7100
AR Path="/5BF2E340/5E7B5E8A" Ref="TP?"  Part="1" 
AR Path="/5BF41E62/5E7B5E8A" Ref="TP?"  Part="1" 
AR Path="/5C0338CC/5E7B5E8A" Ref="TP?"  Part="1" 
AR Path="/5E7B5E8A" Ref="TP?"  Part="1" 
F 0 "TP?" H 17400 7400 50  0000 R CNN
F 1 "LED_MOSI" H 17400 7300 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 17700 7100 50  0001 C CNN
F 3 "~" H 17700 7100 50  0001 C CNN
	1    17500 7100
	1    0    0    -1  
$EndComp
Connection ~ 17500 7100
Wire Wire Line
	17500 7100 17700 7100
Wire Wire Line
	5650 5050 5650 5200
$Comp
L power:GND #PWR?
U 1 1 5E7D4AE3
P 5650 5200
AR Path="/5BF2E340/5E7D4AE3" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4AE3" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5650 4950 50  0001 C CNN
F 1 "GND" H 5655 5027 50  0000 C CNN
F 2 "" H 5650 5200 50  0001 C CNN
F 3 "" H 5650 5200 50  0001 C CNN
	1    5650 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4AE9
P 7650 4850
AR Path="/5BF2E340/5E7D4AE9" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4AE9" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7650 4600 50  0001 C CNN
F 1 "GND" H 7655 4677 50  0000 C CNN
F 2 "" H 7650 4850 50  0001 C CNN
F 3 "" H 7650 4850 50  0001 C CNN
	1    7650 4850
	1    0    0    -1  
$EndComp
Text Label 4450 3850 0    50   ~ 0
SWDIO
Text Label 8100 4250 0    50   ~ 0
USB_DN
Text Label 8100 3900 0    50   ~ 0
USB_DP
$Comp
L Device:R R?
U 1 1 5E7D4AF3
P 7500 3900
AR Path="/5BF2E340/5E7D4AF3" Ref="R?"  Part="1" 
AR Path="/5E7D4AF3" Ref="R?"  Part="1" 
F 0 "R?" H 7570 3946 50  0000 L CNN
F 1 "33R" H 7570 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7430 3900 50  0001 C CNN
F 3 "~" H 7500 3900 50  0001 C CNN
	1    7500 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E7D4AF9
P 7500 4250
AR Path="/5BF2E340/5E7D4AF9" Ref="R?"  Part="1" 
AR Path="/5E7D4AF9" Ref="R?"  Part="1" 
F 0 "R?" H 7570 4296 50  0000 L CNN
F 1 "33R" H 7570 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7430 4250 50  0001 C CNN
F 3 "~" H 7500 4250 50  0001 C CNN
	1    7500 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 4150 7200 3900
Wire Wire Line
	7200 3900 7350 3900
Wire Wire Line
	7650 3900 7950 3900
Wire Wire Line
	7650 4250 8450 4250
$Comp
L Device:R R?
U 1 1 5E7D4B03
P 7950 3750
AR Path="/5BF2E340/5E7D4B03" Ref="R?"  Part="1" 
AR Path="/5E7D4B03" Ref="R?"  Part="1" 
F 0 "R?" H 8020 3796 50  0000 L CNN
F 1 "1k5" H 8020 3705 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7880 3750 50  0001 C CNN
F 3 "~" H 7950 3750 50  0001 C CNN
	1    7950 3750
	-1   0    0    1   
$EndComp
Connection ~ 7950 3900
Wire Wire Line
	7950 3900 8450 3900
$Comp
L Jitter_Components:+3V #PWR?
U 1 1 5E7D4B12
P 7950 3600
AR Path="/5BF2E340/5E7D4B12" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B12" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7950 3450 50  0001 C CNN
F 1 "+3V" H 7965 3773 50  0000 C CNN
F 2 "" H 7950 3600 50  0001 C CNN
F 3 "" H 7950 3600 50  0001 C CNN
	1    7950 3600
	1    0    0    -1  
$EndComp
Text Notes 17000 8800 0    101  Italic 20
Actuator control
Wire Wire Line
	5550 5050 5650 5050
Wire Wire Line
	4450 3850 4950 3850
Wire Wire Line
	4950 4550 4450 4550
Text Label 17900 9250 2    50   ~ 0
pwm_1
Text Label 17900 9000 2    50   ~ 0
pwm_2
Text Label 17900 9100 2    50   ~ 0
pwm_3
Text Label 6850 3550 2    50   ~ 0
UART_TX
Wire Notes Line
	16800 8500 18800 8500
Wire Notes Line
	18800 8500 18800 9400
Wire Notes Line
	18800 9400 16800 9400
Wire Notes Line
	16800 9400 16800 8500
$Comp
L power:GND #PWR?
U 1 1 5E7D4B7C
P 6950 4950
AR Path="/5BF2E340/5E7D4B7C" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B7C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6950 4700 50  0001 C CNN
F 1 "GND" H 6955 4777 50  0000 C CNN
F 2 "" H 6950 4950 50  0001 C CNN
F 3 "" H 6950 4950 50  0001 C CNN
	1    6950 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4B82
P 7350 4950
AR Path="/5BF2E340/5E7D4B82" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B82" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7350 4700 50  0001 C CNN
F 1 "GND" H 7355 4777 50  0000 C CNN
F 2 "" H 7350 4950 50  0001 C CNN
F 3 "" H 7350 4950 50  0001 C CNN
	1    7350 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4650 6700 4650
Wire Wire Line
	6700 4650 6700 5350
Wire Wire Line
	6700 5350 7150 5350
Wire Wire Line
	7150 5350 7150 5100
$Comp
L Device:C C?
U 1 1 5E7D4B8D
P 7150 5500
AR Path="/5E7D4B8D" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7D4B8D" Ref="C?"  Part="1" 
F 0 "C?" H 7265 5546 50  0000 L CNN
F 1 "18pF" H 7265 5455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7188 5350 50  0001 C CNN
F 3 "~" H 7150 5500 50  0001 C CNN
F 4 "crystal matching (see LPC11u3X datasheet)" H 7150 5500 50  0001 C CNN "purpose"
	1    7150 5500
	1    0    0    -1  
$EndComp
Connection ~ 7150 5350
$Comp
L power:GND #PWR?
U 1 1 5E7D4B94
P 7150 5650
AR Path="/5BF2E340/5E7D4B94" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B94" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7150 5400 50  0001 C CNN
F 1 "GND" H 7155 5477 50  0000 C CNN
F 2 "" H 7150 5650 50  0001 C CNN
F 3 "" H 7150 5650 50  0001 C CNN
	1    7150 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7D4B9B
P 7650 4700
AR Path="/5E7D4B9B" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7D4B9B" Ref="C?"  Part="1" 
F 0 "C?" H 7765 4746 50  0000 L CNN
F 1 "18pF" H 7765 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7688 4550 50  0001 C CNN
F 3 "~" H 7650 4700 50  0001 C CNN
F 4 "crystal matching (see LPC11u3X datasheet)" H 7650 4700 50  0001 C CNN "purpose"
	1    7650 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4550 7150 4800
Wire Wire Line
	7150 4550 7650 4550
Connection ~ 7150 4550
$Comp
L Device:Crystal_GND24 Y?
U 1 1 5E7D4BA8
P 7150 4950
AR Path="/5BF2E340/5E7D4BA8" Ref="Y?"  Part="1" 
AR Path="/5E7D4BA8" Ref="Y?"  Part="1" 
F 0 "Y?" V 7000 5050 50  0000 L CNN
F 1 "MCSJK-7U-12.00-10-10-80-B-10" V 7450 5100 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_3225-4Pin_3.2x2.5mm" H 7150 4950 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2645227.pdf?_ga=2.101838344.844808790.1542789852-389210046.1542789852" H 7150 4950 50  0001 C CNN
F 4 "10pF" V 7150 4950 50  0001 C CNN "Load capacitance"
F 5 "80 Ohm" V 7150 4950 50  0001 C CNN "ESR"
F 6 "18pF (see LPC11U3XX datasheet)" V 7150 4950 50  0001 C CNN "Required capacitor value"
F 7 "3225-size crystal, ESR<160,see LPC11U3XX datasheet" V 7150 4950 50  0001 C CNN "alternative"
	1    7150 4950
	0    1    1    0   
$EndComp
Text Label 6350 4550 0    50   ~ 0
XTAL_IN
Text Label 6350 4650 0    50   ~ 0
XTAL_OUT
Text Notes 18700 9100 2    50   ~ 0
CT16B0_MAT0
Text Notes 18700 9000 2    50   ~ 0
CT16B0_MAT1
Text Notes 18700 9250 2    50   ~ 0
CT16B1_MAT1
Wire Wire Line
	6350 4250 7350 4250
NoConn ~ 6350 3550
Wire Wire Line
	6350 4550 7150 4550
Wire Wire Line
	6350 4150 7200 4150
Wire Wire Line
	6350 3550 6850 3550
Wire Wire Line
	4950 2450 3900 2450
Connection ~ 4200 1800
Wire Wire Line
	4400 1800 4400 2350
Wire Wire Line
	4200 1800 4400 1800
$Comp
L Connector:TestPoint TP?
U 1 1 5E7D4C23
P 4200 1800
AR Path="/5BF2E340/5E7D4C23" Ref="TP?"  Part="1" 
AR Path="/5E7D4C23" Ref="TP?"  Part="1" 
F 0 "TP?" H 4250 2050 50  0000 L CNN
F 1 "Reset" H 4250 1950 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 4400 1800 50  0001 C CNN
F 3 "~" H 4400 1800 50  0001 C CNN
	1    4200 1800
	1    0    0    -1  
$EndComp
Text Notes 6900 3550 0    50   ~ 0
Optional:\nUART header?
NoConn ~ 6350 3450
$Comp
L Jitter_Components:+3V #PWR?
U 1 1 5E7D4C33
P 4100 2750
AR Path="/5BF2E340/5E7D4C33" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C33" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4100 2600 50  0001 C CNN
F 1 "+3V" H 4115 2923 50  0000 C CNN
F 2 "" H 4100 2750 50  0001 C CNN
F 3 "" H 4100 2750 50  0001 C CNN
	1    4100 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1300 6300 1300
Connection ~ 5850 1300
$Comp
L power:GND #PWR?
U 1 1 5E7D4C3B
P 5850 1600
AR Path="/5BF2E340/5E7D4C3B" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C3B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5850 1350 50  0001 C CNN
F 1 "GND" H 5855 1427 50  0000 C CNN
F 2 "" H 5850 1600 50  0001 C CNN
F 3 "" H 5850 1600 50  0001 C CNN
	1    5850 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D4C41
P 6300 1600
AR Path="/5BF2E340/5E7D4C41" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C41" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6300 1350 50  0001 C CNN
F 1 "GND" H 6305 1427 50  0000 C CNN
F 2 "" H 6300 1600 50  0001 C CNN
F 3 "" H 6300 1600 50  0001 C CNN
	1    6300 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1300 6550 1300
Connection ~ 6300 1300
$Comp
L Device:C C?
U 1 1 5E7D4C4A
P 6300 1450
AR Path="/5E7D4C4A" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7D4C4A" Ref="C?"  Part="1" 
F 0 "C?" H 6415 1496 50  0000 L CNN
F 1 "100nF" H 6415 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6338 1300 50  0001 C CNN
F 3 "~" H 6300 1450 50  0001 C CNN
F 4 "decoupling" H 6300 1450 50  0001 C CNN "purpose"
	1    6300 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7D4C51
P 5850 1450
AR Path="/5E7D4C51" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7D4C51" Ref="C?"  Part="1" 
F 0 "C?" H 5965 1496 50  0000 L CNN
F 1 "100nF" H 5965 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5888 1300 50  0001 C CNN
F 3 "~" H 5850 1450 50  0001 C CNN
F 4 "decoupling" H 5850 1450 50  0001 C CNN "purpose"
	1    5850 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1300 5850 1300
$Comp
L Device:C C?
U 1 1 5E7D4C59
P 6800 1450
AR Path="/5E7D4C59" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7D4C59" Ref="C?"  Part="1" 
F 0 "C?" H 6915 1496 50  0000 L CNN
F 1 "1uF" H 6915 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6838 1300 50  0001 C CNN
F 3 "~" H 6800 1450 50  0001 C CNN
F 4 "decoupling" H 6800 1450 50  0001 C CNN "purpose"
	1    6800 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1800 4200 1800
Wire Wire Line
	4400 2350 4950 2350
$Comp
L power:GND #PWR?
U 1 1 5E7D4C61
P 4000 2100
AR Path="/5BF2E340/5E7D4C61" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C61" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4000 1850 50  0001 C CNN
F 1 "GND" H 4005 1927 50  0000 C CNN
F 2 "" H 4000 2100 50  0001 C CNN
F 3 "" H 4000 2100 50  0001 C CNN
	1    4000 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7D4C69
P 4000 1950
AR Path="/5E7D4C69" Ref="C?"  Part="1" 
AR Path="/5BF2E340/5E7D4C69" Ref="C?"  Part="1" 
F 0 "C?" H 4115 1996 50  0000 L CNN
F 1 "2.2nF" H 4115 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4038 1800 50  0001 C CNN
F 3 "~" H 4000 1950 50  0001 C CNN
F 4 "reset debounce/protection" H 4000 1950 50  0001 C CNN "purpose"
F 5 "rc time must be faster than boot_ISP" H 4000 1950 50  0001 C CNN "Note"
	1    4000 1950
	1    0    0    -1  
$EndComp
Text Label 6850 3450 2    50   ~ 0
UART_RX
Wire Wire Line
	6350 3450 6850 3450
Wire Wire Line
	6350 2350 6850 2350
Wire Wire Line
	6350 2450 6850 2450
Text Label 3900 2450 0    50   ~ 0
button_~ISP~
Text Notes 4450 2450 0    50   ~ 0
(boot_~ISP~)
Wire Wire Line
	4300 2650 4950 2650
Wire Wire Line
	4300 2750 4300 2650
Wire Wire Line
	4100 2750 4300 2750
Text Notes 4450 2650 0    50   ~ 0
(USB boot)
Text Notes 4450 2850 0    50   ~ 0
(open drain)
Text Notes 4450 2750 0    50   ~ 0
(open drain)
Wire Wire Line
	6550 1300 6800 1300
Connection ~ 6550 1300
$Comp
L Jitter_Components:+3V #PWR?
U 1 1 5E7D4C8D
P 6550 1300
AR Path="/5BF2E340/5E7D4C8D" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C8D" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6550 1150 50  0001 C CNN
F 1 "+3V" H 6565 1473 50  0000 C CNN
F 2 "" H 6550 1300 50  0001 C CNN
F 3 "" H 6550 1300 50  0001 C CNN
	1    6550 1300
	1    0    0    -1  
$EndComp
Text Notes 4450 2350 0    50   ~ 0
(reset)
NoConn ~ 4950 2850
NoConn ~ 4950 2750
Text Label 4450 3350 0    50   ~ 0
SWCLK
Wire Wire Line
	4950 3350 4450 3350
$Comp
L power:GND #PWR?
U 1 1 5E7D4C9E
P 6800 1600
AR Path="/5BF2E340/5E7D4C9E" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4C9E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6800 1350 50  0001 C CNN
F 1 "GND" H 6805 1427 50  0000 C CNN
F 2 "" H 6800 1600 50  0001 C CNN
F 3 "" H 6800 1600 50  0001 C CNN
	1    6800 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2050 5150 1300
Text Label 750  5600 0    50   ~ 0
Vbus
Connection ~ 5650 5050
Wire Wire Line
	5650 2050 5550 2050
Wire Wire Line
	5550 2050 5150 2050
Connection ~ 5550 2050
$Comp
L MCU_NXP_LPC:LPC11U37FBD48-401_ U?
U 1 1 5E7D4C16
P 5650 3550
AR Path="/5BF2E340/5E7D4C16" Ref="U?"  Part="1" 
AR Path="/5E7D4C16" Ref="U?"  Part="1" 
F 0 "U?" H 5650 5228 50  0000 C CNN
F 1 "LPC11U37FBD48-401_" H 5650 5137 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 6500 5050 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/LPC11U3X.pdf" H 5650 2075 50  0001 C CNN
	1    5650 3550
	1    0    0    -1  
$EndComp
Text Label 16950 10800 0    50   ~ 0
pwm_1
Wire Wire Line
	16950 10800 17350 10800
Text Label 4450 4550 0    50   ~ 0
pwm_1
Text Label 6850 2350 2    50   ~ 0
pwm_3
Text Label 6850 2450 2    50   ~ 0
pwm_2
Wire Wire Line
	18700 2200 19300 2200
Wire Wire Line
	20450 2550 19800 2550
Connection ~ 20450 2550
Connection ~ 19800 2550
Wire Wire Line
	19300 2200 19800 2200
Connection ~ 19300 2200
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5E7D4B23
P 1000 4600
AR Path="/5BF2E340/5E7D4B23" Ref="J?"  Part="1" 
AR Path="/5E7D4B23" Ref="J?"  Part="1" 
F 0 "J?" H 1000 4200 50  0000 C CNN
F 1 "TODO" H 1050 4300 50  0000 C CNN
F 2 "Jitter_Footprints:header_4x2.54_right_angle" H 1000 4600 50  0001 C CNN
F 3 "~" H 1000 4600 50  0001 C CNN
	1    1000 4600
	-1   0    0    1   
$EndComp
Text Label 1800 4600 0    50   ~ 0
SWCLK
Text Label 1800 4500 0    50   ~ 0
SWDIO
$Comp
L power:GND #PWR?
U 1 1 5E7D4B1B
P 2050 4700
AR Path="/5BF2E340/5E7D4B1B" Ref="#PWR?"  Part="1" 
AR Path="/5E7D4B1B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2050 4450 50  0001 C CNN
F 1 "GND" H 2055 4527 50  0000 C CNN
F 2 "" H 2050 4700 50  0001 C CNN
F 3 "" H 2050 4700 50  0001 C CNN
	1    2050 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 4600 2050 4600
Wire Wire Line
	1200 4700 2050 4700
Wire Wire Line
	1200 4500 2050 4500
Text Notes 2100 4100 2    101  Italic 20
Debugging: SWD\n(optional)
$Comp
L Jitter_Components:+3V #PWR?
U 1 1 5E8F9DF0
P 1200 4400
AR Path="/5BF2E340/5E8F9DF0" Ref="#PWR?"  Part="1" 
AR Path="/5E8F9DF0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1200 4250 50  0001 C CNN
F 1 "+3V" H 1215 4573 50  0000 C CNN
F 2 "" H 1200 4400 50  0001 C CNN
F 3 "" H 1200 4400 50  0001 C CNN
	1    1200 4400
	-1   0    0    -1  
$EndComp
Wire Notes Line
	650  800  650  3400
Wire Notes Line
	650  3400 3050 3400
Wire Notes Line
	3050 3400 3050 800 
Wire Notes Line
	3050 800  650  800 
Text Notes 750  1050 0    101  Italic 20
USB
Text Notes 1850 950  0    50   ~ 0
TODO what current value?
Text Notes 16650 700  0    197  ~ 0
Mogelijk handige bouwblokjes
$EndSCHEMATC
