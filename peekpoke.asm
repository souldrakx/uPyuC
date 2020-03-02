DOSSEG
.MODEL small
.CODE

PUBLIC _poke
PUBLIC _peek
PUBLIC _putchar
PUBLIC _getchar

	_poke proc
		push bp
		mov bp,sp
		push ds
		mov ax,[bp+4]
		mov ds,ax
		mov bx,[bp+6]
		mov dl,[bp+8]
		mov byte ptr[bx],dl
		pop ds
		pop bp
		ret
	endp
	
	_peek proc
		push bp
		mov bp,sp
		push ds
		mov ax,[bp+4]
		mov ds,ax
		mov bx,[bp+6]
		mov al, byte ptr[bx]
		mov ah,0
		pop ds
		pop bp
	ret
	endp

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
		mov ah,1
		int 21h
			   
		pop bp
		ret
			   		
	_getchar ENDP
end