; Program 3
		AREA	FinalExam_Pretest_3, CODE, READONLY
		ENTRY
		LDR		r0, = 0x40000000
		LDR		r1, = 0xCDEF5678
		LDR		r2, = 0x5678CDEF
		LDR		r3, = 0xBEEFFACE
		LDR		r4, = 0xFACEBEEF
		LDR		sp, = 0x40000020
		LDR		r12, =0x40000030
		STMIA	r0, {r1, r2, r3, r4}

		; (1)
		; LDR		r10, =0x1234ABCD
		; BL		CheckParity
		; uncomment to run (1)

		; (2)
		LDMDB	r0, {r1, r2, r3, r4}

		; data = 0xCDEF5678
		MOV		r10, r1
		BL		CheckParity

		; data = 0x5678CDEF
		MOV		r10, r2
		BL		CheckParity

		; data = 0xBEEFFACE
		MOV		r10, r3
		BL		CheckParity

		; data = 0xFACEBEEF
		MOV		r10, r4
		BL		CheckParity

		STMIB	r6, {r1, r2, r3, r4}

stop	B	stop

		; r7 = data length
		; r8 = lowest bit value
		; r9 = number of 1
		; r10 = data
		; r11 = 0xFACEFACE / 0xBEEFBEEF
		; r12 = store address

CheckParity 
		STMIA	sp!, {r8, r9, r11, r12}
		MOV     r9, #0
		MOV		r7, #32

count_parity
		CMP     r7, #0         	; if no data
		BEQ     count_parity_done

		AND     r8, r10, #1     ; check lowest bit is odd / even
		ADD     r9, r9, r8		; sum total 1 number
		ROR     r10, #1			; right shift for data
		SUB		r7, #1			; length - 1
		B       count_parity

count_parity_done
		AND		r9, #1			; check odd / even
		CMP     r9, #1
		BEQ		odd_parity
		BNE		even_parity

odd_parity
		LDR		r11, =0xFACEFACE
		B		exit

even_parity
		LDR		r11, =0xBEEFBEEF
		B		exit

exit
		STR		r11, [r12]
		LDMDB	sp!, {r8, r9, r11, r12}
		ADD		r12, #4
		BX      lr

		END