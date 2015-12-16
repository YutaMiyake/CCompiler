.data

#0002 Init: ctr int 10
ctr: .word 10

newline: .asciiz "\n"

.text

#0000 Function: main
main:

#0001 BeginFunc 0


#0002 Init: ctr int 10


#0003 _LABEL1:
_LABEL1:

#0004 _TEMP1 := ctr
la $s0, ctr
lw $s0, ($s0)
move $t0, $s0

#0005 PushParam _TEMP1
move $a0, $t0


#0006 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0007 _TEMP2 := ctr
la $s1, ctr
lw $s1, ($s1)
move $t1, $s1

#0008 ctr := ctr - 1
la $s2, ctr
lw $s2, ($s2)
li $s3, 1
sub $s4, $s2, $s3
sw $s4, ctr

#0009 if ctr >= 0 goto _LABEL1
la $s5, ctr
lw $s5, ($s5)
li $s6, 0
bge $s5, $s6, _LABEL1

#0010 goto _LABEL2
j _LABEL2

#0011 _LABEL2:
_LABEL2:

#0012 EndFunc
li $v0, 10     # set up for exit
syscall        # exit

