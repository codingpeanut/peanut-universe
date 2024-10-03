		; 411440364 PAI, HSIN-CHEN
		AREA	hw4_2, CODE
		ENTRY
		
		; My 8 data bits -> 0xD3 = 1101,0011
		; Correct 12 bits -> 0xD94 = 1101,1001,0100
;		LDR		r0, =0xD2
;		LDR		r0, =0x53
;		LDR		r1, =0xD94		; 0xD94 = 1101,1001,0100

;		LDR		r1, =0xD95		; 0xD95 = 1101,1001,0101	(c0 isn't correct)
;		LDR		r1, =0xD96		; 0xD96 = 1101,1001,0110	(c1 isn't correct)
;		LDR		r1, =0xD9C		; 0xD9C = 1101,1001,1100	(c2 isn't correct)
;		LDR		r1, =0xD14		; 0xD14 = 1101,0001,0100	(c3 isn't correct)

;		LDR		r1, =0xD90		; 0xD90 = 1101,1001,0000	(c0 and c1 aren't correct)
		LDR		r1, =0x594		; 0x51C = 0101,1001,0100	(c2 and c3 aren't correct)

;========================================================================;
; 411440364 PAI, HSIN-CHEN
; find the 8 bits of input 12 bits	--> store in r0
		; 0xD90 = 1101,1001,0000	(c0 and c1 aren't correct)
		; 0x594 = 0101,1001,0100	(c2 and c3 aren't correct)
		
		AND		r5, r1, #4			; r5 = 0000,0000,0100
		ADD		r0, r5, ROR	#2		; r0 = 0000,0000,0001
		
		AND		r5, r1, #0x70		; r5 = 0000,0001,0000
		ADD		r0, r5, ROR #3		; r0 = 0000,0000,0011
		
		AND		r5, r1, #0xF00		; r5 = 0101,0000,0000
		ADD		r0, r5, ROR #4		; r0 = 0000,0101,0010 (0x53)
		
;========================================================================;
; 411440364 PAI, HSIN-CHEN
; find the correct c0, c1, c2, c3, storing in r8
; c0=0, c1=0, c2=1, c3=0

		MOV		r7, r0	
		EOR		r7, r7, r0, ROR #1		
		EOR		r7, r7, r0, ROR #3		
		EOR		r7, r7, r0, ROR #4		
		EOR		r7, r7, r0, ROR #6		
		AND		r8, r7, #1
		
		MOV		r7, r0
		EOR		r7, r7, r0, ROR #2
		EOR		r7, r7, r0, ROR #3
		EOR		r7, r7, r0, ROR #5
		EOR		r7, r7, r0, ROR #6
		AND		r7, r7, #1
		ORR		r8, r8, r7, LSL #1	
		
		ROR		r7, r0, #1	
		EOR		r7, r7, r0, ROR #2
		EOR		r7, r7, r0, ROR #3
		EOR		r7, r7, r0, ROR #7
		AND		r7, r7, #1
		ORR		r8, r8, r7, LSL #2	
		
		ROR		r7, r0, #4
		EOR		r7, r7, r0, ROR #5
		EOR		r7, r7, r0, ROR #6
		EOR		r7, r7, r0, ROR #7
		AND		r7, r7, #1
		ORR		r8, r8, r7, LSL #3	; r8 = 0100	(0x4)

;========================================================================;
; 411440364 PAI, HSIN-CHEN
; find the checksum bit of the received 8 data bits, storing in r12
; c0=0, c1=0, c2=1, c3=1
		
		; 0xD90 = 1101,1001,0000	(c0 and c1 aren't correct)
		; 0x594 = 0101,1001,0100	(c2 and c3 aren't correct)

		AND		r9, r1, #1
		
		AND		r2, r1, #2
		ADD		r9, r2
		
		AND		r2, r1, #8
		ADD		r9, r2, ROR #1
		
		AND		r2, r1, #0x80
		ADD		r9, r2, ROR #4		; r9 = 1000	(0x8)

;========================================================================;
; 411440364 PAI, HSIN-CHEN
; (1) comapare two checksum bit
; (2) count how many 1s in r10

		EOR		r10, r8, r9			; r10 = 1100 (0xC)

		MOV		r2, #0
		MOV		r3, #0x1
		MOV		r4, #4
		
loop  	TST  	r10, r3	 	 	 
 	 	BEQ  	next 
 	 	 
 	 	ADD  	r2, #0x1 
 	 	 
next  	LSL  	r3, r3, #0x1  	 	;r3 move 1 bit to left 
 	 	 
 	 	SUB  	r4, #0x1 
 	 	CMP  	r4, #0x0 
 	 	 
 	 	BNE  	loop 

;========================================================================;
; 411440364 PAI, HSIN-CHEN
; find the wrong data bit
; 0xD90 = 1101,1001,0000
; 0x594 = 0101,1001,0100

		MOV		r11, #1
		
		SUB		r10, #1				; r10 = 0xB
		
		LSL		r11, r11, r10		; r11 = 1000,0000,0000 (0x800)
		EOR		r1, r11, r1			; r1 = 1101,1001,0100	(0xD94)

;========================================================================;
; 411440364 PAI, HSIN-CHEN
;CODE LAST STEP --> find the 8 bits of entering 12 bits	--> store in r6
		; r1 = 1101,1001,0100	(0xD94)
		
		AND		r5, r1, #4			; r5 = 0000,0000,0100
		ADD		r6, r5, ROR	#2		; r6 = 0000,0000,0001
		
		AND		r5, r1, #0x70		; r5 = 0000,0001,0000
		ADD		r6, r5, ROR #3		; r6 = 0000,0000,0011
		
		AND		r5, r1, #0xF00		; r5 = 1101,0000,0000
		ADD		r6, r5, ROR #4		; r6 = 0000,1101,0011 (0xD3)
		
stop	B		stop
		END