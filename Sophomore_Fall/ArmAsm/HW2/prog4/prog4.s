;---------------------------------------
;		Author:	411440521 JoshLee		
;		Date:	2023/10/27				
;---------------------------------------
		AREA	prog4, CODE, READONLY
		ENTRY
		
		MOV		R3, #0x40000000
		MOV		R4, #0x60
		
		STR		R6, [R3, #8]
		STRB	R7, [R3], #12
		LDRH	R5, [R3], #12
		LDR		R12, [R3, #4]!
		LDR		R6, [R3, R4, ROR #28]!
		LDR		R0, [R3, R4, LSL #2]
		
		; R3 is the answer
		
stop    B		stop
		END