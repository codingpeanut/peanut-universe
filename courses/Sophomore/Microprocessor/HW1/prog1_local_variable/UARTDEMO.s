            AREA    UARTDEMO, CODE, READONLY
PINSEL0     EQU     0XE002C000          ; controls the function of the pins
U0START     EQU     0XE000C000          ; start of UART0 register
LCR0        EQU     0XC                 ; line control register for UART0
LSR0        EQU     0X14                ; line status register for UART0
RAMSTART    EQU     0X40000000          ; start of onboard RAM for 2104
            ENTRY
start
; Setup the UART
; ------------------------------------------------------------------------------------------------------
            LDR     sp, =RAMSTART       ; set up stack pointer
            BL      UARTConfig          ; initialize/configure UART0

; Store CharData as a local variable
; ------------------------------------------------------------------------------------------------------
            LDR     r1, =CharData       ; starting address of characters
			; Allocate space on the stack for local variables
			; ADD 	sp, sp, #28    		; Reserve space for a 28-byte string

			; Store CharData onto the stack
			MOV		r0, sp				; Store starting address
			BL		strcpy          	; Call the strcpy function to copy the string to the stack
			MOV		sp, r0				; Move stack pointer
			MOV 	r2, r1       		; Load CharData from the stack into register r2

; Print Normal String
; ------------------------------------------------------------------------------------------------------
			MOV		r1, r2
Loop1_Tx
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r0, #0              ; null terminated?
            BLNE    Transmit            ; send character to UAER0
            BNE     Loop1_Tx            ; continue if not a '0'

; Free up the stack space if no longer needed
; ------------------------------------------------------------------------------------------------------
			; SUB 	sp, sp, #28    		; Restore the stack pointer of CharData

done        B       done                ; otherwise we're done

; Strcpy subroutine implements string copy
strcpy
			MOV		r3, r0				; Store starting address
strcpy_loop
			LDRB 	r4, [r1], #1   		; Load a character from the source string into r2 and increment r1
			STRB 	r4, [r0], #1   		; [return r0] Store the character at the destination address and increment r3
			CMP 	r4, #0          	; Check if it's the end of the string
			BNE 	strcpy_loop        	; If not the end, continue copying
			
			MOV		r1, r3				; [return r1] Return starting address
			BX		lr		          	; Return

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
; r5 – scratch
; r6 - scratch
; inputs: r0- byte to transmit
; outputs: none
;

Transmit
            STMIA   sp!, {r5, r6, lr}
            LDR     r5, =U0START
wait        LDRB 	r6, [r5, #LSR0]     ; get status of buffer
            CMP     r6, #0x20           ; buffer empty?
            BEQ     wait                ; spin until buffer’s empty
            STRB    r0, [r5]
            LDMDB   sp!, {r5, r6, pc}
CharData
            DCB     "TKU-ECE-411440521-JoshLee", 0
            END