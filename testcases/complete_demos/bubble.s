.data

#0002 Init: numbers array 10 int 5,15,8,10,12,4,9,2,7,1
numbers: .word 5,15,8,10,12,4,9,2,7,1

#0003 Init: size int 10
size: .word 10

#0004 Init: swapped int 1
swapped: .word 1

#0005 Init: index int 0
index: .word 0

#0006 Init: temp int 0
temp: .word 0

#0007 Decl: idx int
idx: .space 4

newline: .asciiz "\n"

.text

#0000 Function: main
main:

#0001 BeginFunc 0


#0002 Init: numbers array 10 int 5,15,8,10,12,4,9,2,7,1


#0003 Init: size int 10


#0004 Init: swapped int 1


#0005 Init: index int 0


#0006 Init: temp int 0


#0007 Decl: idx int


#0008 idx := 0
li $s0, 0
move $s1, $s0
sw $s1, idx

#0009 _LABEL1:
_LABEL1:

#0010 if idx < 10 goto _LABEL2
la $s2, idx
lw $s2, ($s2)
li $s3, 10
blt $s2, $s3, _LABEL2

#0011 goto _LABEL3
j _LABEL3

#0012 _LABEL4:
_LABEL4:

#0013 _TEMP1 := idx
la $s4, idx
lw $s4, ($s4)
move $t0, $s4

#0014 idx := idx + 1
la $s5, idx
lw $s5, ($s5)
li $s6, 1
add $s7, $s5, $s6
sw $s7, idx

#0015 goto _LABEL1
j _LABEL1

#0016 _LABEL2:
_LABEL2:

#0017 _TEMP2 := idx * 1
la $s0, idx
lw $s0, ($s0)
li $s1, 1
mul $t1, $s0, $s1

#0018 _TEMP3 := _TEMP2 + 0
li $s2, 0
add $t2, $t1, $s2

#0019 _TEMP4 := 4
li $s3, 4
move $t3, $s3

#0020 _TEMP5 := _TEMP4 * _TEMP3
mul $t4, $t3, $t2

#0021 _TEMP6 := _TEMP5 + &numbers
la $s4, numbers
add $t5, $t4, $s4

#0022 _TEMP7 := (_TEMP6)
lw $s5, ($t5)
move $t6, $s5

#0023 PushParam _TEMP7
move $a0, $t6

#0024 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0025 goto _LABEL4
j _LABEL4

#0026 _LABEL3:
_LABEL3:

#0027 _LABEL5:
_LABEL5:

#0028 if swapped goto _LABEL6
la $s6, swapped
lw $s6, ($s6)
li $s7, 1
beq $s6, $s7, _LABEL6

#0029 goto _LABEL7
j _LABEL7

#0030 _LABEL6:
_LABEL6:

#0031 swapped := 0
li $s0, 0
move $s1, $s0
sw $s1, swapped

#0032 index := 9
li $s2, 9
move $s3, $s2
sw $s3, index

#0033 _LABEL8:
_LABEL8:

#0034 if index >= 1 goto _LABEL9
la $s4, index
lw $s4, ($s4)
li $s5, 1
bge $s4, $s5, _LABEL9

#0035 goto _LABEL10
j _LABEL10

#0036 _LABEL11:
_LABEL11:

#0037 _TEMP8 := index
la $s6, index
lw $s6, ($s6)
move $t7, $s6

#0038 index := index - 1
la $s7, index
lw $s7, ($s7)
li $s0, 1
sub $s1, $s7, $s0
sw $s1, index

#0039 goto _LABEL8
j _LABEL8

#0040 _LABEL9:
_LABEL9:

#0041 _TEMP9 := index * 1
la $s2, index
lw $s2, ($s2)
li $s3, 1
mul $t8, $s2, $s3

#0042 _TEMP10 := _TEMP9 + 0
li $s4, 0
add $t9, $t8, $s4

#0043 _TEMP11 := 4
li $s5, 4
move $t1, $s5

#0044 _TEMP12 := _TEMP11 * _TEMP10
mul $t3, $t1, $t9

#0045 _TEMP13 := _TEMP12 + &numbers
la $s6, numbers
add $t2, $t3, $s6

#0046 _TEMP14 := index - 1
la $s7, index
lw $s7, ($s7)
li $s0, 1
sub $t4, $s7, $s0

#0047 _TEMP15 := _TEMP14 * 1
li $s1, 1
mul $t5, $t4, $s1

#0048 _TEMP16 := _TEMP15 + 0
li $s2, 0
add $t6, $t5, $s2

#0049 _TEMP17 := 4
li $s3, 4
move $t8, $s3

#0050 _TEMP18 := _TEMP17 * _TEMP16
mul $t1, $t8, $t6

#0051 _TEMP19 := _TEMP18 + &numbers
la $s4, numbers
add $t9, $t1, $s4

#0052 if (_TEMP13) < (_TEMP19) goto _LABEL12
la $s5, ($t2)
lw $s5, ($s5)
la $s6, ($t9)
lw $s6, ($s6)
blt $s5, $s6, _LABEL12

#0053 goto _LABEL13
j _LABEL13

