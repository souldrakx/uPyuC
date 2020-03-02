extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
void puts(char *str);
extern void putchar(char dato);
extern char getchar( void );
void gets(char *str);
void printdec ( unsigned char dato );

unsigned char Datos(unsigned int segment, unsigned int offset);
unsigned char Direcciones(unsigned int segmento, unsigned int offset);

char msggood[] =" Bien\r\n";
char msgbad1[] =" Error\r\n";
char msgLin[]="Linea ";
char msgfatal[]="Fallo Catastrofico\r\n";
char msgBData[]="Bus de Datos\r\n";
char msgBDir[]="Bus de Direcciones\r\n";
char salto[]="\r\n";

unsigned int seg = 0x2200;

char Data = 0;
char Dir = 0;

int main(void){
    while(1){
        puts(msgBData);
        Data = Datos(seg,0);
        puts(msgBDir);
        Dir = Direcciones(seg,0);
        if((Data == 0) && (Dir == 0)){
            puts(msgfatal);
        }
    getchar();
    }

    return 0;
}

unsigned char Datos(unsigned int segment, unsigned int offset){
    unsigned char dato = 1, aux=0,e=0,i=0;
    
    while(dato != 0){
        
        poke(segment,offset,dato);
        aux = peek(segment,offset);
        printdec(i);
        i++;

        if(dato != aux){
            puts(msgbad1);
            puts(salto);
            e=1;
        }
        else{
            puts(msggood);
            puts(salto);
        }
        
        dato = dato << 1; 
    }

    if(e==1){
        return 0;
    }
    return 1;
}

unsigned char Direcciones(unsigned int segmento, unsigned int offset){
    unsigned char aux = 0;
    unsigned int dir = offset,i = 0,e=0;

    poke(segmento,dir,0);
    aux = peek(segmento,dir);
    puts(msgLin);
    printdec(i);
    i++;
    if (aux != 0){            
        puts(msgbad1);
        puts(salto);
        e=1;
    }
    else{
        puts(msggood);
        puts(salto);
    }

    dir++;

    while (dir != 0){
        poke(segmento,dir,0);
        aux = peek(segmento,dir);
        puts(msgLin);
        printdec(i);
        i++;
        if (aux != 0){            
            puts(msgbad1);
            puts(salto);
            e=1;
        }
        else{
            puts(msggood);
            puts(salto);
        }
        dir = dir << 1; 
    }
    if(e==1){
        return 0;
    }

    return 1;
}

void puts ( char *str ){
    while( *str )
        putchar( *str++ );
}

void gets(char *str){
    char i=0;
    unsigned char aux = 0;
        while((aux=getchar()) != 13){

        if(aux == 8){
            if(i==0){
                putchar(' ');
            }

            else{
                putchar(' ');
                putchar(8);
                str--;
                i--;
            }
        }
        else{
            if(i==25){
                putchar(8);
                putchar(' ');
                putchar(8); 
            }
            else{
                *str=aux;
                str++;
                i++;
            }
        }
    }
    *str='\x0';
}

void printdec ( unsigned char dato ){
    putchar( dato/100 + 0x30 );
    dato%=100;
    putchar( dato/10 + 0x30 );
    putchar( dato%10 + 0x30 );
}