;---------------------------------------
;		Author:	411440521 JoshLee		
;		Date:	2023/10/27				
;---------------------------------------
		AREA	prog7, CODE, READONLY
		ENTRY
		
		LDR		R6, =0xABCD8765
		
		; -----2's complement-----
		LDR		R2, =0xFFFFFFFF
		EOR		R6, R6, R2
		ADD		R7, R6, #1
		; R7 is the answer
		
		LDR		R5, =0x00002022		; 0b0010000000100010
		ORR		R6, R6, R5			; set bits 1, 5, and 13
		; R6 is the answer
		
		LSR		R5, R5, #1			; 0b0001000000010001
		BIC		r6, r6, R5			; clear bits 0, 4, and 12
		; R6 is the answer
		
		LDR		R5, =0x00000910		; 0b0000100100010000
		EOR		R6, R6, R5			; change bits 4, 8, and 11
		; R6 is the answer
		
		LDR		R0, =0xBEEFABCD
		LDR 	R1, =0x00005555
		LDR		R2, =0xFFFF0000
		AND 	R0, R0, R2			; clear the lower half of r0
		ORR 	R0, R0, R1        	; OR the lower 16 bits with the value in r1
		; R0 is the answer
		
stop    B		stop
		END