#0054 _LABEL12:
_LABEL12:

#0055 _TEMP20 := index - 1
la $s7, index
lw $s7, ($s7)
li $s0, 1
sub $t3, $s7, $s0

#0056 _TEMP21 := _TEMP20 * 1
li $s1, 1
mul $t4, $t3, $s1

#0057 _TEMP22 := _TEMP21 + 0
li $s2, 0
add $t5, $t4, $s2

#0058 _TEMP23 := 4
li $s3, 4
move $t8, $s3

#0059 _TEMP24 := _TEMP23 * _TEMP22
mul $t6, $t8, $t5

#0060 _TEMP25 := _TEMP24 + &numbers
la $s4, numbers
add $t1, $t6, $s4

#0061 temp := (_TEMP25)
lw $s5, ($t1)
move $s6, $s5
sw $s6, temp

#0062 _TEMP26 := index - 1
la $s7, index
lw $s7, ($s7)
li $s0, 1
sub $t2, $s7, $s0

#0063 _TEMP27 := _TEMP26 * 1
li $s1, 1
mul $t9, $t2, $s1

#0064 _TEMP28 := _TEMP27 + 0
li $s2, 0
add $t3, $t9, $s2

#0065 _TEMP29 := 4
li $s3, 4
move $t4, $s3

#0066 _TEMP30 := _TEMP29 * _TEMP28
mul $t8, $t4, $t3

#0067 _TEMP31 := _TEMP30 + &numbers
la $s4, numbers
add $t5, $t8, $s4

#0068 _TEMP32 := index * 1
la $s5, index
lw $s5, ($s5)
li $s6, 1
mul $t6, $s5, $s6

#0069 _TEMP33 := _TEMP32 + 0
li $s7, 0
add $t1, $t6, $s7

#0070 _TEMP34 := 4
li $s0, 4
move $t2, $s0

#0071 _TEMP35 := _TEMP34 * _TEMP33
mul $t9, $t2, $t1

#0072 _TEMP36 := _TEMP35 + &numbers
la $s1, numbers
add $t4, $t9, $s1

#0073 (_TEMP31) := (_TEMP36)
lw $s2, ($t4)
move $s3, $s2
sw $s3, ($t5)

#0074 _TEMP37 := index * 1
la $s4, index
lw $s4, ($s4)
li $s5, 1
mul $t3, $s4, $s5

#0075 _TEMP38 := _TEMP37 + 0
li $s6, 0
add $t8, $t3, $s6

#0076 _TEMP39 := 4
li $s7, 4
move $t6, $s7

#0077 _TEMP40 := _TEMP39 * _TEMP38
mul $t2, $t6, $t8

#0078 _TEMP41 := _TEMP40 + &numbers
la $s0, numbers
add $t1, $t2, $s0

#0079 (_TEMP41) := temp
la $s1, temp
lw $s1, ($s1)
move $s2, $s1
sw $s2, ($t1)

#0080 swapped := 1
li $s3, 1
move $s4, $s3
sw $s4, swapped

#0081 _LABEL13:
_LABEL13:

#0082 goto _LABEL11
j _LABEL11

#0083 _LABEL10:
_LABEL10:

#0084 goto _LABEL5
j _LABEL5

#0085 _LABEL7:
_LABEL7:

#0086 idx := 0
li $s5, 0
move $s6, $s5
sw $s6, idx

#0087 _LABEL14:
_LABEL14:

#0088 if idx < 10 goto _LABEL15
la $s7, idx
lw $s7, ($s7)
li $s0, 10
blt $s7, $s0, _LABEL15

#0089 goto _LABEL16
j _LABEL16

#0090 _LABEL17:
_LABEL17:

#0091 _TEMP42 := idx
la $s1, idx
lw $s1, ($s1)
move $t9, $s1

#0092 idx := idx + 1
la $s2, idx
lw $s2, ($s2)
li $s3, 1
add $s4, $s2, $s3
sw $s4, idx

#0093 goto _LABEL14
j _LABEL14

#0094 _LABEL15:
_LABEL15:

#0095 _TEMP43 := idx * 1
la $s5, idx
lw $s5, ($s5)
li $s6, 1
mul $t5, $s5, $s6

#0096 _TEMP44 := _TEMP43 + 0
li $s7, 0
add $t4, $t5, $s7

#0097 _TEMP45 := 4
li $s0, 4
move $t3, $s0

#0098 _TEMP46 := _TEMP45 * _TEMP44
mul $t6, $t3, $t4

#0099 _TEMP47 := _TEMP46 + &numbers
la $s1, numbers
add $t8, $t6, $s1

#0100 _TEMP48 := (_TEMP47)
lw $s2, ($t8)
move $t2, $s2

#0101 PushParam _TEMP48
move $a0, $t2

#0102 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0103 goto _LABEL17
j _LABEL17

#0104 _LABEL16:
_LABEL16:

#0105 _TEMP49 := 0
li $s3, 0
move $t1, $s3

#0106 return _TEMP49
move $v0, $t1
j _end_main

#0107 EndFunc
_end_main:
li $v0, 10     # set up for exit
syscall        # exit

