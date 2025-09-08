#include <stdio.h>
#include <stdlib.h>
#define SEED 123
#define SEED2 1234

int randomValue(int min , int max){
    int random =  rand()% (max-min +1) + min;
    return random;
}
int randomValue2(){
    srand(234);
    return rand();
}
int main() {
    srand(123);
    for (int i = 0; i < 100; i++)
    {
        printf("%d \n",randomValue(1,6));
    }
    
    
    return 0;
}