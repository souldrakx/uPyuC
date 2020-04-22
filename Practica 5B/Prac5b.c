#define BYTE unsigned char
#define WORD unsigned int

#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43

#define PTOs_all_out 0x80
#define PTOs_all_in 0x88

#define PTOs_PA_y_PB_out 0x89
#define PTOs_PB_y_PC_out 0x98
#define PTOs_PA_y_PC_out 0x8A

extern void outportb(WORD port, BYTE dato);
extern BYTE inportb(WORD port);
extern void putchar( char dato );
extern char getchar( void );

void printBin( BYTE dato );

void Leds( BYTE bits);/*Funcion que determina que leds van a encender*/

void setclrbit(WORD A, WORD B);/*Funcion que activa un bit de un puerto y desactiva un bit un puerto*/

void delay(BYTE i);

void puts ( char *str );
void itoa(unsigned int num, char *str, unsigned char base);

void SetBitPort(WORD Puerto, BYTE num_bit);
void ClrBitPort( WORD Puerto, BYTE num_bit );
void NotBitPort( WORD Puerto, BYTE num_bit );
BYTE TstBitPort ( WORD Puerto, BYTE num_bit );
void ReverseBitsPort ( WORD Puerto );

char dato;
char Cad[8];

BYTE i = 0, aux = 0, bits = 0;

void main( void ){
    
    puts("Practica 5b\n\r"); /* imprimir mensaje */
    outportb( RCtr, PTOs_all_in ); /* inicializar 8255 */
    /*Ciclo que lee el puerto PC y conocer el valor del numero en binario*/
    for( i = 0; i < 8; i++ ){
        getchar();
        aux = (TstBitPort( PC , 4 ));/*Lee el puerto P4 bit 4 y guarda el dato en una variable auxiliar*/
        putchar(aux + '0');/*Imprime el valor capturado*/
        aux = aux << i;
        bits |= aux;  /*Seguarda el dato capturado en una variable la cual determinara que led encender*/
    }

    while(1){
       Leds(bits); 
    }
}

/* función para lectura de puertos usando ensamblador in-line */

/* función simple para desplegar un byte en formato binario */
void printBin( BYTE dato ){
 BYTE msk=0x80;
 do{
 putchar( (dato & msk) ? '1' : '0' );
 msk>>=1;
 }while( msk );
}

/*Funciones*/
/*Funcion que enciende los led de forma inverza a la captura y muestra los 6 datos menos significativos*/
void Leds( BYTE bits ){
    BYTE aux, b = 0;/*b = led a encender*/

    while(1){
        aux = bits & (1 << b); /*Si un dato en binario es 1 entra al ciclo y lo enciende*/
        /*La funcion recorrera cada bit del dato ingresado
        Este determinara por que puertos debe salir*/
        if(aux){
            if( (b == 5) || (b == 4) ){/*Los bits 4 y 5 saldran por los puestos PA y PB*/
                outportb(RCtr,PTOs_PA_y_PB_out);
                if(b == 5){
                    setclrbit(PB,PA);
                }
                else{
                    setclrbit(PA,PB);
                }
            }
            else if(  (b == 2) || (b == 3)  ){/*Los bits 2 y 3 saldran por los puestos PB y PC*/
                outportb(RCtr,PTOs_PB_y_PC_out);
                if(b == 3){
                    setclrbit(PC,PB);
                }
                else{
                    setclrbit(PB,PC);
                }
            }
            else{                               /*Los bits 0 y 1 saldran por los puestos PA y PC*/
                outportb(RCtr, PTOs_PA_y_PC_out);
                if(b == 1){
                    setclrbit(PA,PC);
                }
                else{
                    setclrbit(PC,PA);
                }
            }
            delay(10);
        }
        
        if(b == 6){
            b=0;
        }
        else{
            b++;
        }
    }   
}



void setclrbit(WORD PtA, WORD PtB){
    SetBitPort(PtA,1);
    ClrBitPort(PtB,1);
}

void delay(BYTE i){
    while(i--);
}


void puts ( char *str ){
    while( *str )
        putchar( *str++ );
}

void itoa(WORD num, char *str, BYTE base){
    BYTE aux2 = 0;
    char i = 0, j = 0;

    if(num == 0){
        aux2 += 48;
        str[i++] = aux2;
        str[i] = aux2;
        str[i] = '\x0';
    }

    while (num > 0){
        aux2 = num % base;
        if(aux2 > 9){
            aux2 += 7;
        }
        aux2 += 48;
        str[i++] = aux2;
        num /= base;
        str[i] = '\x0';
    }

    i--;
    while (i > j){
        aux2 = str[j];
        str[j] = str[i];
        str[i] = aux2;
        j++;
        i--;
    }
}

void SetBitPort(WORD Puerto, BYTE num_bit){/*Activa un bit de un puerto*/
    outportb( Puerto , inportb( Puerto )|( 0x01 << num_bit ) );
}

void ClrBitPort( WORD Puerto, BYTE num_bit ){/*Desactiva un bit de un puerto*/
    outportb( Puerto, inportb( Puerto ) & ~( 0x01 << num_bit ) );
}
void NotBitPort( WORD Puerto, BYTE num_bit ){/*Niega un bit de un puerto*/
    outportb( Puerto, inportb( Puerto ) ^ ( 0x01 << num_bit ) );
}
BYTE TstBitPort ( WORD Puerto, BYTE num_bit ){/*Verifica si un bit de un puerto es 0 o 1*/
    if ( ( ( inportb(Puerto) ) & (0x01 << num_bit)  ) == 0 ){
        return 0;
    }	
	return 1;
}
void ReverseBitsPort ( WORD Puerto ){/*Invierte el valor de un puerto Eje 10101111 = 11110101*/
    BYTE FLDSMDFR = 0 , i = 1, j = 0, aux = 0;
    aux = inportb( Puerto );
    
    for(i = 0;i < 8 ; i++){
        if(aux & j){
            FLDSMDFR |= 1;
        }
        else{
            FLDSMDFR |= 0;
        }
        j <<= 1;
        FLDSMDFR <<= 1;
    }
    outportb( Puerto, FLDSMDFR );
}


