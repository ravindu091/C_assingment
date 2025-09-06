#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

Cell floor1[10][25];
Cell floor2[10][25];
Cell floor3[10][9];


Cell* cell(int floorNumber, int widthNumber,int lengthNumber ){
    if(floorNumber == 2){
        return &floor3[widthNumber][lengthNumber + 8];
    }else if(floorNumber == 0){
        return &floor1[widthNumber][lengthNumber];

    }else if(floorNumber == 1){
        return &floor2[widthNumber][lengthNumber];
    } 
    return NULL;
}

//Write on log file
void logWrite(const char *message ){
    FILE *fp = fopen("log.txt","a");
    if(fp == NULL){
        printf("Error: Could not open the file \n");
    }
    
    fprintf(fp,message);
    fclose(fp);
}
void cellTypeWrite(int floor, int startWidth, int startLength, int endWidth, int endLength , enum Type type ){
    for(int i = startWidth; i <= endWidth; i++ ){
        for(int j = startLength; j <= endLength; j++){
            Cell *ptr = cell(floor,i,j);

            ptr->type = type;
            
            printf("%d %d %d \n",i , j , ptr->type);
        }
        
    }
    printf("end \n");
}
//Load the wall
int loadWalls(){
    char buffer[100];
    int validated = 0; //if all walls are valid value is 0
    int floor, startWidth, startLength, endWidth, endLength;
    printf("Load wall function \n");
    FILE *fp = fopen("walls.txt","r");
    if(fp == NULL){
        printf("Error: Could not open the wall");
        logWrite("wall file can not open");
        return 1;
    }
    
    //read the file
    while(fscanf(fp,"[%d, %d, %d, %d, %d] ",&floor, &startWidth, &startLength, &endWidth, &endLength)==5){
        printf("read file\n");
        //validation
        if((0 <= endLength && endLength < 25) &&(0 <= startLength && startLength < 25) &&(0 <= startWidth  && startWidth  < 10) &&(0 <= endWidth    && endWidth    < 10)){
            printf("valid walls \n");
            if((startLength == endLength)||(startWidth == endWidth)){
                //valid
            }else{
                printf("Unvalid wall not a line\n");
                sprintf(buffer, "The wall %d, %d, %d, %d, %d is not valid (not aline) \n",floor, startWidth, startLength, endWidth, endLength);
                logWrite(buffer);
                return 1;
            }
        }else {
            printf("Error on the walls \n");
            return 1;
        }
        for(int i = startWidth; i <= endWidth; i++ ){
            for(int j = startLength; j <= endLength; j++){
                Cell *ptr = cell(floor,i,j);
                printf("state of the cell %d \n" ,ptr->type);
                if(ptr->type == BLOCK){
                    sprintf(buffer,"wall can't be place on %d %d blocked cell \n",i , j);
                    logWrite(buffer);
                    validated = 1;
                }else if(ptr->type == START){
                    sprintf(buffer,"wall can't be place on %d %d start cell \n",i , j);
                    logWrite(buffer);
                    validated = 1;
                }
                
                
            }
        }
        //if validated
        //initializing
        if (validated == 0)
        {
          for(int i = startWidth; i <= endWidth; i++ ){
            for(int j = startLength; j <= endLength; j++){
                Cell *temp = cell(floor,i,j);
                temp->type = WALL;
                printf("Wall implemented %d %d %d \n",i , j , temp->type);
                
            }  

          }
        
        }
    
    }
    return validated;

}

int initializeFloor(){
    cellTypeWrite(0,6,8,16,9,START);
    cellTypeWrite(1,0,8,5,16,BLOCK);
    printf("state on wall function %d\n",loadWalls());
    Cell *ptr = cell(0,9,9);
    printf(" where %d \n", ptr->type);
}

int initialize(){
    FILE *fp = fopen("log.txt","w");
    fclose(fp);
    initializeFloor();
}