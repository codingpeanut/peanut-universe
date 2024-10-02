		AREA  	prog1, CODE, READONLY
		ENTRY
		
		; r0 is source/answer memory address
		; r1 is source data
		; r2 is temp data
		; r4 is mask
		; r9 is the answer
		
		; 411440521 JoshLee
		;--------------------------------------;
		; Assume a 32-bit word at memory address 0x40000000 contains 0xBEEFFACE.
		LDR		r0, =0x40000000
		LDR		r1, =0xBEEFFACE
		STR		r1, [r0]
		
		
		; 411440521 JoshLee
		;--------------------------------------;1.(1)
		; insert the value 0x8765 into the word so that 
		; the final value is 0xB8765ACE
		LDR		r9, [r0]
		LDR		r2, =0x8765
		LDR		r4, =0x0FFFF000
		BIC		r9, r4
		ORR		r9, r2, LSL #12
		STR		r9, [r0]
		
		
		; 411440521 JoshLee
		;--------------------------------------;1.(2)
		; set bits 5, 9, 13 and 17 of the word and 
		; leave the remaining bits unchanged
		LDR		r0, =0x40000000
		LDR		r1, =0xBEEFFACE
		STR		r1, [r0]
		LDR		r9, [r0]
		LDR		r4, =0x22220		;0b0010 0010 0010 0010 0000
		ORR		r9, r4
		STR		r9, [r0]
		
		
		; 411440521 JoshLee
		;--------------------------------------;1.(3)
		; use one way to clear bits 7, 10, and 16 of the word 
		; and leave the remainingbits unchanged,
		LDR		r0, =0x40000000
		LDR		r1, =0xBEEFFACE
		STR		r1, [r0]
		LDR		r9, [r0]
		LDR		r4, =0x10480		;0b0001 0000 0100 1000 0000
		BIC		r9, r4
		STR		r9, [r0]
		
		
		; 411440521 JoshLee
		;--------------------------------------;1.(4)
		; use another way to clear bits 7, 10, and 16 of the word and 
		; leave the remaining bits unchanged
		LDR		r0, =0x40000000
		LDR		r1, =0xBEEFFACE
		STR		r1, [r0]
		LDR		r9, [r0]
		LDR		r4, =0x10480		;0b0001 0000 0100 1000 0000
		LDR		r2, =0xFFFFFFFF
		EOR		r4, r2
		AND		r9, r4
		STR		r9, [r0]
		
		
		; 411440521 JoshLee
		;---------------------------------------;1.(5)
		; change bits 18, 25, and 26 of the word and 
		; leave the remaining bitsunchanged
		LDR		r0,	=0x40000000
		LDR		r1, =0xBEEFFACE
		STR		r1, [r0]
		LDR		r9, [r0]
		LDR		r4, =0x06040000		;0b0110 0000 0100 0000 0000 0000 0000
		EOR		r9, r4
		STR		r9, [r0]
		
		
stop    B     stop
		END