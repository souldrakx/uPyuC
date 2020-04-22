#define BYTE unsigned char
#define WORD unsigned int

#define INTR 8 /* Utilizar el vector adecuado */



BYTE TimerSecFlag( void );
void Timer_Ini( void );

extern void poke(WORD segment, WORD offset, BYTE data);
extern BYTE peek(WORD segment, WORD offset);
extern void pokew(WORD segment, WORD offset, WORD data);
extern void putchar(char dato);
extern char getchar( void );


void puts( char *str );
unsigned int atoi(char *str);
void itoa(unsigned int num, char *str, unsigned char base);

BYTE bisiesto(WORD anio);
