;------------- definiciones e includes ------------------------------
.include "m2560def.inc"
.equ init_value = 0x80

;------------- init PORTS -------------------------------------------
ldi R24,INIT_VALUE
out DDRB,R24

;------------- main loop -------------------------------------------
next:
call t103us

call t100ms 

call t1seg

out PINB,R24
rjmp next

t103us:;5
	ldi r24,159 ;1

nxt:nop			;n
	nop			;n
	nop			;n
	nop			;n
	nop			;n
	nop			;n
	nop			;n
	dec r24		;n
	brne nxt	;2(n-1) + 1
ret ;5
;10n+10 = 1600 ciclos donde n = 159
;10(159)+10 = 1590+10=1600 ciclos
; 10 = Call/ret


t100ms: ;5

	ldi  r24, 133 ;1
   	
L1:	ldi  r25, 65 ;1
		
L2:		ldi  r26, 45 ;1
 	
L3:			nop	;z
			dec  r26; z
			brne L3; (2z-1) + 1
		nop ;y
		nop ;y
		dec  r25 ;y
    	brne L2  ;2(y-1) + 1
	nop	;x
	nop	;x
    dec  r24 ;x
    brne L1  ;2(x-1) + 1
ret;5
;
;3x + 2(x-1) +1 +1 + x(3y +2(2y-1) +1 +1 +y(2z +2(z-1) +1 +1)) +10 = 1 600 000 ciclos
;3x + 2(x-1) +1 +1 + x(3y +2(2y-1) +1 +1 +y(2z +2z +2 -2)) +10 = 1 600 000 ciclos se eliminan las sumas de z
;3x + 2(x-1) +1 +1 + x(3y +2(2y-1) +1 +1 +y(4z) +10 = 1 600 000 ciclos
;3x + 2(x-1) +1 +1 + x(5y +y(4z)) +10 = 1 600 000 ciclos simplificando y
;5x + x(5y +y(4z)) +10 = 1 600 000 ciclos simplificando x
;x* (y* (4z +5) +5) +10 = 1 600 000 ciclos simplificando ecuacion donde x = 133, y = 65, z = 45
;133*(65*((4*45)+5) +5) +10 =1 600 000 cilcos
; 10 = Call/ret


t1seg:;5
	ldi r24, 241 ;1

L4:		ldi r25, 71 ;1

L5:			ldi r26, 186 ; 1    
L6:			nop ;z
			nop ;z
			dec r26 ;z 
			brne L6 ;2(z-1) + 1
		nop ;y
		nop ;y
		dec r25 ;y
		brne L5 ;2(y-1) + 1
	nop ;x
	nop ;x
	dec r24 ;x
	brne L4 ;2(x-1) + 1
ret;5

;5x + x*( 5y + y*(5z))+10 = 16 000 000 donde x = 241, y=71, z=186
;Ecu simplificada x (y (5 z + 5) + 5) + 10
;241*(71*((5*186) +5) +5) +10 =1 600 000 cilcos
;10 = Call/ret

;------------- definiciones e includes ------------------------------
.INCLUDE "m1280def.inc"
.equ INIT_VALUE = 0x80

;------------- init PORTS -------------------------------------------
ldi R24,INIT_VALUE
out DDRB,R24
;------------- main loop -------------------------------------------
next:
 ;**** Llamar Retardo ****
out PINB,R24
rjmp next