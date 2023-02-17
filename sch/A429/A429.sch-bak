EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ARINC-429 input stage"
Date "2023-02-17"
Rev "A-dvl"
Comp "IBB"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Amplifier_Operational:LM324 U?
U 1 1 63EEEAFB
P 3325 3450
F 0 "U?" H 3325 3083 50  0000 C CNN
F 1 "LM324" H 3325 3174 50  0000 C CNN
F 2 "" H 3275 3550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 3375 3650 50  0001 C CNN
	1    3325 3450
	1    0    0    1   
$EndComp
$Comp
L BET-device:R R?
U 1 1 63EEFABF
P 2325 3350
F 0 "R?" V 2140 3350 40  0000 C CNN
F 1 "R" V 2216 3350 40  0000 C CNN
F 2 "" V 2255 3350 30  0000 C CNN
F 3 "" H 2325 3350 30  0000 C CNN
	1    2325 3350
	0    1    1    0   
$EndComp
$Comp
L BET-device:R R?
U 1 1 63EF06B4
P 2325 3550
F 0 "R?" V 2140 3550 40  0000 C CNN
F 1 "R" V 2216 3550 40  0000 C CNN
F 2 "" V 2255 3550 30  0000 C CNN
F 3 "" H 2325 3550 30  0000 C CNN
	1    2325 3550
	0    1    1    0   
$EndComp
$Comp
L BET-device:R R?
U 1 1 63EF0E6B
P 3350 2800
F 0 "R?" V 3165 2800 40  0000 C CNN
F 1 "R" V 3241 2800 40  0000 C CNN
F 2 "" V 3280 2800 30  0000 C CNN
F 3 "" H 3350 2800 30  0000 C CNN
	1    3350 2800
	0    1    1    0   
$EndComp
$Comp
L BET-device:R R?
U 1 1 63EF191E
P 2325 2900
F 0 "R?" V 2140 2900 40  0000 C CNN
F 1 "R" V 2216 2900 40  0000 C CNN
F 2 "" V 2255 2900 30  0000 C CNN
F 3 "" H 2325 2900 30  0000 C CNN
	1    2325 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	2575 3350 3025 3350
Wire Wire Line
	3025 3350 3025 2800
Wire Wire Line
	3025 2800 3100 2800
Connection ~ 3025 3350
Wire Wire Line
	3600 2800 3625 2800
Wire Wire Line
	3625 2800 3625 3450
Wire Wire Line
	3625 3450 3850 3450
Connection ~ 3625 3450
Wire Wire Line
	2575 3550 2750 3550
Wire Wire Line
	2575 2900 2750 2900
Wire Wire Line
	2750 2900 2750 3550
Connection ~ 2750 3550
Wire Wire Line
	2750 3550 3025 3550
Text GLabel 2075 2900 0    60   Input ~ 0
VRef
Text GLabel 2075 3350 0    60   Input ~ 0
A429-
Text GLabel 2075 3550 0    60   Input ~ 0
A429+
$Comp
L Comparator:LM2903 U?
U 1 1 63EF5A30
P 4975 3725
F 0 "U?" H 4975 4092 50  0000 C CNN
F 1 "LM2903" H 4975 4001 50  0000 C CNN
F 2 "" H 4975 3725 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393.pdf" H 4975 3725 50  0001 C CNN
	1    4975 3725
	1    0    0    -1  
$EndComp
$Comp
L Comparator:LM2903 U?
U 1 1 63EF7D01
P 5950 3700
F 0 "U?" H 5950 4067 50  0000 C CNN
F 1 "LM2903" H 5950 3976 50  0000 C CNN
F 2 "" H 5950 3700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393.pdf" H 5950 3700 50  0001 C CNN
	1    5950 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:D D?
