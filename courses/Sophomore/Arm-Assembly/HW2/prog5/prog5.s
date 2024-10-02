;---------------------------------------
;		Author:	411440521 JoshLee		
;		Date:	2023/10/27				
;---------------------------------------
		AREA	prog5, CODE, READONLY
		ENTRY
		
		LDR		R3, =0x40000000
		LDR		R6, =0xDEADBEEF
		
		STR		r6, [r3]
		LDRB 	r4, [r3]
		
		; R4 is the answer
		
stop    B		stop
		END