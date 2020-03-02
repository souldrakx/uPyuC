   
.model tiny
   locals
   
.data
	flecha DB ' -> ',0

.code
	org 100h
	
principal proc
    mov sp,0fffh			; inicializa SP (Stack Pointer)
									
			
    mov ax,8000h
	;mov ax,120
	;mov ax,-12
	;mov ax,12345
	call printNumBase

	mov dx,offset flecha
	call puts
	
	xor dx,dx

	call Inver
	mov ax,dx
	call printNumBase



	@@sigue:
	jmp @@sigue
			
	ret						; nunca se llega aqui
endp

;Procedimientos

putchar	proc
	push ax
	push dx
	mov dl,al
	mov ah,2				; imprimir caracter DL
	int 21h					; usando servico 2 (ah=2)
	pop dx					; del int 21h
	pop ax
	ret
endp

puts	proc
	push ax
	push bx
			
	mov  bx,dx
	@@nxt: 
	mov  al,[bx]
	cmp  al,0
	je   @@end
	call putchar
	inc  bx
	jmp  @@nxt
			
	@@end: 
	pop  bx
	pop  ax
	ret
endp

printNumBase PROC ;Guandar en AX
	push ax

	call negar

    mov bx,10
    mov cx,0 
    @@nxt:	
    mov dx,0 
	div bx  
	push dx 
	inc cx
	cmp ax,0
	jne @@nxt

	cmp bp,1
	jne @@verif
	mov al,2Dh
	call putchar
	xor ax,ax

    @@verif:
    pop ax
	cmp ax,10 
	jb @@less
	add ax,7
		
    @@less: 
    add ax,30h

    mov ah,02h
    mov dx,ax
    int 21h 
	loop @@verif

	pop ax
    ret
ENDP

Inver proc
	push ax
	push cx
	push si
	push di

	mov bx,10
	xor cx,cx
	xor si,si

	call negar

	@@inv:
	mov dx,0
	div bx
	mov [si],dx
	add si,2
	inc cx
	cmp ax,0
	jne @@inv

	xor si,si

	@@inv2:
	mov di,[si]
	add ax,di
	cmp cx,1
	je @@finv
	mul bx
	jo @@over
	@@finv:
	add si,2
	loop @@inv2

	cmp ax,7fffh
	ja @@over

	mov dx,ax
	jmp @@fin

	@@over:
	mov dx,0
	mov bp,0
	
	@@fin:

	pop di
	pop si
	pop cx
	pop ax
	ret
endp

negar proc
	cmp ax,8000h
	jb @@fneg
	not ax
	inc ax
	mov bp,1
	@@fneg:
	ret
endp


end   principal              ; End of program 
