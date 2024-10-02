;---------------------------------------
;		Author:	411440521 JoshLee		
;		Date:	2023/10/27				
;---------------------------------------
		AREA	prog2, CODE, READONLY
		ENTRY
		
		LDR		R0, =149	; 149
		LDR		R1, =4321	; 4321
		LDR		R2, =0xFFFFFFFF
		
		; -----2's complement-----
		EOR		R0, R0, R2  ; FFFFFF6A
		ADD		R0, R0, #1	; FFFFFF6B (-149)
		
		EOR		R1, R1, R2  ; FFFFEF1E
		ADD		R1, R1, #1	; FFFFEF1F (-4321)
		; -----2's complement-----
		
		ADD		R7, R0, R1
		
		; R7 is the answer
		
stop	B		stop
		END