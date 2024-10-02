;---------------------------------------
;		Author:	411440521 JoshLee		
;		Date:	2023/10/27				
;---------------------------------------
		AREA 	prog1, CODE, READONLY
		ENTRY

		LDR		R3, =731         ; R3 = 731

		MOV 	R1, #6           ; R1 = 6
		MUL 	R2, R3, R3       ; R2 = x^2
		MUL 	R1, R2, R1       ; R1 = 6x^2

		MOV 	R2, #9           ; R2 = 9
		MUL 	R2, R3, R2       ; R2 = 9x

		SUB 	R2, R1, R2       ; R2 = 6x^2 - 9x
		ADD 	R2, R2, #2       ; R2 = 6x^2 - 9x + 2

		; R2 is the answer

stop    B 		stop
		END
