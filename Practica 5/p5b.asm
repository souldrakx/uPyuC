DOSSEG
.MODEL small
.CODE


PUBLIC _putchar
PUBLIC _getchar
PUBLIC _outportb
PUBLIC _inportb

	_putchar  PROC
		push bp
		mov bp,sp
						
		mov dl,[bp+4]
		mov ah,2
		int 21h
						
		pop bp
		ret
						
	_putchar ENDP
	
	
	_getchar   PROC
		push bp
		mov bp,sp
			   
		mov dl,[bp+4]			   
		mov ah,8
		int 21h
			   
		pop bp
		ret
			   		
	_getchar ENDP

    _outportb PROC
        push bp
        mov bp,sp

        mov dx,[bp+4]   
        mov al,[bp+6]   
        out dx,al

        pop bp
        ret
    _outportb ENDP

    _inportb PROC
        push bp
        mov bp,sp

        mov dx,[bp+4]   
        in al,dx

        pop bp
        ret
    _inportb ENDP
end