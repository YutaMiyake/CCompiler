.data

#0002 Decl: arr array 1000000 int
arr: .space 4000000

newline: .asciiz "\n"

.text

#0000 Function: main
main:

#0001 BeginFunc 0


#0002 Decl: arr array 1000000 int


#0003 _TEMP1 := 0 * 1
li $s0, 0
li $s1, 1
mul $t0, $s0, $s1

#0004 _TEMP2 := _TEMP1 + 0
li $s2, 0
add $t1, $t0, $s2

#0005 _TEMP3 := 0 * 10
li $s3, 0
li $s4, 10
mul $t2, $s3, $s4

#0006 _TEMP4 := _TEMP3 + _TEMP2
add $t3, $t2, $t1

#0007 _TEMP5 := 0 * 100
li $s5, 0
li $s6, 100
mul $t4, $s5, $s6

#0008 _TEMP6 := _TEMP5 + _TEMP4
add $t5, $t4, $t3

#0009 _TEMP7 := 0 * 1000
li $s7, 0
li $s0, 1000
mul $t6, $s7, $s0

#0010 _TEMP8 := _TEMP7 + _TEMP6
add $t7, $t6, $t5

#0011 _TEMP9 := 0 * 10000
li $s1, 0
li $s2, 10000
mul $t8, $s1, $s2

#0012 _TEMP10 := _TEMP9 + _TEMP8
add $t9, $t8, $t7

#0013 _TEMP11 := 1 * 100000
li $s3, 1
li $s4, 100000
mul $t0, $s3, $s4

#0014 _TEMP12 := _TEMP11 + _TEMP10
add $t2, $t0, $t9

#0015 _TEMP13 := 4
li $s5, 4
move $t1, $s5

#0016 _TEMP14 := _TEMP13 * _TEMP12
mul $t4, $t1, $t2

#0017 _TEMP15 := _TEMP14 + &arr
la $s6, arr
add $t3, $t4, $s6

#0018 (_TEMP15) := 2
li $s7, 2
move $s0, $s7
sw $s0, ($t3)

#0019 _TEMP16 := 0 * 1
li $s1, 0
li $s2, 1
mul $t6, $s1, $s2

#0020 _TEMP17 := _TEMP16 + 0
li $s3, 0
add $t5, $t6, $s3

#0021 _TEMP18 := 0 * 10
li $s4, 0
li $s5, 10
mul $t8, $s4, $s5

#0022 _TEMP19 := _TEMP18 + _TEMP17
add $t7, $t8, $t5

#0023 _TEMP20 := 0 * 100
li $s6, 0
li $s7, 100
mul $t0, $s6, $s7

#0024 _TEMP21 := _TEMP20 + _TEMP19
add $t9, $t0, $t7

#0025 _TEMP22 := 0 * 1000
li $s0, 0
li $s1, 1000
mul $t1, $s0, $s1

#0026 _TEMP23 := _TEMP22 + _TEMP21
add $t2, $t1, $t9

#0027 _TEMP24 := 0 * 10000
li $s2, 0
li $s3, 10000
mul $t4, $s2, $s3

#0028 _TEMP25 := _TEMP24 + _TEMP23
add $t3, $t4, $t2

#0029 _TEMP26 := 2 * 100000
li $s4, 2
li $s5, 100000
mul $t6, $s4, $s5

#0030 _TEMP27 := _TEMP26 + _TEMP25
add $t8, $t6, $t3

#0031 _TEMP28 := 4
li $s6, 4
move $t5, $s6

#0032 _TEMP29 := _TEMP28 * _TEMP27
mul $t0, $t5, $t8

#0033 _TEMP30 := _TEMP29 + &arr
la $s7, arr
add $t7, $t0, $s7

#0034 (_TEMP30) := 3
li $s0, 3
move $s1, $s0
sw $s1, ($t7)

#0035 _TEMP31 := 0 * 1
li $s2, 0
li $s3, 1
mul $t1, $s2, $s3

#0036 _TEMP32 := _TEMP31 + 0
li $s4, 0
add $t9, $t1, $s4

#0037 _TEMP33 := 0 * 10
li $s5, 0
li $s6, 10
mul $t4, $s5, $s6

#0038 _TEMP34 := _TEMP33 + _TEMP32
add $t2, $t4, $t9

#0039 _TEMP35 := 0 * 100
li $s7, 0
li $s0, 100
mul $t6, $s7, $s0

#0040 _TEMP36 := _TEMP35 + _TEMP34
add $t3, $t6, $t2

#0041 _TEMP37 := 0 * 1000
li $s1, 0
li $s2, 1000
mul $t5, $s1, $s2

#0042 _TEMP38 := _TEMP37 + _TEMP36
add $t8, $t5, $t3

#0043 _TEMP39 := 0 * 10000
li $s3, 0
li $s4, 10000
mul $t0, $s3, $s4

#0044 _TEMP40 := _TEMP39 + _TEMP38
add $t7, $t0, $t8

