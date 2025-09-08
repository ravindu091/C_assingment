#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

Cell floor1[10][25];
Cell floor2[10][25];
Cell floor3[10][9];
//stair
Stair* stairHead = NULL;
int stairCount =0;

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
    fclose(fp);
    return validated;

}
// create stair node
Stair *createStair(int data[6]){
    Stair* newStair = (Stair*)malloc(sizeof(Stair));
    if (newStair == NULL){
        printf("Memory allocation failed for stairs");
        exit(1);
    }
    newStair->startFloor = data[0];
    newStair->startWidth = data[1];
    newStair->startLength = data[2];
    newStair->endFloor = data[3];
    newStair->endWidth = data[4];
    newStair->endLength = data[5];
    newStair->direction = BOTH;
    newStair->next = NULL;
    return newStair;
}
//insert stair to linked list
void insertStair(Stair* head, int data[6]){
    Stair* newStair = createStair(data);
    newStair->next = head;
    head = newStair;

}

int loadStairs(){
    char buffer[100];
    int startFloor, startWidth, startLength, endFloor, endWidth, endLength;
    int validate = 0;

    FILE *fp = fopen("stairs.txt","r");
    if(fp == NULL){
        printf("Couldn,t open the stairs file \n");
        return 1;
    }

    while(fscanf(fp,"[%d, %d, %d, %d, %d, %d]",&startFloor,&startWidth,&startLength,&endFloor,&endWidth,&endLength)){
        printf("Read the stairs file \n");
        sprintf(buffer,"invalid stair at [%d,%d,%d,%d,%d,%d]",startFloor,startWidth,startLength,endFloor,endWidth,endLength);
        if(!((0 <= endLength && endLength < 25) &&(0 <= startLength && startLength < 25) &&(0 <= startWidth  && startWidth  < 10) &&(0 <= endWidth && endWidth< 10))){
            strcat(buffer, "Invalid stair\n");
            logWrite(buffer);
            return 1;
        }
        //read start and end cell
        Cell *startCell = cell(startFloor,startWidth,startLength);
        Cell *endCell = cell(endFloor,endWidth,endLength);
        if ((startCell == NULL)||(endCell ==NULL))
        {
            strcat(buffer,"Cell not found\n");
            logWrite(buffer);
            printf("%s",buffer);
            return 1;
        }
        //validate
        if(startCell->type == BLOCK){
            strcat(buffer,"Can't implement on blocked cell\n");
            logWrite(buffer);
            printf("%s",buffer);
            return 1;

        }else if(startCell->type == WALL){
            strcat(buffer,"Can't implement on a wall\n");
            logWrite(buffer);
            printf("%s",buffer);
            return 1;
        }
        //implement
        startCell->isStair = 1;
        endCell->isStair = 1;

        //insert to stairs list
        int data[6] = {startFloor,startWidth,startLength,endFloor,endWidth,endLength};
        insertStair(stairHead,data);
        stairCount++;
    }
    fclose(fp);
    printf("Show the stairs");

    Stair *current = stairHead;
    if (current == NULL)
    {
        printf("Cant find the stairs list\n");
        return 1;
    }
    
    while(current != NULL){
        printf(" stairs are %d %d %d \n",current->startFloor,current->startWidth,current->startLength);
        current = current->next;
    }
}

int loadPoles(){
    char line[100];
    int startFloor, endFloor, width,length;
    FILE *fp = fopen("poles.txt","r");
    if(fp == NULL){
        printf("Can't open the poles file");
        return 1;
    }
    while(fgets(line,sizeof(line),fp)){
        int matched = sscanf(line,"[%d, %d, %d, %d]",&startFloor,&endFloor,&width,&length);

        if (matched == 6)
        {
            //pole in valid format
        }else{
            //not a valid pole
        }
        
    }
    fclose(fp);
}
int initializeFloor(){
    cellTypeWrite(0,6,8,16,9,START);
    cellTypeWrite(1,0,8,5,16,BLOCK);
    printf("state on wall function %d\n",loadWalls());
    printf("state on stairs function %d\n",loadStairs());
    Cell *ptr = cell(0,9,9);
    printf(" where %d \n", ptr->type);
}

int initialize(){
    FILE *fp = fopen("log.txt","w");
    fclose(fp);
    initializeFloor();
}