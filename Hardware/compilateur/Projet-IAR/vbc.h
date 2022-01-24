// VLISP Virtual Machine - 2006 - by Sylvain Huet
// Lowcost IS Powerfull


#define OPexec 0
#define OPret 1
#define OPintb 2
#define OPint 3
#define OPnil 4
#define OPdrop 5
#define OPdup 6
#define OPgetlocalb 7
#define OPgetlocal 8
#define OPadd 9
#define OPsub 10
#define OPmul 11
#define OPdiv 12
#define OPmod 13
#define OPand 14
#define OPor 15
#define OPeor 16
#define OPshl 17
#define OPshr 18
#define OPneg 19
#define OPnot 20
#define OPnon 21
#define OPeq 22
#define OPne 23
#define OPlt 24
#define OPgt 25
#define OPle 26
#define OPge 27
#define OPgoto 28
#define OPelse 29
#define OPmktabb 30
#define OPmktab 31
#define OPdeftabb 32
#define OPdeftab 33
#define OPfetchb 34
#define OPfetch 35
#define OPgetglobalb 36
#define OPgetglobal 37
#define OPSecho 38
#define OPIecho 39
#define OPsetlocalb 40
#define OPsetlocal 41
#define OPsetglobal 42
#define OPsetstructb 43
#define OPsetstruct 44
#define OPhd 45
#define OPtl 46
#define OPsetlocal2 47
#define OPstore 48
#define OPcall 49
#define OPcallrb 50
#define OPcallr 51
#define OPfirst 52
#define OPtime_ms 53
#define OPtabnew 54
#define OPfixarg 55
#define OPabs 56
#define OPmax 57
#define OPmin 58
#define OPrand 59
#define OPsrand 60
#define OPtime 61
#define OPstrnew 62
#define OPstrset 63
#define OPstrcpy 64
#define OPvstrcmp 65
#define OPstrfind 66
#define OPstrfindrev 67
#define OPstrlen 68
#define OPstrget 69
#define OPstrsub 70
#define OPstrcat 71
#define OPtablen 72
#define OPstrcatlist 73
#define OPled 74
#define OPmotorset 75
#define OPmotorget 76
#define OPbutton2 77
#define OPbutton3 78
#define OPplayStart 79
#define OPplayFeed 80
#define OPplayStop 81
#define OPload 82
#define OPudpStart 83
#define OPudpCb 84
#define OPudpStop 85
#define OPudpSend 86
#define OPgc 87
#define OPtcpOpen 88
#define OPtcpClose 89
#define OPtcpSend 90
#define OPtcpCb 91
#define OPsave 92
#define OPbytecode 93
#define OPloopcb 94
#define OPIecholn 95
#define OPSecholn 96
#define OPtcpListen 97
#define OPenvget 98
#define OPenvset 99
#define OPsndVol 100
#define OPrfidGet 101
#define OPplayTime 102
#define OPnetCb 103
#define OPnetSend 104
#define OPnetState 105
#define OPnetMac 106
#define OPnetChk 107
#define OPnetSetmode 108
#define OPnetScan 109
#define OPnetAuth 110
#define OPrecStart 111
#define OPrecStop 112
#define OPrecVol 113
#define OPnetSeqAdd 114
#define OPstrgetword 115
#define OPstrputword 116
#define OPatoi 117
#define OPhtoi 118
#define OPitoa 119
#define OPctoa 120
#define OPitoh 121
#define OPctoh 122
#define OPitobin2 123
#define OPlistswitch 124
#define OPlistswitchstr 125
#define OPsndRefresh 126
#define OPsndWrite 127
#define OPsndRead 128
#define OPsndFeed 129
#define OPsndAmpli 130
#define OPcorePP 131
#define OPcorePush 132
#define OPcorePull 133
#define OPcoreBit0 134
#define OPtcpEnable 135
#define OPreboot 136
#define OPstrcmp 137
#define OPadp2wav 138
#define OPwav2adp 139
#define OPalaw2wav 140
#define OPwav2alaw 141
#define OPnetPmk 142
#define OPflashFirmware 143
#define OPcrypt 144
#define OPuncrypt 145
#define OPnetRssi 146
#define OPrfidGetList 147
#define OPrfidRead 148
#define OPrfidWrite 149
#define OPi2cRead 150
#define OPi2cWrite 151


