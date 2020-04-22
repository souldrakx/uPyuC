.include "m2560def.inc"
.equ init_value = 0x80

ldi R21,178	/*nrand*/
next:
ldi R16,0    /*inicial*/
ldi R17,255	 /*final*/

call rand

out PINB,R18

rjmp next



rand:

ldi R22,58	/*nrand2*/

cp R17,R16	/*Checa que sea valido*/
breq fin

add R21,R22 /*nrand+=nrand2*/


/*nrand %= R17
nrand-r17*(nrand/r17)*/
call div /* divisor =r17 ,dividendo =r21 */

mul r17,r23
sub r21,r17
 

while:
cp r21,r16
brsh fin1
add r21,r17
sub r21,r16
cp r21,r16
jmp while

fin1:
mov r16,r21
fin:
mov R18,R16

ret



div:
push r17
push r21
ldi r23,0

cp r17,r21
breq find

divs:
inc r23
sub r17,r21
cp r17,r21
brlt divs

find:
pop r21
pop r17
ret /*resultado en r23*/
