.data

#0000 Init: x int 0
x: .word 0

#0003 Decl: arr array 1000 int
arr: .space 4000

#0004 Decl: idx1 int
idx1: .space 4

#0005 Decl: idx2 int
idx2: .space 4

#0006 Decl: idx3 int
idx3: .space 4

newline: .asciiz "\n"

.text

#0000 Init: x int 0


#0001 Function: main
main:

#0002 BeginFunc 0


#0003 Decl: arr array 1000 int


#0004 Decl: idx1 int


#0005 Decl: idx2 int


#0006 Decl: idx3 int


#0007 idx1 := 0
li $s0, 0
move $s1, $s0
sw $s1, idx1

#0008 _LABEL1:
_LABEL1:

#0009 if idx1 < 10 goto _LABEL2
la $s2, idx1
lw $s2, ($s2)
li $s3, 10
blt $s2, $s3, _LABEL2

#0010 goto _LABEL3
j _LABEL3

#0011 _LABEL4:
_LABEL4:

#0012 idx1 := idx1 + 1
la $s4, idx1
lw $s4, ($s4)
li $s5, 1
add $s6, $s4, $s5
sw $s6, idx1

#0013 goto _LABEL1
j _LABEL1

#0014 _LABEL2:
_LABEL2:

#0015 idx2 := 0
li $s7, 0
move $s0, $s7
sw $s0, idx2

#0016 _LABEL5:
_LABEL5:

#0017 if idx2 < 10 goto _LABEL6
la $s1, idx2
lw $s1, ($s1)
li $s2, 10
blt $s1, $s2, _LABEL6

#0018 goto _LABEL7
j _LABEL7

#0019 _LABEL8:
_LABEL8:

#0020 idx2 := idx2 + 1
la $s3, idx2
lw $s3, ($s3)
li $s4, 1
add $s5, $s3, $s4
sw $s5, idx2

#0021 goto _LABEL5
j _LABEL5

#0022 _LABEL6:
_LABEL6:

#0023 idx3 := 0
li $s6, 0
move $s7, $s6
sw $s7, idx3

#0024 _LABEL9:
_LABEL9:

#0025 if idx3 < 10 goto _LABEL10
la $s0, idx3
lw $s0, ($s0)
li $s1, 10
blt $s0, $s1, _LABEL10

#0026 goto _LABEL11
j _LABEL11

#0027 _LABEL12:
_LABEL12:

#0028 idx3 := idx3 + 1
la $s2, idx3
lw $s2, ($s2)
li $s3, 1
add $s4, $s2, $s3
sw $s4, idx3

#0029 goto _LABEL9
j _LABEL9

#0030 _LABEL10:
_LABEL10:

#0031 _TEMP1 := idx1 * 1
la $s5, idx1
lw $s5, ($s5)
li $s6, 1
mul $t0, $s5, $s6

#0032 _TEMP2 := _TEMP1 + 0
li $s7, 0
add $t1, $t0, $s7

#0033 _TEMP3 := idx2 * 10
la $s0, idx2
lw $s0, ($s0)
li $s1, 10
mul $t2, $s0, $s1

#0034 _TEMP4 := _TEMP3 + _TEMP2
add $t3, $t2, $t1

#0035 _TEMP5 := idx3 * 100
la $s2, idx3
lw $s2, ($s2)
li $s3, 100
mul $t4, $s2, $s3

#0036 _TEMP6 := _TEMP5 + _TEMP4
add $t5, $t4, $t3

#0037 _TEMP7 := 4
li $s4, 4
move $t6, $s4

#0038 _TEMP8 := _TEMP7 * _TEMP6
mul $t7, $t6, $t5

#0039 _TEMP9 := _TEMP8 + &arr
la $s5, arr
add $t8, $t7, $s5

#0040 _TEMP10 := idx1 * idx2
la $s6, idx1
lw $s6, ($s6)
la $s7, idx2
lw $s7, ($s7)
mul $t9, $s6, $s7

