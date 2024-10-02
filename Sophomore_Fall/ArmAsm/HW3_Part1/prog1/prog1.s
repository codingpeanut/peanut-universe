        AREA 	HAMMING, CODE
        ENTRY
        
        ; Registers used:
        ; r0 is current data
        ; r1 is current ldr address
        ; r2 is value to be transmitted
        ; r4 is temp
        ; r5 is current str address
        
        MOV 	r4, #0
        ADR 	r1, arraya          ; current ldr address
        LDR 	r5, =0x40000000		; current str address
        
		; 411440521 JoshLee
loop	CMP 	r5, #0x40000006
        LDRB 	r0, [r1]            ; current data
		
		;---------- calculate c0 ----------; 411440521 JoshLee
        MOV 	r4, r0
        EOR 	r4, r4, r0, ROR #1	; 1 XOR 0
        EOR 	r4, r4, r0, ROR #3	; 3 XOR 1 XOR 0
        EOR 	r4, r4, r0, ROR #4	; 4 XOR 3 XOR 1 XOR 0
        EOR 	r4, r4, r0, ROR #6	; 6 XOR 4 XOR 3 XOR 1 XOR 0
        AND 	r2, r4, #1
        
		;---------- calculate c1 ----------; 411440521 JoshLee
        MOV 	r4, r0
        EOR 	r4, r4, r0, ROR #2	; 2 XOR 0
        EOR 	r4, r4, r0, ROR #3	; 3 XOR 2 XOR 0
        EOR 	r4, r4, r0, ROR #5	; 5 XOR 3 XOR 2 XOR 0
        EOR 	r4, r4, r0, ROR #6	; 6 XOR 5 XOR 3 XOR 2 XOR 0
        AND 	r4, r4, #1
        ORR 	r2, r2, r4, LSL #1
		
		;---------- calculate c2 ----------; 411440521 JoshLee
        ROR 	r4, r0, #1			; get bit 1
        EOR 	r4, r4, r0, ROR #2	; 2 XOR 1
        EOR 	r4, r4, r0, ROR #3	; 3 XOR 2 XOR 1
        EOR 	r4, r4, r0, ROR #7	; 7 XOR 3 XOR 2 XOR 1
        AND 	r4, r4, #1
        ORR 	r2, r2, r4, ROR #29
        
		;---------- calculate c3 ----------; 411440521 JoshLee
        ROR 	r4, r0, #4			; get bit 4
        EOR 	r4, r4, r0, ROR #5	; 5 XOR 4
        EOR 	r4, r4, r0, ROR #6	; 6 XOR 5 XOR 4
        EOR 	r4, r4, r0, ROR #7	; 7 XOR 6 XOR 5 XOR 4
        AND 	r4, r4, #1
        
		;---------- compose data ----------; 411440521 JoshLee
        ORR 	r2, r2, r4, ROR #25
        AND 	r4, r0, #1
        ORR 	r2, r2, r4, LSL #2
        BIC 	r4, r0, #0xF1
        ORR 	r2, r2, r4, LSL #3
        BIC 	r4, r0, #0x0F
        ORR 	r2, r2, r4, LSL #4
        
        STRH 	r2, [r5]           	; store transmitted value
        
		; update current data address
        ADD 	r1, #1             	; shift to new data
        ADD 	r5, #2             	; shift two bytes for next 12bits
		
        BNE 	loop
        
done    B    	done
        ALIGN
arraya	
        DCB 	0xB5
        DCB 	0xAA
        DCB 	0x55
        DCB 	0xAA
        
        END