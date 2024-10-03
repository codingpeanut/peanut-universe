            AREA    UARTDEMO, CODE, READONLY
PINSEL0     EQU     0XE002C000          ; controls the function of the pins
U0START     EQU     0XE000C000          ; start of UART0 register
LCR0        EQU     0XC                 ; line control register for UART0
LSR0        EQU     0X14                ; line status register for UART0
RAMSTART    EQU     0X40000020          ; start of onboard RAM for 2104

            ENTRY
start
            LDR     sp, =RAMSTART       ; set up stack pointer
            BL      UARTConfig          ; initialize/configure UART0

            LDR     r1, =CharData       ; starting address of characters
Loop1
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r0, #0              ; null terminated?
            BLNE    Transmit            ; send character to UAER0
            BNE     Loop1	            ; continue if not a '0'

done        B       done                ; otherwise we're done

; Subroutine UARTConfig
; This subroutine configures the I/O pins first. It
; then sets up the UART control register. The
; parameters
; are set to 8 bits, no parity and 1 stop bit.
; Registers used:
; r5 – scratch register
; r6 – scratch register
; inputs: none
; outputs: none
; 411440521JoshLee
; full descending stack (a)(b)
UARTConfig
            STMDB   sp!, {r5, r6, lr}

			LDR     r5, =PINSEL0        ; base address of register
            LDR     r6, [r5]            ; get contents
            BIC     r6, r6, #0xF        ; clear out lower nibble
            ORR     r6, r6, #0x5        ; sets P0.0 to Tx0 and P0.1 to Rx0
            STR     r6, [r5]            ; r/modify/w back to register

			LDR     r5, =U0START
            ; MOV     r6, #0x9C           ; set 5 bits, even parity, 2 stop bit
			MOV     r6, #0x8B           ; set 8 bits, odd parity, 1 stop bit -> 1(c)
            STRB    r6, [r5, #LCR0]     ; write control byte to LCR

			; MOV     r6, #0xEA           ; 12800 baud @48 MHz VPB clock
            MOV     r6, #0xF			; 12800 baud @3 MHz VPB clock -> 1(c)
			STRB    r6, [r5]            ; store control byte

			; MOV     r6, #0x1C			; set DLAB = 0
            MOV     r6, #0xB				; set DLAB = 0 -> 1(c)
			STRB    r6, [r5, #LCR0]     ; Tx and Rx buffers set up

			LDMIA   sp!, {r5, r6, pc}

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
wait
			LDRB 	r6, [r5, #LSR0]      ; get status of buffer
            CMP     r6, #0x20            ; buffer empty?
            BEQ     wait	             ; spin until buffer empty
            STRB    r0, [r5]
            LDMDB   sp!, {r5, r6, pc}

CharData
            DCB     "TKU-ECE-411440521-JoshLee", 0
            END