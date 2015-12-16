0000 Function: main
0001 BeginFunc 0
0002 Decl: result int
0003 _TEMP1 := 3
0004 PushParam _TEMP1
0005 _TEMP2 := FuncCall square 4
0006 result := _TEMP2
0007 _TEMP3 := result
0008 PushParam _TEMP3
0009 FuncCall print_int 4
0010 _TEMP4 := 3
0011 PushParam _TEMP4
0012 _TEMP5 := 6
0013 PushParam _TEMP5
0014 _TEMP6 := FuncCall sum 8
0015 result := _TEMP6
0016 _TEMP7 := result
0017 PushParam _TEMP7
0018 FuncCall print_int 4
0019 EndFunc
0020 Function: square
0021 BeginFunc 4
0022 PopParam x
0023 _TEMP8 := x * x
0024 _TEMP9 := _TEMP8
0025 return _TEMP9
0026 EndFunc
0027 Function: sum
0028 BeginFunc 8
0029 PopParam y
0030 PopParam x
0031 _TEMP10 := x + y
0032 _TEMP11 := _TEMP10
0033 return _TEMP11
0034 EndFunc
