extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
void puts(char *str);
extern void putchar(char dato);
extern char getchar( void );
void gets(char *str);
void printdec ( unsigned char dato );
void printHex(unsigned int dato);


void Datos(unsigned int segment, unsigned int offset);
void Direcciones(unsigned int segmento, unsigned int offset, unsigned char lines);

void veriDir(unsigned int segmento);

char msggood[] =" Bien\r\n";
char msgbad1[] =" Error\r\n";
char msgLin[]="Linea ";
char msgfatal[]="Fallo Catastrofico\r\n";
char msgBData[]="Bus de Datos\r\n";
char msgBDir[]="Bus de Direcciones\r\n";
char salto[]="\r\n";

unsigned int seg1 = 0xA00;
unsigned int seg2 = 0x800;

char lines = 11;

int main(void){
    while(1){
        
        puts("A000\r\n");

        Datos(seg1,0);
        Direcciones(seg1,0,lines);

        puts("A000\r\n");
        veriDir(seg1);

        puts("8000\r\n");
        veriDir(seg2);

    getchar();
    }
    return 0;
}

void Datos(unsigned int segment, unsigned int offset){
    unsigned char dato = 1,i=0;
    puts(msgBData);
    while(dato != 0){
        
        poke(segment,offset,dato);
        puts(msgLin);
        printdec(i+1);
        i++;

        if(peek(segment,offset) != dato){
            puts(msgbad1);
        }
        else{
            puts(msggood);
        }
        puts(salto);
        dato = dato << 1; 
    }
}

void Direcciones(unsigned int segmento, unsigned int offset, unsigned char lines){
    int dir,sucesss = 0;
    char patron = 0x55,i=0;

    puts(msgBDir);

    for(dir = 1; dir < (1 << lines); dir = dir << 1){
        poke(segmento,offset + dir,0);
    }

    poke(segmento,offset,patron);

    for(dir = 1; dir < (1 << lines); dir = dir << 1){
        for(){
            
        }
        
        if((peek(segmento,offset + dir) == patron) || peek(segmento,offset + dir) != 0 ){
            sucesss |= dir;
        }
    }
    while (i < lines) {
       puts(msgLin);
        printdec(i+1);
        if (sucesss & (1 << i)){
            puts(msgbad1);
        }       
        else{
            puts(msggood);
        }    
        puts(salto);
        i++;
        }
}

void veriDir(unsigned int segmento){
    unsigned int i = 0;
    char patron = 0x55;

    for(i = 0x7fb; i< 0x804; i++){
        poke(segmento,i,patron);
        printHex(i);

        if (peek(segmento,i) != patron)
        {
            puts(msgbad1);
        }
        else
        {
            puts(msggood);
        }
    }
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

void printHex(unsigned int dato) {
	
    int i, aux;
	for(i=12;i>=0;i=i-4){

		aux=(dato>>i) & 0xF;
        aux += (aux<10 ? 0x30: 0x37);
        putchar(aux);
	}
}
