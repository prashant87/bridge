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
P 3900 2700
AR Path="/5BA0610B" Ref="U1"  Part="1" 
AR Path="/5BA195B0/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA1547E/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA1C551/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA1C582/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA254FD/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA2552E/5BA0610B" Ref="U?"  Part="1" 
AR Path="/5BA2555F/5BA0610B" Ref="U?"  Part="1" 
F 0 "U1" H 4000 2500 60  0000 C CNN
F 1 "TSZ124IPT" H 4150 2900 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 3900 2700 60  0001 C CNN
F 3 "" H 3900 2700 60  0001 C CNN
	1    3900 2700
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5BA0610C
P 4850 3775
F 0 "C5" H 4875 3875 50  0000 L CNN
F 1 "2n2" H 4875 3675 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4888 3625 50  0001 C CNN
F 3 "" H 4850 3775 50  0001 C CNN
	1    4850 3775
	1    0    0    -1  
$EndComp
$Comp
L VDDA #PWR01
U 1 1 5BA0610D
P 3850 2150
F 0 "#PWR01" H 3850 2000 50  0001 C CNN
F 1 "VDDA" H 3850 2300 50  0000 C CNN
F 2 "" H 3850 2150 50  0001 C CNN
F 3 "" H 3850 2150 50  0001 C CNN
	1    3850 2150
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR02
U 1 1 5BA0610E
P 3850 3250
F 0 "#PWR02" H 3850 3000 50  0001 C CNN
F 1 "GNDA" H 3850 3100 50  0000 C CNN
F 2 "" H 3850 3250 50  0001 C CNN
F 3 "" H 3850 3250 50  0001 C CNN
	1    3850 3250
	1    0    0    -1  
$EndComp
$Comp
L VDDA #PWR03
U 1 1 5BA0610F
P 4850 3450
F 0 "#PWR03" H 4850 3300 50  0001 C CNN
F 1 "VDDA" H 4850 3600 50  0000 C CNN
F 2 "" H 4850 3450 50  0001 C CNN
F 3 "" H 4850 3450 50  0001 C CNN
	1    4850 3450
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR04
U 1 1 5BA06110
P 4850 4125
F 0 "#PWR04" H 4850 3875 50  0001 C CNN
F 1 "GNDA" H 4850 3975 50  0000 C CNN
F 2 "" H 4850 4125 50  0001 C CNN
F 3 "" H 4850 4125 50  0001 C CNN
	1    4850 4125
	1    0    0    -1  
$EndComp
$Comp
L TSZ124IPT U1
U 2 1 5BA06111
P 3900 4700
AR Path="/5BA06111" Ref="U1"  Part="2" 
AR Path="/5BA195B0/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA1547E/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA1C551/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA1C582/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA254FD/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA2552E/5BA06111" Ref="U?"  Part="2" 
AR Path="/5BA2555F/5BA06111" Ref="U?"  Part="2" 
F 0 "U1" H 4000 4500 60  0000 C CNN
F 1 "TSZ124IPT" H 4150 4900 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 3900 4700 60  0001 C CNN
F 3 "" H 3900 4700 60  0001 C CNN
	2    3900 4700
	1    0    0    1   
$EndComp
$Comp
L R R7
U 1 1 5BA06112
P 3250 3925
F 0 "R7" V 3330 3925 50  0000 C CNN
F 1 "150 1%" V 3250 3925 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3180 3925 30  0001 C CNN
F 3 "" H 3250 3925 30  0000 C CNN
	1    3250 3925
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5BA06113
P 3875 3600
F 0 "R8" V 3955 3600 50  0000 C CNN
F 1 "47k1%" V 3875 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3805 3600 30  0001 C CNN
F 3 "" H 3875 3600 30  0000 C CNN
	1    3875 3600
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 5BA06114
P 3875 4225
F 0 "R9" V 3955 4225 50  0000 C CNN
F 1 "47k1%" V 3875 4225 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3805 4225 30  0001 C CNN
F 3 "" H 3875 4225 30  0000 C CNN
	1    3875 4225
	0    1    1    0   
