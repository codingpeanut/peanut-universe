		AREA		HW4, CODE, READONLY
		ENTRY
;-----------------------------------------------------------------
;	correct  8 bits = 0xB5 		0b10110101
;	correct 12 bits = BA6 	   	0b101110100110
;	wrong   c0      = BA7		0b101110100111
;	wrong 	c1		= BA4		0b101110100100
;	wrong 	c2		= BAE		0b101110101110
;	wrong	c3		= B26		0b101100100110
;	wrong 	c0 c2   = BB6		0b101110110110
;	wrong	c1 c3	= 9A6 		0b100110100110
;-----------------------------------------------------------------

;	r0 = recevied 12 bits
;	r1 = computed 8 bits 
;	r2 = computed 12 bits
;	r3 = recevied 4 bits (c0 c1 c2 c3)
;	r4 = computed 4 bits (c0 c1 c2 c3)


		LDR		r0, =0xBA7	; Example test data


; 411440521 JoshLee
; (Step 1) Received 12 bits -> Received 8 bits
;	r5 = temp
;	r1 = computed 8 bits
;	r0 = recevied 12 bits
		AND		r5, r0, #4				; 0b100
		ORR		r1, r1, r5, ROR #2
		AND		r5, r0, #112			; 0b1110000
		ORR		r1, r1, r5, ROR #3
		AND 	r5, r0, #3840			; 0b111100000000
		ORR		r1, r1, r5, ROR	#4		; taken out 8 bits data

;	Initialize
		MOV r5, #0


; 411440521 JoshLee
; (Step 2) Received 8 bits -> Computed 12 bits (Calculated)
;	r1 = computed 8 bits
;	r5 = temp
;	r2 = computed 12 bits

		; claculate c0
		MOV		r5, r1		
		EOR		r5, r5, r1, ROR #1	;d0 EOR d1
		EOR		r5, r5, r1, ROR	#3	;d0 EOR d1 EOR d3
		EOR		r5, r5, r1, ROR	#4	;d0 EOR d1 EOR d3 EOR d4
		EOR		r5, r5, r1, ROR	#6	;d0 EOR d1 EOR d3 EOR d4 EOR d6
		AND		r2, r5, #1			;c0 -> r2
									;*notes* r4 AND #1 only change bit0  
				
		; claculate c1
		MOV		r5, r1		
		EOR		r5, r5, r1, ROR #2	;d0 EOR d2
		EOR		r5, r5, r1, ROR	#3	;d0 EOR d2 EOR d3
		EOR		r5, r5, r1, ROR	#5	;d0 EOR d2 EOR d3 EOR d5
		EOR		r5, r5, r1, ROR	#6	;d0 EOR d2 EOR d3 EOR d5 EOR d6
		AND		r5, r5, #1			;save bit0 (c1)
		ORR		r2, r2, r5, LSL	#1	
		
		
		; calculate c2
		ROR		r5, r1, #1			;bit0 = d1
		EOR		r5, r5, r1, ROR #2	;d1 EOR d2
		EOR		r5, r5, r1, ROR	#3	;d1 EOR d2 EOR d3
		EOR		r5, r5, r1, ROR	#7	;d1 EOR d2 EOR d3 EOR d7
		AND		r5, r5, #1			;save bit0 (c2)
		ORR		r2, r2, r5, LSL	#3
		
		
		; calculate c3
		ROR		r5, r1, #4
		EOR		r5, r5, r1, ROR #5	;d4 EOR d5
		EOR		r5, r5, r1, ROR #6	;d4 EOR d5 EOR d6
		EOR		r5, r5, r1, ROR #7	;d4 EOR d5 EOR d6 EOR d7
		AND		r5, r5, #1			;save bit0 (c3)
		
		; Final
		ORR		r2, r2, r5, ROR #25	;bit7 = r3
		AND		r5, r1, #1			;Find d0
		ORR		r2, r2, r5, LSL #2	;Add d0
		BIC		r5, r1, #0xF1		;Find d1,d2,d3
		ORR		r2, r2, r5, LSL #3	;Add d1,d2,d3
		BIC		r5, r1, #0x0F		;Find d4,d5,d6,d7
		ORR		r2, r2, r5, LSL #4	;Add d4,d5,d6,d7
		; 411440521 JoshLee
