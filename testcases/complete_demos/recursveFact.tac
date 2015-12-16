0000 Function: main
0001 BeginFunc 0
0002 Init: fact int 10
0003 Decl: total int
0004 _TEMP1 := fact
0005 PushParam _TEMP1
0006 _TEMP2 := FuncCall factorial 4
0007 total := _TEMP2
0008 _TEMP3 := total
0009 PushParam _TEMP3
0010 FuncCall print_int 4
0011 _TEMP4 := 12
0012 PushParam _TEMP4
0013 _TEMP5 := FuncCall factorial 4
0014 total := _TEMP5
0015 _TEMP6 := total
0016 PushParam _TEMP6
0017 FuncCall print_int 4
0018 _TEMP7 := 0
0019 return _TEMP7
0020 EndFunc
0021 Function: factorial
0022 BeginFunc 4
0023 PopParam num
0024 if num <= 1 goto _LABEL1
0025 goto _LABEL2
0026 _LABEL1:
0027 _TEMP8 := 1
0028 return _TEMP8
0029 _LABEL2:
0030 _TEMP9 := num - 1
0031 _TEMP10 := _TEMP9
0032 PushParam _TEMP10
0033 _TEMP11 := FuncCall factorial 4
0034 _TEMP12 := _TEMP11 * num
0035 _TEMP13 := _TEMP12
0036 return _TEMP13
0037 EndFunc