U 1 1 63EF90FA
P 4425 3150
F 0 "D?" V 4471 3070 50  0000 R CNN
F 1 "D" V 4380 3070 50  0000 R CNN
F 2 "" H 4425 3150 50  0001 C CNN
F 3 "~" H 4425 3150 50  0001 C CNN
	1    4425 3150
	0    -1   -1   0   
$EndComp
Text GLabel 4425 3300 0    60   Input ~ 0
VRef
$Comp
L BET-device:R R?
U 1 1 63EFA247
P 4425 2700
F 0 "R?" H 4354 2662 40  0000 R CNN
F 1 "R" H 4354 2738 40  0000 R CNN
F 2 "" V 4355 2700 30  0000 C CNN
F 3 "" H 4425 2700 30  0000 C CNN
	1    4425 2700
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 63EFACDB
P 4425 2450
F 0 "#PWR?" H 4425 2300 50  0001 C CNN
F 1 "+3V3" H 4440 2623 50  0000 C CNN
F 2 "" H 4425 2450 50  0001 C CNN
F 3 "" H 4425 2450 50  0001 C CNN
	1    4425 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4425 3000 4675 3000
Wire Wire Line
	4675 3000 4675 3625
Text GLabel 5450 2650 0    60   Input ~ 0
VRef
$Comp
L Device:D D?
U 1 1 63EFB9CD
P 5450 2800
F 0 "D?" V 5496 2720 50  0000 R CNN
F 1 "D" V 5405 2720 50  0000 R CNN
F 2 "" H 5450 2800 50  0001 C CNN
F 3 "~" H 5450 2800 50  0001 C CNN
	1    5450 2800
	0    -1   -1   0   
$EndComp
$Comp
L BET-device:R R?
U 1 1 63EFC357
P 5450 3225
F 0 "R?" H 5379 3187 40  0000 R CNN
F 1 "R" H 5379 3263 40  0000 R CNN
F 2 "" V 5380 3225 30  0000 C CNN
F 3 "" H 5450 3225 30  0000 C CNN
	1    5450 3225
	-1   0    0    1   
$EndComp
Wire Wire Line
	4425 3000 4425 2950
Connection ~ 4425 3000
Wire Wire Line
	5450 2950 5650 2950
Wire Wire Line
	5650 2950 5650 3600
Wire Wire Line
	5450 2975 5450 2950
Connection ~ 5450 2950
$Comp
L power:GND #PWR?
U 1 1 63EFDD40
P 5450 3475
F 0 "#PWR?" H 5450 3225 50  0001 C CNN
F 1 "GND" H 5455 3302 50  0000 C CNN
F 2 "" H 5450 3475 50  0001 C CNN
F 3 "" H 5450 3475 50  0001 C CNN
	1    5450 3475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3800 5650 4000
Wire Wire Line
	5650 4000 4675 4000
Wire Wire Line
	3850 4000 3850 3450
Wire Wire Line
	4675 3825 4675 4000
Connection ~ 4675 4000
Wire Wire Line
	4675 4000 3850 4000
$Comp
L 4xxx:4011 U?
U 1 1 63EFF4A6
P 6925 3800
F 0 "U?" H 6925 4125 50  0000 C CNN
F 1 "4011" H 6925 4034 50  0000 C CNN
F 2 "" H 6925 3800 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4011bms-12bms-23bms.pdf" H 6925 3800 50  0001 C CNN
	1    6925 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6625 3900 6400 3900
Wire Wire Line
	5275 3900 5275 3725
Wire Wire Line
	6625 3700 6250 3700
Text GLabel 7925 3800 2    60   Output ~ 0
~Act
Text GLabel 7925 4050 2    60   Output ~ 0
Pol
Wire Wire Line
	7925 3800 7225 3800
Wire Wire Line
	7925 4050 6400 4050
Wire Wire Line
	6400 4050 6400 3900
Connection ~ 6400 3900
Wire Wire Line
	6400 3900 5275 3900
Text Notes 5800 4350 0    60   ~ 0
Schematic only\npolarities not verified
$EndSCHEMATC