#0045 _TEMP41 := 3 * 100000
li $s5, 3
li $s6, 100000
mul $t1, $s5, $s6

#0046 _TEMP42 := _TEMP41 + _TEMP40
add $t4, $t1, $t7

#0047 _TEMP43 := 4
li $s7, 4
move $t9, $s7

#0048 _TEMP44 := _TEMP43 * _TEMP42
mul $t6, $t9, $t4

#0049 _TEMP45 := _TEMP44 + &arr
la $s0, arr
add $t2, $t6, $s0

#0050 _TEMP46 := 0 * 1
li $s1, 0
li $s2, 1
mul $t5, $s1, $s2

#0051 _TEMP47 := _TEMP46 + 0
li $s3, 0
add $t3, $t5, $s3

#0052 _TEMP48 := 0 * 10
li $s4, 0
li $s5, 10
mul $t0, $s4, $s5

#0053 _TEMP49 := _TEMP48 + _TEMP47
add $t8, $t0, $t3

#0054 _TEMP50 := 0 * 100
li $s6, 0
li $s7, 100
mul $t1, $s6, $s7

#0055 _TEMP51 := _TEMP50 + _TEMP49
add $t7, $t1, $t8

#0056 _TEMP52 := 0 * 1000
li $s0, 0
li $s1, 1000
mul $t9, $s0, $s1

#0057 _TEMP53 := _TEMP52 + _TEMP51
add $t4, $t9, $t7

#0058 _TEMP54 := 0 * 10000
li $s2, 0
li $s3, 10000
mul $t6, $s2, $s3

#0059 _TEMP55 := _TEMP54 + _TEMP53
add $t5, $t6, $t4

#0060 _TEMP56 := 1 * 100000
li $s4, 1
li $s5, 100000
mul $t0, $s4, $s5

#0061 _TEMP57 := _TEMP56 + _TEMP55
add $t3, $t0, $t5

#0062 _TEMP58 := 4
li $s6, 4
move $t1, $s6

#0063 _TEMP59 := _TEMP58 * _TEMP57
mul $t8, $t1, $t3

#0064 _TEMP60 := _TEMP59 + &arr
la $s7, arr
add $t9, $t8, $s7

#0065 _TEMP61 := 0 * 1
li $s0, 0
li $s1, 1
mul $t7, $s0, $s1

#0066 _TEMP62 := _TEMP61 + 0
li $s2, 0
add $t6, $t7, $s2

#0067 _TEMP63 := 0 * 10
li $s3, 0
li $s4, 10
mul $t4, $s3, $s4

#0068 _TEMP64 := _TEMP63 + _TEMP62
add $t0, $t4, $t6

#0069 _TEMP65 := 0 * 100
li $s5, 0
li $s6, 100
mul $t5, $s5, $s6

#0070 _TEMP66 := _TEMP65 + _TEMP64
add $t1, $t5, $t0

#0071 _TEMP67 := 0 * 1000
li $s7, 0
li $s0, 1000
mul $t3, $s7, $s0

#0072 _TEMP68 := _TEMP67 + _TEMP66
add $t8, $t3, $t1

#0073 _TEMP69 := 0 * 10000
li $s1, 0
li $s2, 10000
mul $t7, $s1, $s2

#0074 _TEMP70 := _TEMP69 + _TEMP68
add $t4, $t7, $t8

#0075 _TEMP71 := 2 * 100000
li $s3, 2
li $s4, 100000
mul $t6, $s3, $s4

#0076 _TEMP72 := _TEMP71 + _TEMP70
add $t5, $t6, $t4

#0077 _TEMP73 := 4
li $s5, 4
move $t0, $s5

#0078 _TEMP74 := _TEMP73 * _TEMP72
mul $t3, $t0, $t5

#0079 _TEMP75 := _TEMP74 + &arr
la $s6, arr
add $t1, $t3, $s6

#0080 _TEMP76 := (_TEMP60) * (_TEMP75)
lw $s7, ($t9)
lw $s0, ($t1)
mul $t7, $s7, $s0

#0081 (_TEMP45) := _TEMP76
move $s1, $t7
sw $s1, ($t2)

#0082 _TEMP77 := 0 * 1
li $s2, 0
li $s3, 1
mul $t8, $s2, $s3

#0083 _TEMP78 := _TEMP77 + 0
li $s4, 0
add $t6, $t8, $s4

#0084 _TEMP79 := 0 * 10
li $s5, 0
li $s6, 10
mul $t4, $s5, $s6

#0085 _TEMP80 := _TEMP79 + _TEMP78
add $t0, $t4, $t6

#0086 _TEMP81 := 0 * 100
li $s7, 0
li $s0, 100
mul $t5, $s7, $s0

#0087 _TEMP82 := _TEMP81 + _TEMP80
add $t3, $t5, $t0

#0088 _TEMP83 := 0 * 1000
li $s1, 0
li $s2, 1000
mul $t9, $s1, $s2

