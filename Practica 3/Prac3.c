extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
void puts(char *str);
extern void putchar(char dato);
extern char getchar( void );
void gets(char *str);
void printdec ( unsigned char dato );

unsigned char Datos(unsigned int segment, unsigned int offset);
unsigned char Direcciones(unsigned int segmento, unsigned int offset, unsigned char lines);

char msggood[] =" Bien\r\n";
char msgbad1[] =" Error\r\n";
char msgLin[]="Linea ";
char msgfatal[]="Fallo Catastrofico\r\n";
char msgBData[]="Bus de Datos\r\n";
char msgBDir[]="Bus de Direcciones\r\n";
char salto[]="\r\n";

unsigned int seg = 0x220;

char lines = 11;
char Data,Dir;

int main(void){
    while(1){
        Data = Datos(seg,0);
        Dir = Direcciones(seg,0,lines);
        if((Data) && (Dir)){
            puts(msgfatal);
        }
    getchar();
    }
    return 0;
}

unsigned char Datos(unsigned int segment, unsigned int offset){
    unsigned char dato = 1,e=0,i=0;
    puts(msgBData);
    while(dato != 0){
        
        poke(segment,offset,dato);
        puts(msgLin);
        printdec(i+1);
        i++;

        if(peek(segment,offset) != dato){
            puts(msgbad1);
            e=1;
        }
        else{
            puts(msggood);
        }
        puts(salto);
        dato = dato << 1; 
    }
    return e;
}

unsigned char Direcciones(unsigned int segmento, unsigned int offset, unsigned char lines){
    int dir,sucesss = 0,i=0;
    char patron = 0xaa, e=0;

    puts(msgBDir);

    for(dir = 1; dir < (1 << lines); dir = dir << 1){
        poke(segmento,dir,0);
    }

    poke(segmento,offset,patron);

    for(dir = 1; dir < (1 << lines); dir = dir << 1){
        if((peek(segmento,dir) == patron) || peek(segmento,dir) != 0 ){
            sucesss |= dir;
        }
    }
    while (i < lines) {

                puts(msgLin);
                printdec(i+1);
                if (sucesss & (1 << i)){
                    puts(msgbad1);
                    e=1;
                }       
                else{
                    puts(msggood);
                }    
                puts(salto);
                i++;
        }
    return e;
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
