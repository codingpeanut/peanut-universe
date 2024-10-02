;---------------------------------------
;		Author:	411440521 JoshLee		
;		Date:	2023/10/27				
;---------------------------------------
		AREA	prog3, CODE, READONLY
		ENTRY
		
		ADR		R0, data1
		ADR		R1, data2
		ADR		R2, data3
		ADR		R3, data4
		ADR		R4, data5
		ADR		R5, data6
		ADR		R6, data7
		ADR		R7, data8
		ADR		R8, data9
		ADR		R9, data10
		
stop	B		stop
		
data1	DCW		0x8ECC, 0xFE37, -149
data2   DCD		0xFE37, 1, 5, 20
data3   DCB 	0xCF, 23, 39, 0x54, 250
data4   DCWU	0x1234
data5   DCB 	255
data6   DCDU	0x12345678, -4321
data7   DCB		0xA3
		ALIGN	4, 3
data8   DCWU	0xFC25
		ALIGN
data9	DCB		"MVP_N. Jokic", 0
data10  DCW		0xEF12
		
		END