EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:a4985
LIBS:ad5543
LIBS:ad7683
LIBS:ad8610
LIBS:ad8620
LIBS:adg5204
LIBS:adr4533
LIBS:adt7410
LIBS:bat54s
LIBS:cp2102
LIBS:crystal-4pin
LIBS:lb1930mc
LIBS:m24c02
LIBS:mcp1703t-3302e
LIBS:mini-usb-b
LIBS:my_comps
LIBS:my-ncp1117st50t3g
LIBS:ncp3063
LIBS:ref196
LIBS:spartan-sip-9007
LIBS:stepper_conn
LIBS:stm32f100rct6b
LIBS:stm32f103cbt6
LIBS:stm32f105r8t6
LIBS:stm32f405rgt6
LIBS:ts881
LIBS:tsv734ipt
LIBS:tsz124ipt
LIBS:amg_preamp-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TSZ124IPT U1
U 1 1 5BA0610B
P 3275 2700
AR Path="/5BA0610B" Ref="U1"  Part="1" 
AR Path="/5BA195B0/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA1547E/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA1C551/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA1C582/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA254FD/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA2552E/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA2555F/5BA0610B" Ref="U?"  Part="1" 
F 0 "U1" H 3375 2500 60  0000 C CNN
F 1 "TSZ124IPT" H 3525 2900 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 3275 2700 60  0001 C CNN
F 3 "" H 3275 2700 60  0001 C CNN
	1    3275 2700
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5BA0610C
P 4225 3775
F 0 "C5" H 4250 3875 50  0000 L CNN
F 1 "2n2" H 4250 3675 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4263 3625 50  0001 C CNN
F 3 "" H 4225 3775 50  0001 C CNN
	1    4225 3775
	1    0    0    -1  
$EndComp
$Comp
L VDDA #PWR01
U 1 1 5BA0610D
P 3225 2150
F 0 "#PWR01" H 3225 2000 50  0001 C CNN
F 1 "VDDA" H 3225 2300 50  0000 C CNN
F 2 "" H 3225 2150 50  0001 C CNN
F 3 "" H 3225 2150 50  0001 C CNN
	1    3225 2150
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR02
U 1 1 5BA0610E
P 3225 3250
F 0 "#PWR02" H 3225 3000 50  0001 C CNN
F 1 "GNDA" H 3225 3100 50  0000 C CNN
F 2 "" H 3225 3250 50  0001 C CNN
F 3 "" H 3225 3250 50  0001 C CNN
	1    3225 3250
	1    0    0    -1  
$EndComp
$Comp
L VDDA #PWR03
U 1 1 5BA0610F
P 4225 3450
F 0 "#PWR03" H 4225 3300 50  0001 C CNN
F 1 "VDDA" H 4225 3600 50  0000 C CNN
F 2 "" H 4225 3450 50  0001 C CNN
F 3 "" H 4225 3450 50  0001 C CNN
	1    4225 3450
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR04
U 1 1 5BA06110
P 4225 4125
F 0 "#PWR04" H 4225 3875 50  0001 C CNN
F 1 "GNDA" H 4225 3975 50  0000 C CNN
F 2 "" H 4225 4125 50  0001 C CNN
F 3 "" H 4225 4125 50  0001 C CNN
	1    4225 4125
	1    0    0    -1  
$EndComp
$Comp
L TSZ124IPT U1
U 2 1 5BA06111
P 3275 4700
AR Path="/5BA06111" Ref="U1"  Part="2" 
AR Path="/5BA195B0/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA1547E/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA1C551/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA1C582/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA254FD/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA2552E/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA2555F/5BA06111" Ref="U?"  Part="2" 
F 0 "U1" H 3375 4500 60  0000 C CNN
F 1 "TSZ124IPT" H 3525 4900 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 3275 4700 60  0001 C CNN
F 3 "" H 3275 4700 60  0001 C CNN
	2    3275 4700
	1    0    0    1   
