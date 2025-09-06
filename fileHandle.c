#include <stdio.h>
#include "structure.h"

void loadWalls(){
    FILE *fp = fopen("wall.txt","w");
    if(fp == NULL){
        printf("Error: Could not open the wall");
        return 0;

    }
    int floor, startWidth, startLength, endWidth, endLength;
    while(fscanf(fp,"[%d , %d , %d , %d , %d] "),&floor, &startWidth, &startLength, &endWidth, &endLength){
        for(int i = startWidth; i <= endWidth; i++ ){
            for(int j = startLength; j <= endLength; j++){
                Cell temp = cell(floor,i,j);
                temp.type = WALL;
                printf("%d %d %d \n",i , j , temp.type);
            }
        
    }
    }
}