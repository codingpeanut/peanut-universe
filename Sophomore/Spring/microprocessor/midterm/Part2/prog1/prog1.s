Stack		EQU		0x00000100
DivbyZ		EQU 	0xD14
SYSHNDCTRL	EQU		0xD24
Usagefault	EQU		0xD2A
NVICBase	EQU		0xE000E000

			AREA STACK, NOINIT, READWRITE, ALIGN = 3
StackMem
			SPACE Stack
			PRESERVE8

			AREA	RESET, CODE, READONLY
			THUMB

; The vector table sits here
; We'll define just a few of them and leave the rest at 0 for now
			DCD		StackMem + Stack 	; Top of Stack
			DCD		Reset_Handler 		; Reset Handler
			DCD		NmiISR 				; NMI Handler
			DCD		FaultISR 			; Hard Fault Handler
			DCD		IntDefaultHandler 	; MPU Fault Handler
			DCD		IntDefaultHandler 	; Bus Fault Handler
			DCD		IntDefaultHandler 	; Usage Fault Handler

			EXPORT	Reset_Handler
			ENTRY

Reset_Handler
			; MRS		r8, CONTROL
			; ORR		r8, #1
			; MSR		CONTROL, r8

			; enable the divide-by-zero trap
			; located in the NVIC
			; base: 0xE000E000
			; offset: 0xD14
			; bit: 4
			LDR 	r6, =NVICBase
			LDR 	r7, =DivbyZ
			LDR 	r1, [r6, r7]
			ORR 	r1, #0x10 ; enable bit 4
			STR 	r1, [r6, r7]

			; now turn on the usage fault exception
			LDR 	r7, =SYSHNDCTRL ; (p. 163)
			LDR 	r1, [r6, r7]
			ORR 	r1, #0x40000
			STR 	r1, [r6, r7]

			; try out a divide by 2 then a divide by 0!
			MOV 	r0, #0
			MOV 	r1, #0x11111111
			MOV 	r2, #0x22222222
			MOV		r3, #0x33333333

			; this divide works just fine
			UDIV 	r4, r2, r1
			; this divide takes an exception
			UDIV 	r5, r3, r0

Exit		B		Exit

NmiISR		B		NmiISR
FaultISR	B		FaultISR

IntDefaultHandler
			; let's read the Usage Fault Status Register
			LDR		r7, =Usagefault
			LDRH	r1, [r6, r7]
			TEQ		r1, #0x200
			BNE		Happened
			BEQ		NotHappened


Happened
			LDR		r3, =MSG_with_Error
			LDR		r1, =0x20000030			; starting address for string to be write
Loop1_STR_string
			LDR		r5, [r3], #1
			STRB	r5, [r1], #1
			CMP		r5, #0
			BNE		Loop1_STR_string
			
			MRS		r8, CONTROL
			ORR		r8, #1
			MSR		CONTROL, r8
			
			BX		lr


NotHappened
			LDR		r3, =MSG_without_Error
			LDR		r1, =0x20000090			; starting address for string to be write
Loop2_STR_string
			LDR		r5, [r3], #1
			STRB	r5, [r1], #1
			CMP		r5, #0
			BNE		Loop2_STR_string
			
			MRS		r8, CONTROL
			ORR		r8, #1
			MSR		CONTROL, r8
			
			BX		lr


done		B		done
			ALIGN
MSG_with_Error
			DCB		"DIVIDE-BY-0 Happened!", 0
MSG_without_Error
			DCB		"DIVIDE-BY-0 Not Happened!", 0
			END