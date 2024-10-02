            AREA    UARTDEMO, CODE, READONLY
PINSEL0     EQU     0XE002C000          ; controls the function of the pins
U0START     EQU     0XE000C000          ; start of UART0 register
LCR0        EQU     0XC                 ; line control register for UART0
LSR0        EQU     0X14                ; line status register for UART0
RAMSTART    EQU     0X40000000          ; start of onboard RAM for 2104
; 411440521 JoshLee
            ENTRY
start
            LDR     sp, =RAMSTART       ; set up stack pointer
            BL      UARTConfig          ; initialize/configure UART0

; 3(a)		to copy the string (variable StudentData) reversely to memory starting from address 0x40000070
; ------------------------- store student data reversely -------------------------
			LDR		r3, =0x40000070
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #41				; rev_head_address(r1) = StudentData(r1) + string_length(#43)
			MOV		r2, #42				; length_counter = string_length + 1
			MOV		r4, #0				; to clear next byte
Loop1_STR_Rev
            LDRB    r5, [r1], #-1       ; load character, decrement address
            STRB	r5, [r3], #1		; store character, increment address
			SUB		r2, #1				; length_counter counter--
			CMP     r2, #0              ; length_counter greater than 0?
			STRB	r4, [r3]			; clear next byte
            BNE     Loop1_STR_Rev       ; continue if length_counter not equals to 0
; ------------------------- store student data reversely -------------------------

; 411440521 JoshLee
; 3(b)		to use calls to subroutine Transmit to display a sequence of 10 characters at memory address 0x40000078 in the UART #1 window after program execution by using F5 (Run)
; ----------------------------- display 10 characters ----------------------------
			LDR		r1, =0x40000078
			MOV		r2, #10				; length_counter
Loop2_Tx_x_char
            LDRB    r0, [r1], #1		; load character, decrement address
			CMP     r2, #0              ; length_counter greater than 0?
			BLNE	Transmit			; send character to UART
			SUB		r2, #1				; length_counter counter--
            BNE     Loop2_Tx_x_char     ; continue if length_counter not equals to 0
; ----------------------------- display 10 characters ----------------------------

; 411440521 JoshLee
; 3(c)		to use calls to subroutine Receive to receive a sequence of error-free 20 characters from the UART0 and put them in memory starting from address 0x400000A0. (Show execution results by using F10 (Step over) and F11 (Step).)
; ----------------------------- receive 20 characters ----------------------------
			MOV		r9, #20
			LDR		r1, =0x400000A0
Loop3_Rx_xx_char
            BL		Receive
			STRB	r1, [r0], #1
			SUBS	r9, r9, #1
			BNE		Loop3_Rx_xx_char
; ----------------------------- receive 20 characters ----------------------------

done        B       done                ; otherwise we're done

; Subroutine UARTConfig
; This subroutine configures the I/O pins first. It
; then sets up the UART control register. The
; parameters
; are set to 8 bits, no parity and 1 stop bit.
; Registers used:
; r5   scratch register
; r6   scratch register
; inputs: none
; outputs: none

UARTConfig
            STMIA   sp!, {r5, r6, lr}
            LDR     r5, =PINSEL0        ; base address of register
            LDR     r6, [r5]            ; get contents
            BIC     r6, r6, #0xF        ; clear out lower nibble
            ORR     r6, r6, #0x5        ; sets P0.0 to Tx0 and P0.1 to Rx0
            STR     r6, [r5]            ; r/modify/w back to register
            LDR     r5, =U0START
            MOV     r6, #0x83           ; set 8 bits, no parity, 1 stop bit
            STRB    r6, [r5, #LCR0]     ; write control byte to LCR
            MOV     r6, #0x61           ; 9600 baud @15 MHz VPB clock
            STRB    r6, [r5]            ; store control byte
            MOV     r6, #3              ; set DLAB = 0
            STRB    r6, [r5, #LCR0]     ; Tx and Rx buffers set up
            LDMDB   sp!, {r5, r6, pc}


; Subroutine Transmit
; This routine puts one byte into the UART
; for transmitting.
; Register used:
; r5 - scratch
; r6 - scratch
; inputs: r0- byte to transmit
; outputs: none
; 411440521 JoshLee

Transmit
            STMIA   sp!, {r5, r6, lr}
            LDR     r5, =U0START
wait_Tx
			LDRB 	r6, [r5, #LSR0]     ; get status of buffer
            TST     r6, #0x20           ; buffer empty?
            BEQ     wait_Tx             ; spin until buffer empty
            STRB    r0, [r5]
            LDMDB   sp!, {r5, r6, pc}

Receive
			STMIA	sp!, {r5, r6, lr}
			LDR		r5, =U0START
wait_Rx
			LDRB	r6, [r5, #LSR0]		; get status of buffer
			TST		r6, #1				; data ready?
			BEQ		wait_Rx				; until data ready
			LDRB	r0, [r5]
			LDMDB	sp!, {r5, r6, pc}

StudentData
			;        0                    21   26 29     36   41
			DCB     "411440521-Lee-Midterm Exam in Spring 2024!", 0		; string_length = 42 (index: 0~41)
            END