$EndComp
$Comp
L R R7
U 1 1 5BA06112
P 2625 3925
F 0 "R7" V 2705 3925 50  0000 C CNN
F 1 "150 1%" V 2625 3925 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2555 3925 30  0001 C CNN
F 3 "" H 2625 3925 30  0000 C CNN
	1    2625 3925
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5BA06113
P 3250 3600
F 0 "R8" V 3330 3600 50  0000 C CNN
F 1 "47k1%" V 3250 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3180 3600 30  0001 C CNN
F 3 "" H 3250 3600 30  0000 C CNN
	1    3250 3600
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 5BA06114
P 3250 4225
F 0 "R9" V 3330 4225 50  0000 C CNN
F 1 "47k1%" V 3250 4225 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3180 4225 30  0001 C CNN
F 3 "" H 3250 4225 30  0000 C CNN
	1    3250 4225
	0    1    1    0   
$EndComp
$Comp
L TSZ124IPT U1
U 4 1 5BA06115
P 5325 3900
AR Path="/5BA06115" Ref="U1"  Part="4" 
AR Path="/5BA195B0/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA1547E/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA1C551/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA1C582/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA254FD/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA2552E/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA2555F/5BA06115" Ref="U?"  Part="3" 
F 0 "U1" H 5425 3700 60  0000 C CNN
F 1 "TSZ124IPT" H 5575 4100 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 5325 3900 60  0001 C CNN
F 3 "" H 5325 3900 60  0001 C CNN
	4    5325 3900
	1    0    0    1   
$EndComp
$Comp
L R R10
U 1 1 5BA06116
P 4075 2700
F 0 "R10" V 4155 2700 50  0000 C CNN
F 1 "10k 1%" V 4075 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4005 2700 30  0001 C CNN
F 3 "" H 4075 2700 30  0000 C CNN
	1    4075 2700
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 5BA06117
P 5150 4700
F 0 "R13" V 5230 4700 50  0000 C CNN
F 1 "10k 1%" V 5150 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5080 4700 30  0001 C CNN
F 3 "" H 5150 4700 30  0000 C CNN
	1    5150 4700
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 5BA06118
P 4075 4700
F 0 "R11" V 4155 4700 50  0000 C CNN
F 1 "10k 1%" V 4075 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4005 4700 30  0001 C CNN
F 3 "" H 4075 4700 30  0000 C CNN
	1    4075 4700
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 5BA06119
P 5150 2700
F 0 "R12" V 5230 2700 50  0000 C CNN
F 1 "10k 1%" V 5150 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5080 2700 30  0001 C CNN
F 3 "" H 5150 2700 30  0000 C CNN
	1    5150 2700
	0    -1   -1   0   
$EndComp
$Comp
L TSZ124IPT U1
U 3 1 5BA0611A
P 7975 3750
AR Path="/5BA0611A" Ref="U1"  Part="3" 
AR Path="/5BA195B0/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA1547E/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA1C551/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA1C582/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA254FD/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA2552E/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA2555F/5BA0611A" Ref="U?"  Part="4" 
F 0 "U1" H 8075 3550 60  0000 C CNN
F 1 "TSZ124IPT" H 8225 3950 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 7975 3750 60  0001 C CNN
F 3 "" H 7975 3750 60  0001 C CNN
	3    7975 3750
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 5BA0611B
P 7150 3900
F 0 "R14" V 7230 3900 50  0000 C CNN
F 1 "1k 1%" V 7150 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7080 3900 30  0001 C CNN
F 3 "" H 7150 3900 30  0000 C CNN
	1    7150 3900
	0    -1   -1   0   
$EndComp
$Comp
L R R15
U 1 1 5BA0611C
P 7900 4425
F 0 "R15" V 7980 4425 50  0000 C CNN
F 1 "100k 1%" V 7900 4425 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7830 4425 30  0001 C CNN
F 3 "" H 7900 4425 30  0000 C CNN
	1    7900 4425
	0    -1   -1   0   
