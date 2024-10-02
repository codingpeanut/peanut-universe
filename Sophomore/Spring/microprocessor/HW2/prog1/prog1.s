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
; 411440521 JoshLee
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
; 411440521 JoshLee
Reset_Handler
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

; 411440521 JoshLee
IntDefaultHandler
			; let's read the Usage Fault Status Register
			LDR		r7, =Usagefault
			LDRH	r1, [r6, r7]
			TEQ		r1, #0x200
			
			; 15-1
			; r1 should have bit 9 set indicating
			; a devide-by-zero has taken place
			IT		EQ
			LDREQ	r9, =0xDEADDEAD

			; 15-2
			; switch to user Thread mode
			MRS		r8, CONTROL
			ORR		r8, r8, #1
			MSR		CONTROL, r8
			BX		LR

			ALIGN

			END