#0041 _TEMP11 := _TEMP10 * idx3
la $s0, idx3
lw $s0, ($s0)
mul $t0, $t9, $s0

#0042 (_TEMP9) := _TEMP11
move $s1, $t0
sw $s1, ($t8)

#0043 goto _LABEL12
j _LABEL12

#0044 _LABEL11:
_LABEL11:

#0045 goto _LABEL8
j _LABEL8

#0046 _LABEL7:
_LABEL7:

#0047 goto _LABEL4
j _LABEL4

#0048 _LABEL3:
_LABEL3:

#0049 idx1 := 0
li $s2, 0
move $s3, $s2
sw $s3, idx1

#0050 _LABEL13:
_LABEL13:

#0051 if idx1 < 10 goto _LABEL14
la $s4, idx1
lw $s4, ($s4)
li $s5, 10
blt $s4, $s5, _LABEL14

#0052 goto _LABEL15
j _LABEL15

#0053 _LABEL16:
_LABEL16:

#0054 idx1 := idx1 + 1
la $s6, idx1
lw $s6, ($s6)
li $s7, 1
add $s0, $s6, $s7
sw $s0, idx1

#0055 goto _LABEL13
j _LABEL13

#0056 _LABEL14:
_LABEL14:

#0057 idx2 := 0
li $s1, 0
move $s2, $s1
sw $s2, idx2

#0058 _LABEL17:
_LABEL17:

#0059 if idx2 < 10 goto _LABEL18
la $s3, idx2
lw $s3, ($s3)
li $s4, 10
blt $s3, $s4, _LABEL18

#0060 goto _LABEL19
j _LABEL19

#0061 _LABEL20:
_LABEL20:

#0062 idx2 := idx2 + 1
la $s5, idx2
lw $s5, ($s5)
li $s6, 1
add $s7, $s5, $s6
sw $s7, idx2

#0063 goto _LABEL17
j _LABEL17

#0064 _LABEL18:
_LABEL18:

#0065 idx3 := 0
li $s0, 0
move $s1, $s0
sw $s1, idx3

#0066 _LABEL21:
_LABEL21:

#0067 if idx3 < 10 goto _LABEL22
la $s2, idx3
lw $s2, ($s2)
li $s3, 10
blt $s2, $s3, _LABEL22

#0068 goto _LABEL23
j _LABEL23

#0069 _LABEL24:
_LABEL24:

#0070 idx3 := idx3 + 1
la $s4, idx3
lw $s4, ($s4)
li $s5, 1
add $s6, $s4, $s5
sw $s6, idx3

#0071 goto _LABEL21
j _LABEL21

#0072 _LABEL22:
_LABEL22:

#0073 _TEMP12 := idx1 * idx2
la $s7, idx1
lw $s7, ($s7)
la $s0, idx2
lw $s0, ($s0)
mul $t2, $s7, $s0

#0074 _TEMP13 := _TEMP12 * idx3
la $s1, idx3
lw $s1, ($s1)
mul $t1, $t2, $s1

#0075 _TEMP14 := _TEMP13
move $t4, $t1

#0076 PushParam _TEMP14
move $a0, $t4

#0077 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0078 goto _LABEL24
j _LABEL24

#0079 _LABEL23:
_LABEL23:

#0080 goto _LABEL20
j _LABEL20

#0081 _LABEL19:
_LABEL19:

#0082 goto _LABEL16
j _LABEL16

#0083 _LABEL15:
_LABEL15:

#0084 _TEMP15 := 0 * 1
li $s2, 0
li $s3, 1
mul $t3, $s2, $s3

#0085 _TEMP16 := _TEMP15 + 0
li $s4, 0
add $t6, $t3, $s4

#0086 _TEMP17 := 0 * 10
li $s5, 0
li $s6, 10
mul $t5, $s5, $s6

#0087 _TEMP18 := _TEMP17 + _TEMP16
add $t7, $t5, $t6

