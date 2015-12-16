0000 Function: main
0001 BeginFunc 0
0002 Init: ctr int 10
0003 _LABEL1:
0004 _TEMP1 := ctr
0005 PushParam _TEMP1
0006 FuncCall print_int 4
0007 _TEMP2 := ctr
0008 ctr := ctr - 1
0009 if ctr >= 0 goto _LABEL1
0010 goto _LABEL2
0011 _LABEL2:
0012 EndFunc
