.data

#0002 Init: fact int 10
fact: .word 10

#0003 Decl: total int
total: .space 4

newline: .asciiz "\n"

.text

#0000 Function: main
main:

#0001 BeginFunc 0


#0002 Init: fact int 10


#0003 Decl: total int


#0004 _TEMP1 := fact
la $s0, fact
lw $s0, ($s0)
move $t0, $s0

#0005 PushParam _TEMP1
move $a0, $t0

#0006 _TEMP2 := FuncCall factorial 4
jal factorial
move $t1, $v0

#0007 total := _TEMP2
move $s1, $t1
sw $s1, total

#0008 _TEMP3 := total
la $s2, total
lw $s2, ($s2)
move $t2, $s2

#0009 PushParam _TEMP3
move $a0, $t2

#0010 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0011 _TEMP4 := 12
li $s3, 12
move $t3, $s3

#0012 PushParam _TEMP4
move $a0, $t3

#0013 _TEMP5 := FuncCall factorial 4
jal factorial
move $t4, $v0

#0014 total := _TEMP5
move $s4, $t4
sw $s4, total

#0015 _TEMP6 := total
la $s5, total
lw $s5, ($s5)
move $t5, $s5

#0016 PushParam _TEMP6
move $a0, $t5

#0017 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0018 _TEMP7 := 0
li $s6, 0
move $t6, $s6

#0019 return _TEMP7
move $v0, $t6
j _end_main

#0020 EndFunc
_end_main:
li $v0, 10     # set up for exit
syscall        # exit

#0021 Function: factorial
factorial:

#0022 BeginFunc 4
sw $fp, -4($sp)
sw $ra, -8($sp)
la $fp, 0($sp)
la $sp, -8($sp)
sw $a0, -4($sp)
la $sp, -4($sp)

#0023 PopParam num


#0024 if num <= 1 goto _LABEL1
li $s7, 1
ble $a0, $s7, _LABEL1

#0025 goto _LABEL2
j _LABEL2

#0026 _LABEL1:
_LABEL1:

#0027 _TEMP8 := 1
li $s0, 1
move $t7, $s0

#0028 return _TEMP8
move $v0, $t7
j _end_factorial

#0029 _LABEL2:
_LABEL2:

#0030 _TEMP9 := num - 1
li $s1, 1
sub $t8, $a0, $s1

#0031 _TEMP10 := _TEMP9
move $t9, $t8

#0032 PushParam _TEMP10
move $a0, $t9

#0033 _TEMP11 := FuncCall factorial 4
jal factorial
move $t0, $v0
lw $a0, 0($sp)
addiu $sp, $sp, 4

#0034 _TEMP12 := _TEMP11 * num
mul $t1, $t0, $a0

#0035 _TEMP13 := _TEMP12
move $t2, $t1

#0036 return _TEMP13
move $v0, $t2
j _end_factorial

#0037 EndFunc
_end_factorial:
la $sp, 0($fp)
lw $ra, -8($sp)
lw $fp, -4($sp)
jr $ra   # return