$EndComp
$Comp
L TSZ124IPT U1
U 4 1 5BA06115
P 5950 3900
AR Path="/5BA06115" Ref="U1"  Part="4" 
AR Path="/5BA195B0/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA1547E/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA1C551/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA1C582/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA254FD/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA2552E/5BA06115" Ref="U?"  Part="3" 
AR Path="/5BA2555F/5BA06115" Ref="U?"  Part="3" 
F 0 "U1" H 6050 3700 60  0000 C CNN
F 1 "TSZ124IPT" H 6200 4100 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 5950 3900 60  0001 C CNN
F 3 "" H 5950 3900 60  0001 C CNN
	4    5950 3900
	1    0    0    1   
$EndComp
$Comp
L R R10
U 1 1 5BA06116
P 4700 2700
F 0 "R10" V 4780 2700 50  0000 C CNN
F 1 "10k 1%" V 4700 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4630 2700 30  0001 C CNN
F 3 "" H 4700 2700 30  0000 C CNN
	1    4700 2700
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 5BA06117
P 5775 4700
F 0 "R13" V 5855 4700 50  0000 C CNN
F 1 "10k 1%" V 5775 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5705 4700 30  0001 C CNN
F 3 "" H 5775 4700 30  0000 C CNN
	1    5775 4700
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 5BA06118
P 4700 4700
F 0 "R11" V 4780 4700 50  0000 C CNN
F 1 "10k 1%" V 4700 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4630 4700 30  0001 C CNN
F 3 "" H 4700 4700 30  0000 C CNN
	1    4700 4700
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 5BA06119
P 5775 2700
F 0 "R12" V 5855 2700 50  0000 C CNN
F 1 "10k 1%" V 5775 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5705 2700 30  0001 C CNN
F 3 "" H 5775 2700 30  0000 C CNN
	1    5775 2700
	0    -1   -1   0   
$EndComp
$Comp
L TSZ124IPT U1
U 3 1 5BA0611A
P 8600 3750
AR Path="/5BA0611A" Ref="U1"  Part="3" 
AR Path="/5BA195B0/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA1547E/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA1C551/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA1C582/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA254FD/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA2552E/5BA0611A" Ref="U?"  Part="4" 
AR Path="/5BA2555F/5BA0611A" Ref="U?"  Part="4" 
F 0 "U1" H 8700 3550 60  0000 C CNN
F 1 "TSZ124IPT" H 8850 3950 60  0000 C CNN
F 2 "Package_SSOP:TSSOP-14_4.4x5mm_P0.65mm" H 8600 3750 60  0001 C CNN
F 3 "" H 8600 3750 60  0001 C CNN
	3    8600 3750
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 5BA0611B
P 7775 3900
F 0 "R14" V 7855 3900 50  0000 C CNN
F 1 "1k 1%" V 7775 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7705 3900 30  0001 C CNN
F 3 "" H 7775 3900 30  0000 C CNN
	1    7775 3900
	0    -1   -1   0   
$EndComp
$Comp
L R R15
U 1 1 5BA0611C
P 8525 4425
F 0 "R15" V 8605 4425 50  0000 C CNN
F 1 "100k 1%" V 8525 4425 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8455 4425 30  0001 C CNN
F 3 "" H 8525 4425 30  0000 C CNN
	1    8525 4425
	0    -1   -1   0   
