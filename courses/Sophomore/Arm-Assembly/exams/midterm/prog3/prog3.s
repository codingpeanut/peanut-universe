		AREA 	prog3, CODE ,READONLY
		ENTRY
		
		; r0 is data address
		; r1 is data
		; r2 is one bit of data
		; r3 is the amount of data
		
		; 411440521 JoshLee
		;----------------------------------;3.(1)
		; Point out each stored value from the memory window 
		; and write down the address of each variable (data1~data5).
		ADR		r1, data1
		
		
		; 411440521 JoshLee
		;----------------------------------;3.(2)
		; Store data1 into memory started from address 0x40000000.
		ADR		r1, data1
		LDR		r0, =0x40000000
		
loop2   LDRB	r2, [r1], #1
		CMP		r2, #0
		STRBNE	r2, [r0], #1
		BNE		loop2
		
		
		; 411440521 JoshLee
		;----------------------------------;3.(3) 
		; Reverse the string in data1 and put the reversed string 
		; in the memory started at address 0x40000030.
		ADR		r1, data1
		LDR		r0, =0x40000030
		ADD		r0, #25				; pointer points the last bit of data1
loop3   LDRB	r2, [r1], #1
		CMP		r2, #0
		STRBNE	r2, [r0], #-1
		BNE		loop3
		
		
		; 411440521 JoshLee
		;---------------------------------;3.(4)
		; Store data2 into memory started from address 0x40000060.
		ADR		r1, data2
		LDR		r0, =0x40000060
		LDR		r3, =4
		
loop4   LDRH	r2, [r1], #2
		STRH	r2, [r0], #2
		SUB		r3, #1
		CMP		r3, #0
		BNE		loop4
		
		
		; 411440521 JoshLee
		;---------------------------------;3.(5)
		; Store data3 into memory started from address 0x40000070.
		ADR		r1, data3
		LDR		r0, =0x40000070
		LDR		r3, =6
		
loop5   LDR		r2, [r1], #4
		STR		r2, [r0], #4
		SUB		r3, #1
		CMP		r3, #0
		BNE		loop5
		
		
		
		; 411440521 JoshLee
		;---------------------------------;3.(6)
		; Reverse data3 and put the reversed data3 
		; in the memory started from address 0x40000090.
		ADR		r1, data3
		LDR		r0, =0x40000090
		ADD		r0, #20
		LDR		r3, =6

loop6   LDR		r2, [r1], #4
		STR		r2, [r0], #-4
		SUB		r3, #1
		CMP		r3, #0
		BNE		loop6
		
		
		
		; 411440521 JoshLee
		;---------------------------------;3.(7)
		; Store the string data4 into memory started 
		; from address 0x400000B0.
		ADR		r1, data4
		LDR		r0, =0x400000B0
		LDR		r3, =7
 
loop7   LDRB	r2, [r1], #1
		STRB	r2, [r0], #1
		SUB		r3, #1
		CMP		r3, #0
		BNE		loop7
		
		
		; 411440521 JoshLee
		;---------------------------------;3.(8)
		; Store data5 into memory started from address 0x400000C0.
		ADR		r1, data5
		LDR		r0, =0x400000C0
		LDR		r3, =6

loop8   LDR		r2, [r1], #4
		STR		r2, [r0], #4
		SUB		r3, #1
		CMP		r3, #0
		BNE		loop8
		
		
		; 411440521 JoshLee
		;---------------------------------;3.(9)
		; Add the 6 words in data5 and put the sum in the word at 
		; memory address 0x400000E0.
		ADR		r1, data5
		LDR		r0, =0x400000E0
		LDR		r3, =6
		LDR		r7, =0				; sum
		
loop9   LDR		r2, [r1], #4
        ADD		r7, r2
		SUB		r3, #1
		CMP		r3, #0
		BNE		loop9
		STR		r7, [r0]
		
		
stop	B		stop
		
data1   DCB   "Midterm Exam in Fall 2023!", 0
data2   DCW   0x1234, 0x5678, 0xBEEF, 0xFACE
data3   DCD   0x8ECC, 0xFE37, 0xABCD, 1, 5, 0x1234FACE
data4   DCB   0xCF, 23, 39, 0x54, 250, 0xFF, 0xAD
data5   DCD   0xFE37, 1, 5, 20, 0xABCDFACE, 0x12345678

		END