#include <stdio.h>
#include <conio.h>

unsigned short lfsr = 0xACE1u;
  unsigned bit;
/*
  unsigned int rand( unsigned int start, unsigned int end )
{   
    if(start == end) return start;
    bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
    lfsr =  (lfsr >> 1) | (bit << 15) % end;
    while(lfsr<start){
        lfsr = lfsr + end - start;
    }
    return lfsr;
  
}*/

unsigned int MyRand(unsigned int start_range,unsigned int end_range)
  {
    static unsigned int rand = 0xACE1U; /* Any nonzero start state will work. */

    /*check for valid range.*/
    if(start_range == end_range) {
        return start_range;
    }

    /*get the random in end-range.*/
    rand += 236;
    rand %= end_range;

    /*get the random in start-range.*/
    while(rand < start_range){
        rand = rand + end_range - start_range;
    }

    return rand;
  }

int main(){/*
    int b = 0, res = 0,i,j,z;


    for(i = 0;i < 150; i++){
        for(j = 0; j < 70; j++){
            for(z = 0; z < 50; z++){
                res = i * ( j * ( ( 4 * z ) + 5) + 5 ) + 10;
            
                if(res == 1600000){
                printf("%d,%d,%d",i,j,z);
                b = 1;
                }
                /res = 0;
            }
        }    
    }

    if(b==0){
        printf("no esncontrado %d",res);
    }*/
    int i;
    for(i = 0;i<100;i++){
    printf("%d\n",MyRand(0,65535));
    }
    return 0;
}
