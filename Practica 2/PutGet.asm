dosseg
.model small
.code

	public _putchar
	public _getchar
	
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

END