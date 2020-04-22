#include "Timer.h"

void UpdateClock( void );
void DisplayClock( void );
void PrintDec2d( BYTE );
void Delay( BYTE );

void SetClock( BYTE, BYTE, BYTE);
void SetDate( WORD, BYTE, BYTE);

BYTE seg=55; /* para el manejo de los segundos */
BYTE min =59;
BYTE hr=23;

WORD a = 2020;
BYTE m = 1;
BYTE d = 29;

BYTE Cad[5];
/*BYTE Anio[10];*/

BYTE *MM[12] = {
    "enero","febrero","marzo","abril","mayo","junio",
    "julio","agosto","septiembre","octubre","noviembre","diciembre"
};

BYTE DM[12] = {31,28,31,30,31,30,31,31,30,31,30,31};


void main(){
    SetClock(hr,min,seg);
    SetDate(a,m,d),
    Timer_Ini(); /* inicialzaTimer de 1 segundo */
    while(1){
    /* Verificación para actualizar el reloj */
    if(TimerSecFlag() ){ /* Ha pasado un segundo? */
        UpdateClock(); /* actualiza y muestra el reloj */
        poke(0x0,0xFFFF,seg);/* indicar en puerto */
        DisplayClock(); /* desplegar reloj en 0,0 */
        
    }
                        /* otras cosas por hacer */
    Delay(100);
     /* Imprime */
    }
}

void UpdateClock( void ){
    seg++;
    if(seg == 60){
        seg=0;
        min++;
    }
    if(min == 60){
        min=0;
        hr++;
    }
    if(hr == 24){
        hr=0;
        d++;
    }
    if(d >= DM[m]+1){
        if(((m == 1) && (bisiesto(a) == 1)) && (d<=29  )  ){ /*si el año es biseisto incrementa un dia mas para febrero*/

        }
        else
        {
            d = 1;
            m++;
        }
    }   
    if(m == 12){
        m=0;
        a++;
    }
}

void DisplayClock( void ){
/* imprimir reloj en formato "hh:m:ss" */;
    
    PrintDec2d(d);
    putchar(' ');

    puts(MM[m]);
    putchar(' ');

    itoa(a,Cad,10);
    puts(Cad);
    putchar(' ');

    PrintDec2d(hr);
    putchar(':');

    PrintDec2d(min);
    putchar(':');

    PrintDec2d(seg);
    putchar('\r');
    putchar('\n');
}

void Delay( BYTE i){
    while(--i);
}

void SetClock( BYTE hora, BYTE minuto, BYTE segundos){ /*formato 24hr*/
    hr=hora;
    min= minuto;
    seg= segundos;
}

void SetDate(WORD year, BYTE month, BYTE day){
    a=year;
    m=month;
    d=day;
}

void PrintDec2d( BYTE dato){
    putchar( dato/10 +'0'); /* Imprime decenas */
    putchar( dato%10 +'0'); /* Imprime unidades */
}
/**
*Funciones Prac2
*/
void puts ( char *str ){
    while( *str )
        putchar( *str++ );
}

WORD atoi(char *str){
    int aux = 0;
    while((*str) && (*str >= '0' && *str <= '9')){
        aux*=10;
        (*str)-=48;
        aux+=(*str);
        str++;
    }
    return aux;
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

BYTE bisiesto(WORD anio){
    if (((anio % 4 == 0) && (anio % 100 != 0)) || (anio % 400 == 0)) {
        return 1;
    }
    return 0;
}



