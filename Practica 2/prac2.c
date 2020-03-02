extern void putchar( char dato );
extern char getchar( void );

void puts( char *str );
void gets(char *str);
void printdec(unsigned char dato );

unsigned int atoi(char *str);
void itoa(unsigned int num, char *str, unsigned char base);

void fecha(char *str);
unsigned int Zeller(unsigned int dias, unsigned int mes ,unsigned int anio);

unsigned int substr (char *str,unsigned ini,unsigned fin);

char msg[] = "Escribe: ";

char *MM[12] = {
    "Enero","Febrero","Marzo","Abril","Mayo","Junio",
    "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

int DM[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

char *Week[7] = {
    "Sabado", "Domingo", "Lunes",
    "Martes", "Miercoles", "Jueves", "Viernes"};

char Inicio[] = "Ingresa fecha en formato dd/mm//aaaa\r\n";
char salto[]="\r\n";

char Input[20];
char Input2[20];
char Anio[10];
char Dias[10];
char caux[20];

unsigned int numero;
 
unsigned char i=0;

int main ( void ){
    while(1){

        puts(Inicio);
        gets(Input);
        puts(Input);
        puts(salto);
        fecha(Input);
        getchar();
    }
return 0;
}

void puts ( char *str ){
    while( *str )
        putchar( *str++ );
}

void gets(char *str){
    char i = 0;
    unsigned char aux = 0;
    while ((aux = getchar()) != 13){
        if(aux == 8){
            if(i == 0){
                putchar(' ');
                putchar(8);
            }
            else{
                putchar(' ');
                putchar(8);
                str--;
                i--;
            }
        }
        else{
            if(i == 10){
                putchar(8);
                putchar(' ');
                putchar(8);
            }
            else{
                *str = aux;
                str++;
                i++;
            }
        }
    }
    *str = '\x0';
}

void printdec ( unsigned char dato ){ /*Imprime hasta 255*/
    putchar( dato/100 + 0x30 );
    dato%=100;
    putchar( dato/10 + 0x30 );
    putchar( dato%10 + 0x30 );
}

unsigned int atoi(char *str){
    int aux = 0;
    while((*str) && (*str >= '0' && *str <= '9')){
        aux*=10;
        (*str)-=48;
        aux+=(*str);
        str++;
    }
    return aux;
}

void itoa(unsigned int num, char *str, unsigned char base){
    unsigned char aux2 = 0;
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

void fecha(char *str){
    int B = 0;
    int D = 0;
    int A = 0;
    int dias,mes,anio;

    dias = substr(str,0,1);
    mes = substr(str,3,4);
    anio = substr(str,6,9);
    mes--;

    if(anio == 0){
        A = 1;
    }
    
    if (((anio % 4 == 0) && (anio % 100 != 0)) || (anio % 400 == 0)) {
        B = 1;
    }

    if( ((dias <= DM[mes]) && (dias != 0)) || (((mes == 1) && (B == 1)) && (dias <= 29))){
        D = 1;
    }

    if((A == 0) && (B == 1 || D == 1)){
        puts(Week[Zeller(dias,mes,anio)]);
        putchar(' ');
        itoa(dias, Dias,10);
        puts(Dias);
        puts(" de ");
        puts(MM[mes]);
        itoa(anio, Anio,10);
        puts(" del a/no ");
        puts(Anio);
    }
    else
    {
        puts("Fecha no Valida");
    }
}

unsigned int Zeller(unsigned int dias, unsigned int mes ,unsigned int anio){
    int a,q,m,k,j,h;
    q=dias;
    m=mes+1;
    a=anio;
    if (m == 1) { 
        m = 13; 
        a--; 
    } 
    if (m == 2) { 
    m = 14; 
    a--; 
    } 

    k=a%100;
    j=a/100;
    h= q + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
    h %= 7;
    return h;
}

unsigned int substr (char *str,unsigned ini,unsigned fin){
    unsigned int straux = 0;
    int i = 0,j=0;
    for(i = ini; i <= fin; i++){
        caux[j] = str[i];
        j++;
    }
    straux = atoi(caux);
    return straux;
}