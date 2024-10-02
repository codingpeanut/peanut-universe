;---------------------------------------
;		Author:	411440521 JoshLee		
;		Date:	2023/10/27				
;---------------------------------------
		AREA	prog6, CODE, READONLY
		ENTRY
		
		LDR		R2, =0x12345678
		LDR		R3, =0x87654321
		MOV		R4, #0x00000012 
		
		BIC		r2, r2, #0xFF000000
		LSL 	r2, r3, #4
		LSL 	r2, r2, r4
		ROR 	r2, r2, #12
		AND 	r2, r2, r3
		ORR 	r2, r2, r4
		EOR 	r2, r2, r4
		BIC 	r2, r2, r4
		EOR 	r2, r2, r3, ROR #7
		
		; R2 is the answer
		
stop    B		stop
		END