; Initialize
		LDR		r5, = 0


; 411440521 JoshLee	
; (Step 3) Hamming 12 bits -> Checksum 4 bits (C0 C1 C2 C3)
;	r0 = recevied 12 bits 
;	r2 = computed 12 bits
;	r3 = recevied 4 bits
;	r4 = computed 4 bits
;	r5 = temp 
		
		; recevied 12 bits -> recevied 4 bits
		AND		r5, r0, #1			; 0b1 = 1 (c0)
		ORR		r3, r3, r5			; 12 bits(bit0) -> r5(bit0)
		AND		r5, r0, #2			; 0b10 = 2 (c1)
		ORR		r3, r3, r5			; 12 bits(bit1) -> r5(bit1)
		AND		r5, r0, #8			; 0b1000 = 8 (c2)
		ORR		r3, r3, r5, ROR	#1	; 12 bits(bit3) -> r5(bit2)
		AND		r5, r0, #0x80		; 0b10000000 = 0x80 (c3)
		ORR		r3, r3, r5, ROR	#4	; 12 bits(bit7) -> r5(bit3)
		; r3 recevied checksum (4 bits)
		
		; computed 12 bits -> computed 4 bits
		AND		r5, r2, #1			; 0b1 = 1 (c0)
		ORR		r4, r4, r5			; 12 bits(bit0) -> r5(bit0)
		AND		r5, r2, #2			; 0b10 = 2 (c1)
		ORR		r4, r4, r5			; 12 bits(bit1) -> r5(bit1)
		AND		r5, r2, #8			; 0b1000 = 8 (c2)
		ORR		r4, r4, r5, ROR	#1	; 12 bits(bit3) -> r5(bit2)
		AND		r5, r2, #0x80		; 0b10000000 = 0x80 (c3)
		ORR		r4, r4, r5, ROR	#4	; 12 bits(bit7) -> r5(bit3)
		; r4 computed checksum (4 bits)
		
		; Initialize
		LDR r5, =0

; 411440521 JoshLee
; (Step 4) Correct the 8 bits
;		r0 = recevied 12 bits
;		r1 = computed 8 bits
;		r2 = computed 12 bits
;		r3 = recevied 4 bits
;		r4 = computed 4 bits
;		r10 = correct 12 bits
;		r6 = correct 8 bits
;		r5, r7, r8 = temp

		EOR		r5, r3, r4
		LDR 	r6, =1
		LDR		r7, =0
		LDR		r8, =4

; count worong bits
count_wrongs
		TST		r5, r6			
		ADDNE	r7, #1
		LSL		r6, #1
		SUB		r8, #1
		CMP		r8, #0
		BGT		count_wrongs
		; r7 = how many error bits
		
		; Clear temp
		LDR		r5, =0
		LDR		r6, =0
		LDR		r8, =0
		
		; Correct 8 bits based on the number of errors (wrong bits)
		CMP		r7, #1
		BEQ		one_wrong
		CMPNE	r7, #2
		BEQ		two_wrongs
		BNE		done

; 411440521 JoshLee
; one wrong number
one_wrong
		MOV		r6, r1
		B		done

; 411440521 JoshLee
; two wrong number
two_wrongs
		LDR		r8, =1
		CMP		r7, #2
		BNE		done

		EOR		r5, r3, r4				; 2^n + 2^m
		SUB		r5, #1					; 2^n + 2^m - 1 (wrong bit index)
		EOR		r10, r0, r8, LSL r5		; wrong bit index

		AND		r5, r10, #4				; Binary: 0b100 (d0)
		ORR		r6, r6, r5, ROR #2
		AND		r5, r10, #112			; Binary: 0b1110000 (d3 d2 d1)
		ORR		r6, r6, r5, ROR #3
		AND 	r5, r10, #3840			; Binary: 0b111100000000 (d7 d6 d5 d4)
		ORR		r6, r6, r5, ROR	#4

done
		; Clear temp
		LDR		r5, =0
		LDR		r7, =0
		LDR		r8, =0


stop	B 	stop
		END