		AREA	HW4, CODE, READONLY
		ENTRY

;-----------------------------------------------------------------
;   Correct  8 bits = 0xB5        0b10110101 
;   Correct 12 bits = BA6         0b101110100110
;   Wrong   C0      = BA7         0b101110100111
;   Wrong   C1      = BA4         0b101110100100
;   Wrong   C2      = BAE         0b101110101110
;   Wrong   C3      = B26         0b101100100110
;   Wrong   C0 C2   = BB6         0b101110110110
;   Wrong   C1 C3   = 9A6         0b100110100110
;-----------------------------------------------------------------

		; Registers:
		; r0 - received 12 bits
		; r1 - computed 8 bits
		; r2 - computed 12 bits
		; r3 - received 4 bits (C0 C1 C2 C3)
		; r4 - computed 4 bits (C0 C1 C2 C3)
		; r5 - temp (calcualted 8 bits)
		; r6 - correct 8 bits
		; r7 - temporary counter (number of errors)
		; r8 - temporary counter (length)
		; r10 - correct 12 bits

		LDR     r0, =0xBB6    ; Example input value


; (Step 1) Received 12 bits -> Received 8 bits
		AND     r5, r0, #4			; Binary: 0b100 (d0)
		ORR     r1, r1, r5, ROR #2
		AND     r5, r0, #112		; Binary: 0b1110000 (d3 d2 d1)
		ORR     r1, r1, r5, ROR #3
		AND     r5, r0, #3840		; Binary: 0b111100000000 (d7 d6 d5 d4)
		ORR     r1, r1, r5, ROR #4


; (Step 2) Received 8 bits -> Computed 12 bits (Calculated)
		MOV     r5, #0

		; Calculate C0
		MOV     r5, r1
		EOR     r5, r5, r1, ROR #1
		EOR     r5, r5, r1, ROR #3
		EOR     r5, r5, r1, ROR #4
		EOR     r5, r5, r1, ROR #6
		AND     r2, r5, #1

		; Calculate C1
		MOV     r5, r1
		EOR     r5, r5, r1, ROR #2
		EOR     r5, r5, r1, ROR #3
		EOR     r5, r5, r1, ROR #5
		EOR     r5, r5, r1, ROR #6
		AND     r5, r5, #1
		ORR     r2, r2, r5, LSL #1

		; Calculate C2
		ROR     r5, r1, #1
		EOR     r5, r5, r1, ROR #2
		EOR     r5, r5, r1, ROR #3
		EOR     r5, r5, r1, ROR #7
		AND     r5, r5, #1
		ORR     r2, r2, r5, LSL #3

		; Calculate C3
		ROR     r5, r1, #4
		EOR     r5, r5, r1, ROR #5
		EOR     r5, r5, r1, ROR #6
		EOR     r5, r5, r1, ROR #7
		AND     r5, r5, #1

		; Build caculated 12 bits
		ORR     r2, r2, r5, ROR #25
		AND     r5, r1, #1
		ORR     r2, r2, r5, LSL #2
		BIC     r5, r1, #0xF1
		ORR     r2, r2, r5, LSL #3
		BIC     r5, r1, #0x0F
		ORR     r2, r2, r5, LSL #4


; (Step 3) Hamming 12 bits -> Checksum 4 bits (C0 C1 C2 C3)
		LDR     r5, =0

		; Received 12 bits -> Received checksum 4 bits
		AND     r5, r0, #1			; Binary: 0b1 (c0)
		ORR     r3, r3, r5
		AND     r5, r0, #2			; Binary: 0b10 (c1)
		ORR     r3, r3, r5
		AND     r5, r0, #8			; Binary: 0b1000 (c2)
		ORR     r3, r3, r5, ROR #1
		AND     r5, r0, #0x80		; Binary: 0b10000000 (c3)
		ORR     r3, r3, r5, ROR #4

		; Computed 12 bits -> Computed checksum 4 bits
		AND     r5, r2, #1			; Binary: 0b1 (c0)
		ORR     r4, r4, r5
		AND     r5, r2, #2			; Binary: 0b10 (c1)
		ORR     r4, r4, r5
		AND     r5, r2, #8			; Binary: 0b1000 (c2)
		ORR     r4, r4, r5, ROR #1
		AND     r5, r2, #0x80		; Binary: 0b10000000 (c3)
		ORR     r4, r4, r5, ROR #4


; (Step 4) Correct the 8 bits
		LDR     r5, =0
		LDR     r6, =0
		LDR     r8, =0

		; Count number of wrong bits
count_wrongs
		TST     r5, r6
		ADDNE   r7, #1		; add when computed bit != correct bit
		LSL     r6, #1
		SUB     r8, #1
		CMP     r8, #0
		BGT     count_wrongs

		; Correct 8 bits based on the number of errors (wrong bits)
		LDR     r5, =0
		LDR     r6, =0
		LDR     r8, =0

		; Correct One wrong bit
		CMP     r7, #2
		BEQ     two_wrongs
		MOV     r6, r1
		BNE		done

		; Correct Two wrong bits
two_wrongs
		LDR     r8, =1
		CMP     r7, #2
		BNE     done
		EOR     r5, r3, r4				; 2^n + 2^m
		SUB     r5, #1					; 2^n + 2^m - 1
		EOR     r10, r0, r8, LSL r5

		AND     r5, r10, #4				; Binary: 0b100 (d0)
		ORR     r6, r6, r5, ROR #2
		AND     r5, r10, #112			; Binary: 0b1110000 (d3 d2 d1)
		ORR     r6, r6, r5, ROR #3
		AND     r5, r10, #3840			; Binary: 0b111100000000 (d7 d6 d5 d4)
		ORR     r6, r6, r5, ROR #4


; Stop the program
done	B		done

		END