$EndComp
$Comp
L C C6
U 1 1 5BA0611D
P 8550 4750
F 0 "C6" H 8575 4850 50  0000 L CNN
F 1 "100n" H 8575 4650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8588 4600 50  0001 C CNN
F 3 "" H 8550 4750 50  0001 C CNN
	1    8550 4750
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 5BA0611E
P 2850 2750
F 0 "C3" H 2875 2850 50  0000 L CNN
F 1 "100n" H 2875 2650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 2600 30  0001 C CNN
F 3 "" H 2850 2750 60  0000 C CNN
	1    2850 2750
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR05
U 1 1 5BA0611F
P 2850 3000
F 0 "#PWR05" H 2850 2750 50  0001 C CNN
F 1 "GNDA" H 2850 2850 50  0000 C CNN
F 2 "" H 2850 3000 50  0001 C CNN
F 3 "" H 2850 3000 50  0001 C CNN
	1    2850 3000
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5BA06120
P 2850 5100
F 0 "C4" H 2875 5200 50  0000 L CNN
F 1 "100n" H 2875 5000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 4950 30  0001 C CNN
F 3 "" H 2850 5100 60  0000 C CNN
	1    2850 5100
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR06
U 1 1 5BA06121
P 2850 5350
F 0 "#PWR06" H 2850 5100 50  0001 C CNN
F 1 "GNDA" H 2850 5200 50  0000 C CNN
F 2 "" H 2850 5350 50  0001 C CNN
F 3 "" H 2850 5350 50  0001 C CNN
	1    2850 5350
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5BA06122
P 2500 2550
F 0 "R5" V 2580 2550 50  0000 C CNN
F 1 "1k5 1%" V 2500 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2430 2550 30  0001 C CNN
F 3 "" H 2500 2550 30  0000 C CNN
	1    2500 2550
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5BA06123
P 2250 2275
F 0 "R3" V 2330 2275 50  0000 C CNN
F 1 "1M 1%" V 2250 2275 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 2275 30  0001 C CNN
F 3 "" H 2250 2275 30  0000 C CNN
	1    2250 2275
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 5BA06124
P 2500 4850
F 0 "R6" V 2580 4850 50  0000 C CNN
F 1 "1k5 1%" V 2500 4850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2430 4850 30  0001 C CNN
F 3 "" H 2500 4850 30  0000 C CNN
	1    2500 4850
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5BA06125
P 2250 4575
F 0 "R4" V 2330 4575 50  0000 C CNN
F 1 "1M 1%" V 2250 4575 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4575 30  0001 C CNN
F 3 "" H 2250 4575 30  0000 C CNN
	1    2250 4575
	-1   0    0    1   
$EndComp
$Comp
L C C1
U 1 1 5BA06126
P 1975 2550
F 0 "C1" H 2000 2650 50  0000 L CNN
F 1 "22n" H 2000 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2013 2400 50  0001 C CNN
F 3 "" H 1975 2550 50  0001 C CNN
	1    1975 2550
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 5BA06127
P 2000 4850
F 0 "C2" H 2025 4950 50  0000 L CNN
F 1 "22n" H 2025 4750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2038 4700 50  0001 C CNN
F 3 "" H 2000 4850 50  0001 C CNN
	1    2000 4850
	0    1    1    0   
$EndComp
$Comp
L TEST_1P J2
U 1 1 5BA0612A
P 7175 3800
F 0 "J2" H 7175 4070 50  0000 C CNN
F 1 "T1" H 7175 4000 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 7375 3800 50  0001 C CNN
F 3 "" H 7375 3800 50  0001 C CNN
	1    7175 3800
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P J3
U 1 1 5BA0612B
P 9200 3625
F 0 "J3" H 9200 3895 50  0000 C CNN
F 1 "T2" H 9200 3825 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 9400 3625 50  0001 C CNN
F 3 "" H 9400 3625 50  0001 C CNN
	1    9200 3625
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5BA0612C
P 1975 2850
F 0 "R1" V 2055 2850 50  0000 C CNN
F 1 "1k5 1%" V 1975 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1905 2850 30  0001 C CNN
F 3 "" H 1975 2850 30  0000 C CNN
	1    1975 2850
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5BA0612D
P 2000 5150
F 0 "R2" V 2080 5150 50  0000 C CNN
F 1 "1k5 1%" V 2000 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1930 5150 30  0001 C CNN
F 3 "" H 2000 5150 30  0000 C CNN
	1    2000 5150
	0    1    1    0   
$EndComp
Text Label 7950 3550 1    60   ~ 0
v_ref
Text Label 6125 4700 0    60   ~ 0
v_ref
Text Label 2350 2050 0    60   ~ 0
v_ref
Text Label 2350 4350 0    60   ~ 0
v_ref
$Comp
L Conn_01x02 J1
U 1 1 5BA07CB0
P 725 3575
F 0 "J1" H 725 3675 50  0000 C CNN
F 1 "in" H 725 3375 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 725 3575 50  0001 C CNN
F 3 "" H 725 3575 50  0001 C CNN
	1    725  3575
	-1   0    0    -1  