#0089 _TEMP84 := _TEMP83 + _TEMP82
add $t1, $t9, $t3

#0090 _TEMP85 := 0 * 10000
li $s3, 0
li $s4, 10000
mul $t2, $s3, $s4

#0091 _TEMP86 := _TEMP85 + _TEMP84
add $t7, $t2, $t1

#0092 _TEMP87 := 1 * 100000
li $s5, 1
li $s6, 100000
mul $t8, $s5, $s6

#0093 _TEMP88 := _TEMP87 + _TEMP86
add $t4, $t8, $t7

#0094 _TEMP89 := 4
li $s7, 4
move $t6, $s7

#0095 _TEMP90 := _TEMP89 * _TEMP88
mul $t5, $t6, $t4

#0096 _TEMP91 := _TEMP90 + &arr
la $s0, arr
add $t0, $t5, $s0

#0097 _TEMP92 := (_TEMP91)
lw $s1, ($t0)
move $t9, $s1

#0098 PushParam _TEMP92
move $a0, $t9

#0099 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0100 _TEMP93 := 0 * 1
li $s2, 0
li $s3, 1
mul $t3, $s2, $s3

#0101 _TEMP94 := _TEMP93 + 0
li $s4, 0
add $t2, $t3, $s4

#0102 _TEMP95 := 0 * 10
li $s5, 0
li $s6, 10
mul $t1, $s5, $s6

#0103 _TEMP96 := _TEMP95 + _TEMP94
add $t8, $t1, $t2

#0104 _TEMP97 := 0 * 100
li $s7, 0
li $s0, 100
mul $t7, $s7, $s0

#0105 _TEMP98 := _TEMP97 + _TEMP96
add $t6, $t7, $t8

#0106 _TEMP99 := 0 * 1000
li $s1, 0
li $s2, 1000
mul $t4, $s1, $s2

#0107 _TEMP100 := _TEMP99 + _TEMP98
add $t5, $t4, $t6

#0108 _TEMP101 := 0 * 10000
li $s3, 0
li $s4, 10000
mul $t0, $s3, $s4

#0109 _TEMP102 := _TEMP101 + _TEMP100
add $t9, $t0, $t5

#0110 _TEMP103 := 2 * 100000
li $s5, 2
li $s6, 100000
mul $t3, $s5, $s6

#0111 _TEMP104 := _TEMP103 + _TEMP102
add $t1, $t3, $t9

#0112 _TEMP105 := 4
li $s7, 4
move $t2, $s7

#0113 _TEMP106 := _TEMP105 * _TEMP104
mul $t7, $t2, $t1

#0114 _TEMP107 := _TEMP106 + &arr
la $s0, arr
add $t8, $t7, $s0

#0115 _TEMP108 := (_TEMP107)
lw $s1, ($t8)
move $t4, $s1

#0116 PushParam _TEMP108
move $a0, $t4

#0117 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0118 _TEMP109 := 0 * 1
li $s2, 0
li $s3, 1
mul $t6, $s2, $s3

#0119 _TEMP110 := _TEMP109 + 0
li $s4, 0
add $t0, $t6, $s4

#0120 _TEMP111 := 0 * 10
li $s5, 0
li $s6, 10
mul $t5, $s5, $s6

#0121 _TEMP112 := _TEMP111 + _TEMP110
add $t3, $t5, $t0

#0122 _TEMP113 := 0 * 100
li $s7, 0
li $s0, 100
mul $t9, $s7, $s0

#0123 _TEMP114 := _TEMP113 + _TEMP112
add $t2, $t9, $t3

#0124 _TEMP115 := 0 * 1000
li $s1, 0
li $s2, 1000
mul $t1, $s1, $s2

#0125 _TEMP116 := _TEMP115 + _TEMP114
add $t7, $t1, $t2

#0126 _TEMP117 := 0 * 10000
li $s3, 0
li $s4, 10000
mul $t8, $s3, $s4

#0127 _TEMP118 := _TEMP117 + _TEMP116
add $t4, $t8, $t7

#0128 _TEMP119 := 3 * 100000
li $s5, 3
li $s6, 100000
mul $t6, $s5, $s6

#0129 _TEMP120 := _TEMP119 + _TEMP118
add $t5, $t6, $t4

#0130 _TEMP121 := 4
li $s7, 4
move $t0, $s7

#0131 _TEMP122 := _TEMP121 * _TEMP120
mul $t9, $t0, $t5

#0132 _TEMP123 := _TEMP122 + &arr
la $s0, arr
add $t3, $t9, $s0

#0133 _TEMP124 := (_TEMP123)
lw $s1, ($t3)
move $t1, $s1

#0134 PushParam _TEMP124
move $a0, $t1

#0135 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0136 _TEMP125 := 0
li $s2, 0
move $t2, $s2

#0137 return _TEMP125
move $v0, $t2
j _end_main

#0138 EndFunc
_end_main:
li $v0, 10     # set up for exit
syscall        # exit

