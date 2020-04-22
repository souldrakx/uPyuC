.include "m2560def.inc"
.equ init_value = 0x80


next:
call t100us

call t1ms 

call t1seg

jmp next

t100us:;5
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
; 10 = Call/ret


t1ms: ;5

	ldi  r24, 205 ;1
   	
L2:	ldi  r25, 25 ;1
L1: 	
		dec  r25 ;n
    	brne L1  ;2(n-1) + 1
    dec  r24 ;m
    brne L2  ;2(m-1) + 1
ret;5
;n(3m+3)+10=16000 donde n = 25 y m = 205
;


t1seg:;5
	ldi r24, 241 ;1

L3:		ldi r25, 71 ;1

L4:			ldi r26, 186 ; 1    
L5:			nop ;z
			nop ;z
			dec r26 ;z 
			brne L5 ;2(z-1) + 1
		nop ;y
		nop ;y
		dec r25 ;y
		brne L4 ;2(y-1) + 1
	nop ;x
	nop ;x
	dec r24 ;x
	brne L3 ;2(x-1) + 1
ret;5

;5x + x*( 5y + y*(5z))+10 = 16000000 donde x = 241, y=71, z=186
;Ecu simplificada x (y (5 z + 5) + 5) + 10

