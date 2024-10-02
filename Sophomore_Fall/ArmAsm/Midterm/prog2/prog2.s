		AREA	prog2, CODE, READONLY
		ENTRY
		
		; 411440521 JoshLee
		;--------------------------------------;2.(1)
		; Compute j = (2n + 2m - 2p) - 48 and put j in r5, 
		; assuming n = 7, m = 6 and p = 5 are respectively 
		; in r2, r3 and r4 initially.
		MOV		r2, #7				; n=7
		MOV		r3, #6				; m=6
		MOV		r4, #5				; p=5
		LDR		r0, =1				; 2^1
		ADD		r5, r0, LSL r2		; 2^n
		ADD		r5, r0, LSL r3		; 2^n+2^m
		SUB		r5, r0, LSL r4		; 2^n+2^m-2^p
		SUB		r5, #48				; (2^n+2^m-2^p)-48
		
		; r3 is reference adress (0x40000000)
		; r4 is test number
		; r5 is the answer
		; r6 is data length
		; r7 is data
		; r10 is temp adress
		; r11 is temp data
		
		; 411440521 JoshLee
		;--------------------------------------;2.(2)
		LDR		r10, =0x40000010
		LDR		r11, =0xDEADABCD
		STR		r11, [r10]

		LDR		r10, =0x40000020
		LDR		r11, =0xABCD8765
		STR		r11, [r10]

		LDR		r10, =0x40000030
		LDR		r11, =0xBEEFFACE
		STR		r11, [r10]
		LDR		r3, =0x40000000
		
		
		; 411440521 JoshLee
		;--------------------------------------;2.(2)(a)
		; the number of ones (using TST) in the word at address 0x40000010.
		LDR		r4, =1
		LDR		r5, =0
		LDR		r6, =32
		LDR		r7, [r3, #0x10]
   
loopa	TST		r7, r4
		ADDNE	r5, #1
		LSL		r4, #1
		SUB		r6, #1
		CMP		r6, #0
		BNE		loopa
		STR		r5, [r3, #0x40]
		
		
		; 411440521 JoshLee
		;--------------------------------------;2.(2)(b)
		; the number of ones (using AND) in the word at address 0x40000020.
		LDR		r4, =1
		LDR		r5, =0
		LDR		r6, =32
		LDR		r7, [r3, #0x20]

loopb   AND		r8, r7, r4
		CMP		r8, #1
		ADDEQ	r5, #1
		LSR		r7, #1
		SUB		r6, #1
		CMP		r6, #0
		BNE		loopb
		STR		r5, [r3, #0x44]
		
		
		; 411440521 JoshLee
		;--------------------------------------;2.(2)(c)
		; the number of zeros (using TST and without using SUB) in 
		; the word ataddress 0x40000030.
		LDR		r4, =1
		LDR		r5, =0
		LDR		r6, =0
		LDR		r7, [r3, #0x30]
   
loopc   TST		r7, r4
		ADDEQ	r5, #1
		LSL		r4, #1
		ADD		r6, #1
		CMP		r6, #32
		BNE		loopc
		STR		r5, [r3, #0x48]
		
		
		; 411440521 JoshLee
		;--------------------------------------;2.(2)(d)
		; the number of different bits between the 2 words at 
		; addresses 0x40000020 and 0x40000030
		LDR		r4, =1
		LDR		r5, =0
		LDR		r6, =32
		LDR		r7, [r3, #0x20]
		LDR		r8, [r3, #0x30]
		EOR		r9, r7, r8
		
loopd   TST		r9, r4
		ADDNE	r5, #1
		LSL		r4, #1
		SUB		r6, #1
		CMP		r6, #0
		BNE		loopd
		STR		r5, [r3, #0x4C]

stop    B     	stop
		END