$EndComp
$Comp
L C C6
U 1 1 5BA0611D
P 7925 4750
F 0 "C6" H 7950 4850 50  0000 L CNN
F 1 "100n" H 7950 4650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7963 4600 50  0001 C CNN
F 3 "" H 7925 4750 50  0001 C CNN
	1    7925 4750
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 5BA0611E
P 2225 2750
F 0 "C3" H 2250 2850 50  0000 L CNN
F 1 "100n" H 2250 2650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2263 2600 30  0001 C CNN
F 3 "" H 2225 2750 60  0000 C CNN
	1    2225 2750
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR05
U 1 1 5BA0611F
P 2225 3000
F 0 "#PWR05" H 2225 2750 50  0001 C CNN
F 1 "GNDA" H 2225 2850 50  0000 C CNN
F 2 "" H 2225 3000 50  0001 C CNN
F 3 "" H 2225 3000 50  0001 C CNN
	1    2225 3000
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5BA06120
P 2225 5100
F 0 "C4" H 2250 5200 50  0000 L CNN
F 1 "100n" H 2250 5000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2263 4950 30  0001 C CNN
F 3 "" H 2225 5100 60  0000 C CNN
	1    2225 5100
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR06
U 1 1 5BA06121
P 2225 5350
F 0 "#PWR06" H 2225 5100 50  0001 C CNN
F 1 "GNDA" H 2225 5200 50  0000 C CNN
F 2 "" H 2225 5350 50  0001 C CNN
F 3 "" H 2225 5350 50  0001 C CNN
	1    2225 5350
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5BA06122
P 1875 2550
F 0 "R5" V 1955 2550 50  0000 C CNN
F 1 "1k5 1%" V 1875 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1805 2550 30  0001 C CNN
F 3 "" H 1875 2550 30  0000 C CNN
	1    1875 2550
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5BA06123
P 1625 2275
F 0 "R3" V 1705 2275 50  0000 C CNN
F 1 "1M 1%" V 1625 2275 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1555 2275 30  0001 C CNN
F 3 "" H 1625 2275 30  0000 C CNN
	1    1625 2275
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 5BA06124
P 1875 4850
F 0 "R6" V 1955 4850 50  0000 C CNN
F 1 "1k5 1%" V 1875 4850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1805 4850 30  0001 C CNN
F 3 "" H 1875 4850 30  0000 C CNN
	1    1875 4850
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5BA06125
P 1625 4575
F 0 "R4" V 1705 4575 50  0000 C CNN
F 1 "1M 1%" V 1625 4575 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1555 4575 30  0001 C CNN
F 3 "" H 1625 4575 30  0000 C CNN
	1    1625 4575
	-1   0    0    1   
$EndComp
$Comp
L C C1
U 1 1 5BA06126
P 1350 2550
F 0 "C1" H 1375 2650 50  0000 L CNN
F 1 "22n" H 1375 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1388 2400 50  0001 C CNN
F 3 "" H 1350 2550 50  0001 C CNN
	1    1350 2550
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 5BA06127
P 1375 4850
F 0 "C2" H 1400 4950 50  0000 L CNN
F 1 "22n" H 1400 4750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1413 4700 50  0001 C CNN
F 3 "" H 1375 4850 50  0001 C CNN
	1    1375 4850
	0    1    1    0   
$EndComp
$Comp
L TEST_1P J2
U 1 1 5BA0612A
P 6550 3800
F 0 "J2" H 6550 4070 50  0000 C CNN
F 1 "T1" H 6550 4000 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 6750 3800 50  0001 C CNN
F 3 "" H 6750 3800 50  0001 C CNN
	1    6550 3800
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P J3
U 1 1 5BA0612B
P 8575 3625
F 0 "J3" H 8575 3895 50  0000 C CNN
F 1 "T2" H 8575 3825 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 8775 3625 50  0001 C CNN
F 3 "" H 8775 3625 50  0001 C CNN
	1    8575 3625
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5BA0612C
P 1350 2850
F 0 "R1" V 1430 2850 50  0000 C CNN
F 1 "1k5 1%" V 1350 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1280 2850 30  0001 C CNN
F 3 "" H 1350 2850 30  0000 C CNN
	1    1350 2850
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5BA0612D
P 1375 5150
F 0 "R2" V 1455 5150 50  0000 C CNN
F 1 "1k5 1%" V 1375 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1305 5150 30  0001 C CNN
F 3 "" H 1375 5150 30  0000 C CNN
	1    1375 5150
	0    1    1    0   
