            AREA    UARTDEMO, CODE, READONLY
PINSEL0     EQU     0XE002C000          ; controls the function of the pins
U0START     EQU     0XE000C000          ; start of UART0 register
LCR0        EQU     0XC                 ; line control register for UART0
LSR0        EQU     0X14                ; line status register for UART0
RAMSTART    EQU     0X40000000          ; start of onboard RAM for 2104

            ENTRY
start
            LDR     sp, =RAMSTART       ; set up stack pointer
            BL      UARTConfig          ; initialize/configure UART0

; 2(c)		display reversely the string words
; --------------------- display reversely the string words -----------------------
; string_length = 42 (index: 0~41)
; 0                    21   26 29     36   41
; 411440521-Lee-Midterm Exam in Spring 2024!

; for '!' at 41
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #41				; for '!'
			LDRB	r0, [r1]			; load character
			BL	    Transmit            ; send character to UAER0

; for "2024" at 37
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #37				; for "2024"
			MOV		r2, #4				; length_counter = 4
Loop3_2024
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r2, #0              ; length_counter greater than 0?
            BLNE    Transmit            ; send character to UAER0
			SUB		r2, #1				; counter--
            BNE     Loop3_2024          ; continue if print_counter not equals to 0

; for ' ' at 36
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #36				; for ' '
			LDRB	r0, [r1]			; load character
			BL	    Transmit            ; send character to UAER0

; for "Spring" at 30
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #30				; for "Spring"
			MOV		r2, #6				; length_counter = 6
Loop3_Spring
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r2, #0              ; length_counter greater than 0?
            BLNE    Transmit            ; send character to UAER0
			SUB		r2, #1				; counter--
            BNE     Loop3_Spring        ; continue if print_counter not equals to 0

; for ' ' at 29
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #29				; for ' '
			LDRB	r0, [r1]			; load character
			BL	    Transmit            ; send character to UAER0

; for "in" at 27
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #27				; for "Spring"
			MOV		r2, #2				; length_counter = 2
Loop3_in
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r2, #0              ; length_counter greater than 0?
            BLNE    Transmit            ; send character to UAER0
			SUB		r2, #1				; counter--
            BNE     Loop3_in        ; continue if print_counter not equals to 0
; 411440521JoshLee
; for ' ' at 26
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #26				; for ' '
			LDRB	r0, [r1]			; load character
			BL	    Transmit            ; send character to UAER0

; for "Exam" at 22
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #22				; for "Exam"
			MOV		r2, #4				; length_counter = 4
Loop3_Exam
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r2, #0              ; length_counter greater than 0?
            BLNE    Transmit            ; send character to UAER0
			SUB		r2, #1				; counter--
            BNE     Loop3_Exam	        ; continue if print_counter not equals to 0

; for ' ' at 21
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #21				; for ' '
			LDRB	r0, [r1]			; load character
			BL	    Transmit            ; send character to UAER0

; for "411440521-Lee-Midterm" at 0
			LDR     r1, =StudentData    ; starting address of StudentData
			ADD		r1, #0				; for "411440521-Lee-Midterm"
			MOV		r2, #21				; length_counter = 21
Loop3_411440521
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r2, #0              ; length_counter greater than 0?
            BLNE    Transmit            ; send character to UAER0
			SUB		r2, #1				; counter--
            BNE     Loop3_411440521	    ; continue if print_counter not equals to 0
; --------------------- display reversely the string words -----------------------

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
;

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