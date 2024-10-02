		AREA	PreTest4, CODE, READONLY
		ENTRY

		; Load values into registers
		LDR		r0, =0x8765ABCD		; in 0x40000000
		LDR		r1, =0xABCD8765		; in 0x40000004
		LDR		r2, =0xFACEBEEF		; in 0x40000008
		LDR		r3, =0xDEADBEEF		; in 0x4000000C

		; Load base addresses into registers
		LDR		r6, =0x40000000
		LDR		r7, =0x40000004
		LDR		r8, =0x40000008
		LDR		r9, =0x4000000C

		; Store values into base memory addresses
		STR		r0, [r6]
		STR		r1, [r7]
		STR		r2, [r8]
		STR		r3, [r9]

		; Load values from memory back into registers
		LDR		r0, [r6]
		LDR		r1, [r7]
		LDR		r2, [r8]
		LDR		r3, [r9]

		; Calculate parity for r0 and update r2
		; calculate checksum bit using bits	9876543210
		; 							        * * * * *
		; r4 is temp
		; r0 is value of 0x40000000 (0x8765ABCD)
		; r2 is value of 0x40000008 (0xFACEBEEF)
		ROR		r4, r0, #1			; d1
		EOR		r4, r4, r0, ROR #3	; d1 XOR d3
		EOR		r4, r4, r0, ROR #5	; d1 XOR d3 XOR d5
		EOR		r4, r4, r0, ROR #7	; d1 XOR d3 XOR d5 XOR d7
		EOR		r4, r4, r0, ROR #9	; d1 XOR d3 XOR d5 XOR d7 XOR d9
		AND		r4, r4, #1			; isolate bit (lowest bit)
									; for odd parity
		EOR		r4, r4, #1			; if r4 == 1 -> set bit12 = 0
									; if r4 == 0 -> set bit12 = 1
		ORR		r2, r2, r4, LSL #12	; set bit12(0xFACEBEEF) = r4

		; Store updated value in memory
		STR		r2, [r8]

		; Calculate parity for r1 and update r3
		; calculate checksum bit using bits	9876543210
		; 							         * * * *
		; r5 is temp
		; r1 is value of 0x40000004 (0xABCD8765)
		; r3 is value of 0x4000000C (0xDEADBEEF)
		ROR		r5, r1, #2			; d2
		EOR		r5, r5, r1, ROR #4	; d2 XOR d4
		EOR		r5, r5, r1, ROR #6	; d2 XOR d4 XOR d6
		EOR		r5, r5, r1, ROR #8	; d2 XOR d4 XOR d6 XOR d8
		AND		r5, r5, #1			; isolate bit (lowest bit)
									; for even parity
									; if r5 == 1 -> set bit15 = 1
									; if r5 == 0 -> set bit15 = 0
		ORR		r3, r3, r5, LSL #15	; set bit15(0xDEADBEEF) = r5

		; Store updated value in memory
		STR		r3, [r9]

stop	B		stop

		END