$EndComp
Text Label 7325 3550 1    60   ~ 0
v_ref
Text Label 5500 4700 0    60   ~ 0
v_ref
Text Label 1725 2050 0    60   ~ 0
v_ref
Text Label 1725 4350 0    60   ~ 0
v_ref
$Comp
L Conn_01x02 J1
U 1 1 5BA07CB0
P 525 3575
F 0 "J1" H 525 3675 50  0000 C CNN
F 1 "in" H 525 3375 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 525 3575 50  0001 C CNN
F 3 "" H 525 3575 50  0001 C CNN
	1    525  3575
	-1   0    0    -1  
$EndComp
Text Label 9550 3750 0    60   ~ 0
out
$Comp
L Conn_01x05 J4
U 1 1 5BA08AEF
P 11050 3750
F 0 "J4" H 11050 4050 50  0000 C CNN
F 1 "Conn_01x05" H 11050 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch1.27mm" H 11050 3750 50  0001 C CNN
F 3 "" H 11050 3750 50  0001 C CNN
	1    11050 3750
	1    0    0    -1  
$EndComp
Text Label 10550 3950 0    60   ~ 0
v_ref
Wire Wire Line
	3225 2350 3225 2150
Wire Wire Line
	3225 3050 3225 3250
Wire Wire Line
	4225 3625 4225 3450
Wire Wire Line
	4225 4125 4225 3925
Wire Wire Line
	2625 3775 2625 2850
Wire Wire Line
	2625 2850 2825 2850
Wire Wire Line
	2825 4550 2625 4550
Wire Wire Line
	2625 4550 2625 4075
Wire Wire Line
	3100 4225 2625 4225
Connection ~ 2625 4225
Wire Wire Line
	3100 3600 2625 3600
Connection ~ 2625 3600
Wire Wire Line
	3725 2700 3925 2700
Wire Wire Line
	3400 3600 3825 3600
Wire Wire Line
	3825 3600 3825 2700
Connection ~ 3825 2700
Wire Wire Line
	3725 4700 3925 4700
Wire Wire Line
	3400 4225 3825 4225
Wire Wire Line
	3825 4225 3825 4700
Connection ~ 3825 4700
Wire Wire Line
	4225 2700 5000 2700
Wire Wire Line
	4225 4700 5000 4700
Wire Wire Line
	4875 3750 4675 3750
Wire Wire Line
	4675 3750 4675 2700
Connection ~ 4675 2700
Wire Wire Line
	4875 4050 4675 4050
Wire Wire Line
	4675 4050 4675 4700
Connection ~ 4675 4700
Wire Wire Line
	5300 4700 5700 4700
Wire Wire Line
	5775 3900 7000 3900
Wire Wire Line
	5975 3900 5975 2700
Wire Wire Line
	5975 2700 5300 2700
Connection ~ 5975 3900
Wire Wire Line
	2025 2550 2825 2550
Wire Wire Line
	2025 4850 2825 4850
Wire Wire Line
	7525 3600 7325 3600
Wire Wire Line
	7325 3600 7325 3375
Wire Wire Line
	7300 3900 7525 3900
Wire Wire Line
	7750 4425 7400 4425
Wire Wire Line
	7400 3900 7400 4750
Connection ~ 7400 3900
Wire Wire Line
	8575 3625 8575 4750
Wire Wire Line
	8575 4425 8050 4425
Connection ~ 8575 3750
Wire Wire Line
	7400 4750 7775 4750
Connection ~ 7400 4425
Wire Wire Line
	8575 4750 8075 4750
Connection ~ 8575 4425
Wire Wire Line
	8425 3750 9175 3750
Wire Wire Line
	2225 2600 2225 2550
Wire Wire Line
	2225 2900 2225 3000
Wire Wire Line
	2225 5250 2225 5350
Wire Wire Line
	2225 4950 2225 4850
Connection ~ 2225 2550
Wire Wire Line
	1500 2550 1725 2550
