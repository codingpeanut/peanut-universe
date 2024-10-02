			AREA   	AIRCRTest, CODE, READONLY
AIRCR		EQU     0x400000C8
RAMSTART	EQU		0x40000020

start
			LDR     sp, =RAMSTART
			LDR 	r0, =AIRCR
				
			; (Step 1) set AIRCR = 0b 1111 1111 (address of AIRCR = 0x400000C8)
			MOV		r2, #0xFF		; r2 = 0b 1111 1111
			STRB	r2, [r0]
			
			; (Step 2) read AIRCR, assume AIRCR width = 6, r2 = 0b 1111 1100 (only 6 bit set successfully)-> simulation
			LDRB	r2, [r0]
			MOV		r2, #0xFC		; r2 = 0b 1111 1100 (assume AIRCR width = 6)
			MOV		r1, #0			; r1 = width_counter
			
			BL		with_test_pattern_LSR
			BL		with_test_pattern_LSL
			BL		without_test_pattern_LSR
			BL		without_test_pattern_LSL
			
stop		B		stop

; 411440521 JoshLee	
; Supplement of TST -> logic AND
; if result == 0 -> Z flag = 1 -> EQ
; if result != 0 -> Z flag = 0 -> NE

; (a) using LSR with test pattern LSR
; silde r3 (test pattern) to check r2 (AIRCR), focus on 1
; r1 = width_counter
; r2 = AIRCR		= 0b 1111 1100 ->     -> 0b 1111 1100
; r3 = test pattern = 0b 1000 0000 -> LSR -> 0b 0100 0000 ...
with_test_pattern_LSR
            STMFD   sp!, {r1-r3, lr}
            MOV		r3, #0x80			; r3 = 0b 1000 0000 (test pattern_a)
TEST1        
            CMP		r1, #8				; if reach max_width?
            BEQ		OUT1				; yes -> test finish ->> width = max_width
            TST		r2, r3				; test pattern & AIRCR == 0?
            BEQ		OUT1            	; EQ (result is 0 before reach max_width) ->> width = width_counter
            ADD		r1, r1, #1			; width_counter++
            LSR		r3, r3, #1			; right slide test pattern
            B		TEST1
OUT1        
            LDMFD  sp!, {r1-r3, pc}

; 411440521 JoshLee
; (b) using LSL with test pattern LSL
; silde r3 (test pattern) to check r2 (AIRCR), focus on 0
; r1 = width_counter
; r2 = AIRCR		= 0b 1111 1100 ->     -> 0b 1111 1100
; r3 = test pattern = 0b 1000 0000 -> LSL -> 0b 0000 0001 ...
with_test_pattern_LSL
			STMFD   sp!, {r1-r4, lr}
			MOV		r3, #0x1			; r3 = 0b 0000 0001 (test_pattern_b)
TEST2		
			CMP		r1, #8				; if reach max_width?
			BEQ		OUT2				; yes -> test finish ->> width = max_width
			TST		r2, r3				; test pattern & AIRCR != 0?
			BNE		OUT2				; NE (result is not 0 before reach max_width) ->> width = width_counter
			ADD		r1, r1, #1			; width_counter_inverse++
			LSL		r3, r3, #1			; left slide test pattern
			B		TEST2
OUT2
			MOV		r4, #0x8
			SUB		r4, r1				; width = max_width - width_counter_inverse
			LDMFD	sp!, {r1-r4, pc}

; 411440521 JoshLee
; (c) using LSR without test pattern LSR
; check r3 (test pattern) by silding r2 (AIRCR)
; r1 = width_counter
; r2 = AIRCR		= 0b 1111 1100
; r3 = test pattern	= 0b 1000 0000
without_test_pattern_LSR
			STMFD   sp!, {r1-r4, lr}
			MOV		r3, #0x1			; r3 = 0b 0000 0001 (test_pattern_c)
TEST3
			CMP		r1, #8				; if reach max_width?
			BEQ		OUT3				; yes -> test finish ->> width = max_width
			TST		r2, r3				; test pattern & AIRCR != 0?
			BNE		OUT3				; NE (result is not 0 before reach max_width) ->> width = width_counter
			ADD		r1, r1, #1			; width_counter++
			LSR		r2, r2, #1			; right slide test pattern
			B		TEST3
OUT3
			MOV		r4, #0x8
			SUB		r4, r1
			LDMFD   sp!, {r1-r4, pc}

; 411440521 JoshLee
; (d) using LSL without test pattern LSL
; check r3 (test pattern) by silding r2 (AIRCR)
; r1 = width_counter
; r2 = AIRCR		= 0b 1111 1100
; r3 = test pattern	= 0b 1000 0000
without_test_pattern_LSL
			STMFD   sp!, {r1-r3, lr}
			MOV		r3, #0x80			; r3 = 0b 1000 0000 (test pattern_d)
TEST4		
			CMP		r1, #8				; if reach max_width?
			BEQ		OUT4				; yes -> test finish ->> width = max_width
			TST		r2, r3				; test pattern & AIRCR == 0?
			BEQ		OUT4				; EQ (result is 0 before reach max_width) ->> width = width_counter
			ADD		r1, r1, #1			; width_counter++
			LSL		r2, r2, #1			; lsft slide test pattern 
			B		TEST4
OUT4		
			LDMFD  sp!, {r1-r3, pc}


			END