$EndComp
Text Label 9650 3750 0    60   ~ 0
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
	3850 2350 3850 2150
Wire Wire Line
	3850 3050 3850 3250
Wire Wire Line
	4850 3625 4850 3450
Wire Wire Line
	4850 4125 4850 3925
Wire Wire Line
	3250 3775 3250 2850
Wire Wire Line
	3250 2850 3450 2850
Wire Wire Line
	3450 4550 3250 4550
Wire Wire Line
	3250 4550 3250 4075
Wire Wire Line
	3725 4225 3250 4225
Connection ~ 3250 4225
Wire Wire Line
	3725 3600 3250 3600
Connection ~ 3250 3600
Wire Wire Line
	4350 2700 4550 2700
Wire Wire Line
	4025 3600 4450 3600
Wire Wire Line
	4450 3600 4450 2700
Connection ~ 4450 2700
Wire Wire Line
	4350 4700 4550 4700
Wire Wire Line
	4025 4225 4450 4225
Wire Wire Line
	4450 4225 4450 4700
Connection ~ 4450 4700
Wire Wire Line
	4850 2700 5625 2700
Wire Wire Line
	4850 4700 5625 4700
Wire Wire Line
	5500 3750 5300 3750
Wire Wire Line
	5300 3750 5300 2700
Connection ~ 5300 2700
Wire Wire Line
	5500 4050 5300 4050
Wire Wire Line
	5300 4050 5300 4700
Connection ~ 5300 4700
Wire Wire Line
	5925 4700 6325 4700
Wire Wire Line
	6400 3900 7625 3900
Wire Wire Line
	6600 3900 6600 2700
Wire Wire Line
	6600 2700 5925 2700
Connection ~ 6600 3900
Wire Wire Line
	2650 2550 3450 2550
Wire Wire Line
	2650 4850 3450 4850
Wire Wire Line
	8150 3600 7950 3600
Wire Wire Line
	7950 3600 7950 3375
Wire Wire Line
	7925 3900 8150 3900
Wire Wire Line
	8375 4425 8025 4425
Wire Wire Line
	8025 3900 8025 4750
Connection ~ 8025 3900
Wire Wire Line
	9200 3625 9200 4750
Wire Wire Line
	9200 4425 8675 4425
Connection ~ 9200 3750
Wire Wire Line
	8025 4750 8400 4750
Connection ~ 8025 4425
Wire Wire Line
	9200 4750 8700 4750
Connection ~ 9200 4425
Wire Wire Line
	9050 3750 9800 3750
Wire Wire Line
	2850 2600 2850 2550
Wire Wire Line
	2850 2900 2850 3000
Wire Wire Line
	2850 5250 2850 5350
Wire Wire Line
	2850 4950 2850 4850
Connection ~ 2850 2550
Wire Wire Line
	2125 2550 2350 2550
Wire Wire Line
	2250 2425 2250 2850
Wire Wire Line
	2250 2125 2250 2050
Wire Wire Line
	2250 2050 2550 2050
Wire Wire Line
	2150 4850 2350 4850
Wire Wire Line
	2250 4725 2250 5150
Wire Wire Line
	2250 4425 2250 4350
Wire Wire Line
	2250 4350 2550 4350
Connection ~ 2850 4850
Connection ~ 2250 2550
Wire Wire Line
	1825 2550 1450 2550
Wire Wire Line
	1450 4850 1850 4850
Connection ~ 2250 4850
Wire Wire Line
	7175 3800 7175 3900
Connection ~ 7175 3900
Wire Wire Line
	2250 2850 2125 2850
Wire Wire Line
	1825 2850 1725 2850
Wire Wire Line
	1725 2850 1725 2550
Connection ~ 1725 2550
Wire Wire Line
	2250 5150 2150 5150
Wire Wire Line
	1850 5150 1700 5150
Wire Wire Line
	1700 5150 1700 4850
Connection ~ 1700 4850
Wire Wire Line
	925  3575 1450 3575
Wire Wire Line
	1450 3575 1450 2550
Wire Wire Line
	1450 4850 1450 3675
Wire Wire Line
	1450 3675 925  3675
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
$EndSCHEMATC