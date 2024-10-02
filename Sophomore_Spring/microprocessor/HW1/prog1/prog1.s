            AREA    UARTDEMO, CODE, READONLY
PINSEL0     EQU     0XE002C000          ; controls the function of the pins
U0START     EQU     0XE000C000          ; start of UART0 register
LCR0        EQU     0XC                 ; line control register for UART0
LSR0        EQU     0X14                ; line status register for UART0
RAMSTART    EQU     0X40000000          ; start of onboard RAM for 2104

RevData		EQU		0X40000022			; start of reversed character address
            ENTRY
start
            LDR     sp, =RAMSTART       ; set up stack pointer
            BL      UARTConfig          ; initialize/configure UART0

            LDR     r1, =CharData       ; starting address of characters
Loop1
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r0, #0              ; null terminated?
            BLNE    Transmit            ; send character to UAER0
            BNE     Loop1               ; continue if not a '0'

			LDR     r0, =CharData       ; load address of CharData into r0 (param 1 of ReverseString)
			LDR		r1, =RevData		; load address of RevData into r1  (param 2 of ReverseString)
			BL      ReverseString       ; reverse the string

			LDR		r1, =RevData		; Load address of RevData into r1
Loop2
            LDRB    r0, [r1], #1        ; load character, increment address
            CMP     r0, #0              ; null terminated?
            BLNE    Transmit            ; send character to UAER0
            BNE     Loop2               ; continue if not a '0'
done        B       done                ; otherwise we're done

; Subroutine ReverseString
; Reverses a null-terminated string.
; Registers used:
; r4, r5, r6, r7 - scratch registers
; inputs: r0 - pointer to the original string, r1 - pointer to the reversed string
; outputs: none
ReverseString
            STMIA   sp!, {r4-r7, lr}    ; Save register state

            MOV     r4, r0     			; [Param Used] Load address of the string into r4
			MOV		r6, #0				; String Length
str_len_loop
            LDRB    r5, [r4]			; Load a character from the string into r5
            CMP     r5, #0            	; Check if the end of the string '\0' is reached
            BEQ     rev_str            	; If reached, jump to string reverse part
			ADD     r4, r4, #1        	; Increment the string pointer
			ADD     r6, r6, #1        	; Increment character count
            B       str_len_loop        ; Continue looping until end of string

rev_str
            SUB     r4, r4, #1          ; Point to the end of the string (last character before '\0')
            MOV     r7, r6              ; r7 stores the string length
            MOV     r6, #0            	; r6 stores the reverse index
            MOV     r0, r1      		; [Param Used] Load address of the reversed string into r0
rev_str_loop
            LDRB    r5, [r4], #-1       ; Load character from the end of the string into r5 and decrement the storage position pointer
            STRB    r5, [r0], #1        ; Store loaded character back to the string at the increment position
            SUBS    r7, r7, #1          ; Decrement string length
            CMP     r7, r6              ; Check if the entire string has been reversed
            BGT     rev_str_loop        ; If not, continue looping

			MOV 	r5, #0           	; Load NULL character
			STRB 	r5, [r0]        	; Store NULL at the end of reversed string

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