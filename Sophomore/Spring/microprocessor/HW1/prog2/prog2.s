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

            LDR     r1, =CharData       ; starting address of characters
Loop1_Tx
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r0, #0              ; null terminated?
            BLNE    Transmit            ; send character to UAER0
            BNE     Loop1_Tx            ; continue if not a '0'

			MOV		r9, #20
Loop1_Rx
            BL		Receive
			STRB	r0, [r1], #1
			SUBS	r9, r9, #1
			BNE		Loop1_Rx

done        B       done                ; otherwise we're done

; Subroutine UARTConfig
; This subroutine configures the I/O pins first. It
; then sets up the UART control register. The
; parameters
; are set to 8 bits, no parity and 1 stop bit.
; Registers used:
; r5 - scratch register
; r6 - scratch register
; inputs: none
; outputs: none
; 411440521 JoshLee
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
; 411440521 JoshLee
; Subroutine Transmit
; This routine puts one byte into the UART
; for transmitting.
; Register used:
; r5 - scratch
; r6 - scratch
; inputs: r0 - byte to transmit
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
			TST		r6, 0xE				; verify data
			LDRB	r0, [r5]
			LDMDB	sp!, {r5, r6, pc}
CharData
            DCB     "TKU-ECE-411440521-JoshLee", 0
            END