#0088 _TEMP19 := 0 * 100
li $s7, 0
li $s0, 100
mul $t9, $s7, $s0

#0089 _TEMP20 := _TEMP19 + _TEMP18
add $t8, $t9, $t7

#0090 _TEMP21 := 4
li $s1, 4
move $t0, $s1

#0091 _TEMP22 := _TEMP21 * _TEMP20
mul $t2, $t0, $t8

#0092 _TEMP23 := _TEMP22 + &arr
la $s2, arr
add $t1, $t2, $s2

#0093 _TEMP24 := 9 * 1
li $s3, 9
li $s4, 1
mul $t4, $s3, $s4

#0094 _TEMP25 := _TEMP24 + 0
li $s5, 0
add $t3, $t4, $s5

#0095 _TEMP26 := 9 * 10
li $s6, 9
li $s7, 10
mul $t5, $s6, $s7

#0096 _TEMP27 := _TEMP26 + _TEMP25
add $t6, $t5, $t3

#0097 _TEMP28 := 9 * 100
li $s0, 9
li $s1, 100
mul $t9, $s0, $s1

#0098 _TEMP29 := _TEMP28 + _TEMP27
add $t7, $t9, $t6

#0099 _TEMP30 := 4
li $s2, 4
move $t0, $s2

#0100 _TEMP31 := _TEMP30 * _TEMP29
mul $t8, $t0, $t7

#0101 _TEMP32 := _TEMP31 + &arr
la $s3, arr
add $t2, $t8, $s3

#0102 _TEMP33 := 9 * 1
li $s4, 9
li $s5, 1
mul $t4, $s4, $s5

#0103 _TEMP34 := _TEMP33 + 0
li $s6, 0
add $t5, $t4, $s6

#0104 _TEMP35 := 9 * 10
li $s7, 9
li $s0, 10
mul $t3, $s7, $s0

#0105 _TEMP36 := _TEMP35 + _TEMP34
add $t9, $t3, $t5

#0106 _TEMP37 := 8 * 100
li $s1, 8
li $s2, 100
mul $t6, $s1, $s2

#0107 _TEMP38 := _TEMP37 + _TEMP36
add $t0, $t6, $t9

#0108 _TEMP39 := 4
li $s3, 4
move $t7, $s3

#0109 _TEMP40 := _TEMP39 * _TEMP38
mul $t8, $t7, $t0

#0110 _TEMP41 := _TEMP40 + &arr
la $s4, arr
add $t4, $t8, $s4

#0111 _TEMP42 := (_TEMP32) * (_TEMP41)
lw $s5, ($t2)
lw $s6, ($t4)
mul $t3, $s5, $s6

#0112 (_TEMP23) := _TEMP42
move $s7, $t3
sw $s7, ($t1)

#0113 _TEMP43 := 0 * 1
li $s0, 0
li $s1, 1
mul $t5, $s0, $s1

#0114 _TEMP44 := _TEMP43 + 0
li $s2, 0
add $t6, $t5, $s2

#0115 _TEMP45 := 0 * 10
li $s3, 0
li $s4, 10
mul $t9, $s3, $s4

#0116 _TEMP46 := _TEMP45 + _TEMP44
add $t7, $t9, $t6

#0117 _TEMP47 := 0 * 100
li $s5, 0
li $s6, 100
mul $t0, $s5, $s6

#0118 _TEMP48 := _TEMP47 + _TEMP46
add $t8, $t0, $t7

#0119 _TEMP49 := 4
li $s7, 4
move $t2, $s7

#0120 _TEMP50 := _TEMP49 * _TEMP48
mul $t4, $t2, $t8

#0121 _TEMP51 := _TEMP50 + &arr
la $s0, arr
add $t1, $t4, $s0

#0122 _TEMP52 := (_TEMP51)
lw $s1, ($t1)
move $t3, $s1

#0123 PushParam _TEMP52
move $a0, $t3

#0124 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0125 EndFunc
_end_main:
li $v0, 10     # set up for exit
syscall        # exit

