			AREA 	LED1, CODE, READONLY
			ENTRY
			
			
			; Set the direction using GPIODIR (page 661)
			; Base is 0x40025000
			LDR		r0, = 0x40000000
			SUB 	r7, r7, r7				 ; clear out r7


			LDR 	r6, =0x100				 ; start with LED = 0b 0001 0000 0000 (PF8, red)
mainloop1	; red -> green -> blue
			; turn on the LED
			; if bits [9:2] affect the writes, then the address
			; is offset by 0x38
			STR 	r6, [r0, #0x38] 		 ; base + 0x38 so [9:2] = 0b00111000
			BL		DELAY


			; change colors until green
			CMP 	r6, #0x1				 ; if LED == 0b 0000 0000 0001 (PF0, green) -> switch to loop2
			BLE	 	mainloop2				 ; reset to 2 otherwise
			LSRGT 	r6, r6, #4 				 ; LED = LED * 2
			B 		mainloop1


mainloop2	; blue -> green -> red
			; turn on the LED
			; if bits [9:2] affect the writes, then the address
			; is offset by 0x38
			STR 	r6, [r0, #0x38]			 ; base + 0x38 so [9:2] = 0b00111000
			BL		DELAY


			; change colors until red
			CMP 	r6, #0x100				 ; reset with LED = 0b 0001 0000 0000 (PF8, red) -> switch back to loop1
			BGE		mainloop1				 ; reset to 2 otherwise
			LSLLT 	r6, r6, #4 				 ; LED = LED * 2
			B 		mainloop2


DELAY		
			LDR 	r7, =0x8AB75D			 ; set delay = 25 seconds = 25 * 15MHz = 0x8AB75D, set counter to 0x8AB75D
spin
			SUBS 	r7, r7, #1
			BNE 	spin					 ; run until r7 = 0
			BX		LR


stop		B		stop
			END