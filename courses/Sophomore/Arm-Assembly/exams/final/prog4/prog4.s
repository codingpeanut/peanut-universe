; Program 4
		AREA	FinalExam_Pretest_4, CODE, READONLY
		ENTRY

		LDR 	r0, =0x40000000
		LDR		sp, =0x40000020
		LDR		r1, =0x8765ABCD
		LDR		r2, =0xCDEF6543
		LDR		r3, =0xFACEBEEF
		LDR		r4, =0x87654321

		STMIA 	r0, {r1, r2, r3, r4} ; low to high => 0x40000000 to 0x4000000C => r1 to r4
		BL		sub1

		BL		reset_data
		LDMDA 	sp, {r1, r2, r3, r4} ; high to low => 0x40000030 to 0x40000024 => r4 to r1
		BL		sub2

stop	B		stop

reset_data
		STMIB	sp!, {r1, r2, r3, r4} ; low to high => 0x40000024 to 0x40000030 => r1 to r4
		BX		lr

sub1
		; r5 = mask / result
		; r6 = 0x40000000
		; r7 = 0x40000008
		; r8 = total number of 1 in bit 3, 4, 5, 9 and 11
		; r9 = clear bit8

		MOV		r5, #1
		LDR		r6, [r0]
		LDR		r7, [r0, #8]

		MOV		r5, #1
		AND	 	r5, r5, r6, ROR #3
		TST		r5,	#1
		ADDNE	r8, #1

		MOV		r5, #1
		AND	 	r5, r5, r6, ROR #4
		TST		r5,	#1
		ADDNE	r8, #1

		MOV		r5, #1
		AND	 	r5, r5, r6, ROR #5
		TST		r5,	#1
		ADDNE	r8, #1

		MOV		r5, #1
		AND	 	r5, r5, r6, ROR #9
		TST		r5,	#1
		ADDNE	r8, #1

		MOV		r5, #1
		AND	 	r5, r5, r6, ROR #11
		TST		r5,	#1
		ADDNE	r8, #1


		AND		r8, #1			; check total is odd / even
		CMP		r8, #0			; if even
		BEQ		is_even_sub1
		CMP		r8, #1			; if odd
		BEQ		is_odd_sub1

is_even_sub1
		MOV		r8, #1
		B		exit_sub1

is_odd_sub1
		MOV		r8, #0
		B		exit_sub1

exit_sub1
		LDR		r9, =0x100
		BIC		r7, r7, r9
		ORR		r7, r7, r8, LSL #8
		STR		r7, [r0, #8]
		BX		lr


sub2
		; r1 = 0x40000000
		; r2 = 0x40000008
		; r3 = total number of 1 in bit 6, 9, 13, 16 and 19
		; r4 = clear bits
		; r5 = bits 

		LDR		r1, =0
		LDR		r2, =0
		LDR		r3, =0
		LDR		r4, =0
		LDR		r5, =0

		MOV		r5, #1
		LDR		r1, [r0]
		LDR		r2, [r0, #8]

		MOV		r5, #1
		AND		r5, r5, r1, ROR #6
		ADD		r3, r3, r5

		MOV		r5, #1
		AND		r5, r5, r1, ROR #9
		ADD		r3, r3, r5

		MOV		r5, #1
		AND		r5, r5, r1, ROR #13
		ADD		r3, r3, r5

		MOV		r5, #1
		AND		r5, r5, r1, ROR #16
		ADD		r3, r3, r5

		MOV		r5, #1
		AND		r5, r5, r1, ROR #19
		ADD		r3, r3, r5

		AND		r3, #1
		CMP		r3, #0
		BEQ		is_even_sub2
		CMP		r3, #1
		BEQ		is_odd_sub2

is_even_sub2
		MOV		r3, #1
		B		exit_sub2

is_odd_sub2
		MOV		r3, #0
		B		exit_sub2

exit_sub2
		LDR		r4, =0x100000
		BIC		r2, r2, r4
		ORR		r2, r2, r3, LSL #20
		STR		r2, [r0, #8]
		BX		lr

		END