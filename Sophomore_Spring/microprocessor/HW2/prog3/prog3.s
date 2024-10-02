			AREA   	AIRCRConfig, CODE, READONLY
AIRCR		EQU     0x400000C8
RAMSTART	EQU		0x40000000

start
			LDR     sp, =RAMSTART
			LDR		r3, =0x0F		; 4 bits wide
			MOV		r4, #0x4		; priority group number
			LDR		r5, =0x4A		; 0100 1010 (IRQ)
			BL		set_priority_group_number
			BL		read_priority_group_number
			BL		pri_subpri_number 
stop 		B		stop


; 3(1) set the priority group number to AIRCR register (using empty ascending stack to recover register)
set_priority_group_number
			; use empty ascending stack to recover register
			STMEA   sp!, {r0, r1, r2, r4, lr}
			LDR		r0, =AIRCR	; assuming AIRCR register at 0x400000C8
			LDR		r1, [r0]
			BIC		r1, #0x700		
			MOV		r2, #0X100
			MUL		r4, r2, r4		;r4 = 0x400
			ORR		r1, r1, r4
			STR		r1, [r0]
			LDMEA   sp!, {r0, r1, r2, r4, pc}


; 3(2) read the priority group number from AIRCR register (using full ascending stack to recover register)
read_priority_group_number
			STMFA   sp!, {r0, r1, r2, lr}
			LDR		r0, =AIRCR	
			LDR		r1, [r0]
			LSR		r1, #8			
			AND		r1, #7			
			LDMFA   sp!, {r0, r1, r2, pc}


; 3(3) get pre-emption priority and sub-priority of IRQ from AIRCR register (using empty descending stack to recover register)

pri_subpri_number 
			STMED   sp!, {r3, r4, r5, r6, lr}	
			BIC		r5, r5, r3		;subpriority(r5)
			ADD		r4, #1
			MOV		r6, r5
			LSR		r6, r4			
			LSL		r6, r4			;group priority(r6)
			LDMED   sp!, {r3, r4, r5, r6, pc}


			END