Wire Wire Line
	1625 2425 1625 2850
Wire Wire Line
	1625 2125 1625 2050
Wire Wire Line
	1625 2050 1925 2050
Wire Wire Line
	1525 4850 1725 4850
Wire Wire Line
	1625 4725 1625 5150
Wire Wire Line
	1625 4425 1625 4350
Wire Wire Line
	1625 4350 1925 4350
Connection ~ 2225 4850
Connection ~ 1625 2550
Wire Wire Line
	1200 2550 825  2550
Wire Wire Line
	825  4850 1225 4850
Connection ~ 1625 4850
Wire Wire Line
	6550 3800 6550 3900
Connection ~ 6550 3900
Wire Wire Line
	1625 2850 1500 2850
Wire Wire Line
	1200 2850 1100 2850
Wire Wire Line
	1100 2850 1100 2550
Connection ~ 1100 2550
Wire Wire Line
	1625 5150 1525 5150
Wire Wire Line
	1225 5150 1075 5150
Wire Wire Line
	1075 5150 1075 4850
Connection ~ 1075 4850
Wire Wire Line
	825  2550 825  3575
Wire Wire Line
	825  4850 825  3675
Wire Wire Line
	10850 3950 10525 3950
Wire Wire Line
	10100 3850 10850 3850
Wire Wire Line
	10400 3650 10400 4025
Wire Wire Line
	10850 3750 10525 3750
Text Label 10550 3750 0    60   ~ 0
out
Wire Wire Line
	10850 3650 10400 3650
Connection ~ 10400 3850
$Comp
L GNDA #PWR07
U 1 1 5BA093C6
P 10400 4025
F 0 "#PWR07" H 10400 3775 50  0001 C CNN
F 1 "GNDA" H 10400 3875 50  0000 C CNN
F 2 "" H 10400 4025 50  0001 C CNN
F 3 "" H 10400 4025 50  0001 C CNN
	1    10400 4025
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 3550 10850 3550
Wire Wire Line
	10400 3550 10400 3375
$Comp
L VDDA #PWR08
U 1 1 5BA09791
P 10400 3375
F 0 "#PWR08" H 10400 3225 50  0001 C CNN
F 1 "VDDA" H 10400 3525 50  0000 C CNN
F 2 "" H 10400 3375 50  0001 C CNN
F 3 "" H 10400 3375 50  0001 C CNN
	1    10400 3375
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 5BA09CBD
P 10100 3375
F 0 "#FLG09" H 10100 3450 50  0001 C CNN
F 1 "PWR_FLAG" H 10100 3525 50  0000 C CNN
F 2 "" H 10100 3375 50  0001 C CNN
F 3 "" H 10100 3375 50  0001 C CNN
	1    10100 3375
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 3375 10100 3550
Connection ~ 10400 3550
Wire Wire Line
	10100 3850 10100 4025
$Comp
L PWR_FLAG #FLG010
U 1 1 5BA0A475
P 10100 4025
F 0 "#FLG010" H 10100 4100 50  0001 C CNN
F 1 "PWR_FLAG" H 10100 4175 50  0000 C CNN
F 2 "" H 10100 4025 50  0001 C CNN
F 3 "" H 10100 4025 50  0001 C CNN
	1    10100 4025
	-1   0    0    1   
$EndComp
Wire Wire Line
	825  3575 725  3575
Wire Wire Line
	825  3675 725  3675
$Comp
L R R16
U 1 1 5BA151A3
P 9325 3750
F 0 "R16" V 9405 3750 50  0000 C CNN
F 1 "1k 1%" V 9325 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9255 3750 30  0001 C CNN
F 3 "" H 9325 3750 30  0000 C CNN
	1    9325 3750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9475 3750 9725 3750
Wire Notes Line
	9325 3575 9050 3050
Text Notes 8200 2950 0    60   ~ 0
Long wires after a socket may introduce noise \nas it typically happens at opamp output with \npresence of a capacitance. A resistance is supposed \nto help a little bit. So that opamp output works \non a little piece of wire before the resistance.
$EndSCHEMATC
