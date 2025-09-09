#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
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
Player ple;
Player *playerA = &ple;
int direction(Player* player,int direction){
    switch(direction)
    {
    case 2:
        player->direction = NORTH;
        break;
    case 3:
        player->direction = EAST;
        break;
    case 4:
        player->direction = SOUTH;
        break;
    case 5:
        player->direction = WEST;
        break;

    default:
        break;
    }
}
int main() {
    srand(123);
    for (int i = 0; i < 100; i++)
    {
        printf("%d \n",randomValue(1,6));
    }

    int direction = 5;

    switch(direction)
    {
    case 2:
        ple.direction = NORTH;
        break;
    case 3:
        ple.direction = EAST;
        break;
    case 4:
        ple.direction = SOUTH;
        break;
    case 5:
        ple.direction = WEST;
        break;

    default:
        break;
    }
    
    return 0;
}