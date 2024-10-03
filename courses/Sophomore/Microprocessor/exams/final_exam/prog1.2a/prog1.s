Stack		EQU		0x00000100
DivbyZ		EQU 	0xD14
SYSHNDCTRL	EQU		0xD24
Usagefault	EQU		0xD2A
NVICBase	EQU		0xE000E000
RAMSTART	EQU		0x40000000

			AREA STACK, NOINIT, READWRITE, ALIGN = 3
StackMem
			SPACE Stack
			PRESERVE8


			AREA	Timer, CODE, READONLY
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
			MOVW 	r10, #0xBEEF
			MOVT 	r10, #0xDEAD
Spot		B 		Spot


CPU_CONFIG
			; base 0x40000000
			LDR 	r0, =0x40000000		; base 0x400FE000
			MOV 	r2, #0x60 			; offset 0x060 for this register
			LDR 	r1, =0x01C00540
			STR 	r1, [r0, r2] 		; write the register’s content
			
			LDR 	r7, =0x604 			; enable timer0 - RCGCTIMER
			LDR 	r1, [r0, r7] 		; p. 321, base 0x400FE000
			ORR 	r1, #0x1 			; offset - 0x604
			STR 	r1, [r0, r7] 		; bit 0
			
			NOP
			NOP
			NOP
			NOP
			NOP 						; give myself 5 clocks per spec

TIMER_CONFIG
			; base 0x40030000
			LDR 	r8, =0x40000000 	; configure timer0 to be
										; one-shot, p.698 GPTMTnMR
			MOV 	r7, #0x4 		
			LDR 	r1, [r8, r7] 		; offset 0x4
			ORR 	r1, #0x21 			; bit 5 = 1, 1:0 = 0x1
			STR 	r1, [r8, r7]
			
			LDR 	r1, [r8] 			; set as 16-bit timer only
			ORR 	r1, #0x4 			; base 0x40030000
			STR 	r1, [r8] 			; offset 0, bit[2:0] = 0x4
			
			; offset 0x30
			MOV 	r7, #0x30 			; set the match value at 0
			; match value 32 bits (from 0x FFFF FFFF to match value)
			LDR 	r1, =0xFF1B1E3F 	; match value = 5 sec * 15 MHz = 0xE4E1C0, 0xFFFFFFFF - 0xE4E1C0 = 0xFF1B1E3F
			STR 	r1, [r8, r7] 		; offset - 0x38

GPTM_CONFIG
			LDR 	r8, =0x40000000
			MOV 	r7, #0x18 			; set bits in the GPTM
			LDR 	r1, [r8, r7] 		; Interrupt Mask Register
			ORR 	r1, #0x10 			; p. 714 - base: 0x40030000
			STR 	r1, [r8, r7] 		; offset - 0x18, bit 5

NVIC_CONFIG
			LDR 	r6, =0xE000E000 	; enable interrupt on timer0
										; p. 132, base 0xE000E000
			MOV 	r7, #0x100 			; offset - 0x100, bit 19
			MOV 	r1, #(1<<19) 		; enable bit 19 for timer0
			STR 	r1, [r6, r7]




start
			LDR 	r6, =0x40000000 	; start the timer
			MOV 	r7, #0xC
			LDR 	r1, [r6, r7]
			ORR 	r1, #0x1
			STR 	r1, [r6, r7] 		; go!!

stop		B		stop
			END