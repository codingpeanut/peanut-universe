; Program 2
		AREA FinalExam_Pretest_2, CODE, READONLY
		ENTRY

		BL initialize

		BL func1
		BL func2
		BL func3
		BL func4
		BL func5

stop	B	stop


initialize
		LDR		r0, =0xDEADBEEF
		LDR 	r1, =0xFACEABCD
		LDR		sp, =0x40000020
		BX		lr


func1
		; r5 = temp
		STMDA	sp!, {r0, r1}
		MOV 	r5, #0xFF
		ORR 	r0, r0, r5, LSL #16
		LDR		r3, = 0x20000000

		; reset temp
		LDR	r5, =0
		BX	lr


func2
		; r5 = temp (target value)
		; r6 = temp ()
		MOV r5, #0xFF				; store 0xFB
		MOV	r6, #0xFF				; clear lowest byte(0x 00 00 00 FF)
		
		; ROR bit12 - bit19 to bit0
		; right shift 3 byte for 0xDEFFBEEF
		; and store to r5
		AND	r5, r5, r0, ROR #12

		; store in r5 to r1
		BIC	r1, r1, r6				; clear lowest byte (mark 1 for delete)
		ORR	r1, r1, r5				; modify value 0xFB to r1

		; reset temp
		LDR	r5, =0
		LDR r6, =0
		
		; push r0, r1 back
		; LDMIB sp!, {r0, r1}		; for restore (if needed)
		BX	lr


; r5 = test number
; r6 = number of 1
; r7 = test each bit (0x 0000 0001)
; r8 = length
func3
		LDR 	r6, =0
		LDR		r7, =1			; r7 = mask
		LDR		r8, =32			; r8 = data length
		EOR		r5, r0, r1		; r5 = mark different bits index

count_different_bit_TST
		CMP		r8, #0
		TST		r5, r7			; tset lowest bit for r5
		ADDNE	r6, #1			; if TST result is 1 (NE), then add 1

		LSL		r7, #1			; right shift 1 bit for mask
		SUB		r8, #1			; counter - 1
		CMP		r8,	#0

		BGT		count_different_bit_TST

		MOV		r3, r6

		; clear temp
		LDR		r5, =0
		LDR 	r6, =0
		LDR		r7, =0
		LDR		r8, =0
		BX		lr


func4	
		; r5 = test data
		; r6 = number of one
		; r7 = test each bit (0x00000001)
		; r8 = length
		; r9 = result of AND (for TST)

		LDR		r6, =0
		LDR		r7, =1
		LDR		r8, =32			; data length
		EOR		r5, r0, r1

count_different_bit_AND
		AND		r9, r5, r7		; 1 for EQ, 0 for NE
		; loop
		CMP     r8, #0
		BEQ     exit_loop		; if data length == 0, break

		CMP		r9, #0
		BGT		is_different	; if r9 > 0, then r9 is EQ (TST)
		BEQ		is_same			; if r9 == 0, then r9 is NE (TST)

is_different
		ADD		r6, #1			; different + 1
		LSL		r7, #1
		SUB		r8, #1
		B		count_different_bit_AND

is_same
		LSL		r7, #1
		SUB		r8, #1
		B		count_different_bit_AND

exit_loop
		MOV		r4, r6
		; clear temp
		LDR		r5, =0
		LDR		r6, =0
		LDR		r7, =0
		LDR		r8, =0
		LDR		r9, =0

		BX		lr


func5
		; r5 = test number
		; r6 = number of one
		; r7 = test each bit
		; r8 = length
		; r9 = result of AND (for TST)
		; r10 = current bit index
		; r11 = address to store bits

		LDR		r6, =0
		LDR		r7, =1
		LDR		r8, =32
		LDR		r10, =0				; current bit index
		LDR		r11, =0x40000050
		EOR		r5, r0, r1
		
count_different_bit_AND_func5
		AND		r9, r5, r7
		;loop
		CMP     r8, #0
		BEQ     exit_loop_func5

		CMP		r9, #0
		BGT		is_different_func5	; if r9 > 0, then r9 is EQ
		BEQ		is_same_func5		; if r9 == 0, then r9 is NE

is_different_func5
		ADD		r6, #1
		LSL		r7, #1				; move to next bit
		SUB		r8, #1				; data length - 1

		; store bits & update address
		STRB	r10, [r11]			; store new result
		ADD		r11, #1				; move to next byte

		; plus count bits 
		ADD		r10, #1				; move to next data index

		B		count_different_bit_AND_func5

is_same_func5
		LSL		r7, #1				; move to next bit
		SUB		r8, #1				; data length - 1
		ADD		r10, #1				; move to next data index
		B		count_different_bit_AND_func5

exit_loop_func5
		MOV	r4, r6
		; clear temp
		LDR	r5, =0
		LDR	r6, =0
		LDR	r7, =0
		LDR	r8, =0
		LDR	r9, =0
		
		BX	lr

		END