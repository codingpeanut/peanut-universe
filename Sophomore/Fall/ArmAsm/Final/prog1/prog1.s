; Program 1
		AREA 	FinalExam_Pretest_1, CODE, READONLY
		ENTRY

; Q1.STMIA + LDMDA
		BL 		Initialize
		LDR 	r8, =0x40000020
		LDR 	r9, =0x4000002C

		STMIA 	r8, {r0, r1, r2, r3}
		LDMDA 	r9, {r4, r5, r6, r7}

; Q2.STMIB + LDMDB
		BL		Initialize
		LDR 	r8, =0x4000001C
		LDR 	r9, =0x40000030

		STMIB 	r8, {r0, r1, r2, r3}
		LDMDB 	r9, {r4, r5, r6, r7}

; Q3.STMDA + LDMIA
		BL		Initialize
		LDR 	r8, =0x4000002C
		LDR 	r9, =0x40000020

		STMDA 	r8, {r0, r1, r2, r3}
		LDMIA 	r9, {r4, r5, r6, r7}

; Q4.STMDB + LDMIB
		BL		Initialize
		LDR 	r8, =0x40000030
		LDR 	r9, =0x4000001C

		STMDB	r8, {r0, r1, r2, r3}
		LDMIB 	r9, {r4, r5, r6, r7}

stop	B		stop

Initialize
		LDR 	r0, =0xBBBBBBBB 
		LDR 	r1, =0xFFFFFFFF 
		LDR 	r2, =0xEEEEEEEE 
		LDR 	r3, =0xDDDDDDDD

		LDR		r4, =0
		LDR		r5, =0
		LDR		r6, =0
		LDR		r7, =0

		BX		lr

		END