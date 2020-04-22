extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
void puts(char *str);
extern void putchar(char dato);
extern char getchar( void );
void gets(char *str);
void printdec ( unsigned char dato );

unsigned char Datos(unsigned int, unsigned int);
unsigned char Direcciones(unsigned int, unsigned int, unsigned char);

char msggood[] =" Bien\r\n";
char msgbad1[] =" Error\r\n";
char msgLin[]="Linea ";
char msgfatal[]="Fallo Catastrofico\r\n";
char msgBData[]="Bus de Datos\r\n";
char msgBDir[]="Bus de Direcciones\r\n";
char salto[]="\r\n";

unsigned int seg = 0x280;

char lines = 12;
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
    unsigned char dato = 1,e=0,i=0,datgood = 0;
    puts(msgBData);

    for (dato = 1;dato;dato = dato << 1){
        poke(segment,0,dato);
        if(peek(segment,0) != dato){
            datgood |= dato;
        }
    }

    while (i < 8) {

        puts(msgLin);
        printdec(i+1);

        if (datgood & (1 << i)){
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

unsigned char Direcciones(unsigned int segmento, unsigned int offset, unsigned char lines){
    int dir, dir2,lingood = 0,i=0;
    char patron = 0xAA, antipatron = 0x55 ,e=0;

    puts(msgBDir);

    for(dir = 1; dir < (1 << lines); dir = dir << 1){
        poke(segmento,dir,0);
    }

    poke(segmento,offset,patron);

    for(dir = 1; dir < (1 << lines); dir = dir << 1){
        poke(segmento,offset,patron);
        if(peek(segmento,offset+dir) == patron){
            lingood |= dir;
        }
    }

    poke(segmento,offset,antipatron);

    for(dir = 1; dir < (1 << lines); dir = dir << 1){
        poke(segmento,offset,antipatron);
        if(peek(segmento,offset+dir) == antipatron){
            lingood |= dir;
        }
    }



    
    while (i < lines) {

        puts(msgLin);
        printdec(i);

        if (lingood & (1 << i)){
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
