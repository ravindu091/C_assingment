#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

#define SEED 12345

Cell floor[3][10][25];

//stair
Stair* stairHead = NULL;
Pole* poleHead = NULL;
int stairCount =0;
int inValidBlock = 0;
void initializeAllCells() {
    for(int x=0;x <3;x++){
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 25; j++) {
                floor[x][i][j].type = FREE;
                floor[x][i][j].isPole = 0;
                floor[x][i][j].isStair = 0;
                floor[x][i][j].momentPoint = 0;
                floor[x][i][j].pointType = NONE;
            }
        }
    }
    
    
    
}
int inRange(int value, int start, int end){
    if (start <= value && value <= end)
    {
        return 1;
    }
    return 0;
    
}
Cell* cell(int floorNumber, int widthNumber,int lengthNumber ){
    if((inRange(floorNumber , 0,2))&&((inRange(widthNumber,0,9))&&(inRange(lengthNumber,0,24)))){
        return &floor[floorNumber][widthNumber][lengthNumber];
    }
    return NULL;
}

//Write on log file
int logWrite(const char *message ){
    FILE *fp = fopen("log.txt","a");
    if(fp == NULL){
        printf("Error: Could not open the file \n");
        return 1;
    }
    
    fprintf(fp,message);
    fclose(fp);
}
void cellTypeWrite(int floorNumber, int startWidth, int startLength, int endWidth, int endLength , enum Type type ){
    for(int i = startWidth; i <= endWidth; i++ ){
        for(int j = startLength; j <= endLength; j++){
            Cell *ptr = cell(floorNumber,i,j);

            ptr->type = type;
            inValidBlock++;
            printf("%d %d %d \n",i , j , ptr->type);
        }
        
    }
    printf("end \n");
}

//Load the wall
int loadWalls(){
    char buffer[100];
    int validated = 0; //if all walls are valid value is 0
    int floorNumber, startWidth, startLength, endWidth, endLength;
    printf("Load wall function \n");
    FILE *fp = fopen("walls.txt","r");
    if(fp == NULL){
        printf("Error: Could not open the wall");
        logWrite("wall file can not open");
        return 1;
    }
    
    //read the file
    while(fscanf(fp,"[%d, %d, %d, %d, %d] ",&floorNumber, &startWidth, &startLength, &endWidth, &endLength)==5){
        printf("read file\n");
        //validation
        if((0 <= endLength && endLength < 25) &&(0 <= startLength && startLength < 25) &&(0 <= startWidth  && startWidth  < 10) &&(0 <= endWidth    && endWidth    < 10)){
            printf("valid walls \n");
            if((startLength == endLength)||(startWidth == endWidth)){
                //valid
            }else{
                printf("Unvalid wall not a line\n");
                sprintf(buffer, "The wall %d, %d, %d, %d, %d is not valid (not aline) \n",floorNumber, startWidth, startLength, endWidth, endLength);
                logWrite(buffer);
                return 1;
            }
        }else {
            printf("Error on the walls \n");
            return 1;
        }
        for(int i = startWidth; i <= endWidth; i++ ){
            for(int j = startLength; j <= endLength; j++){
                Cell *ptr = cell(floorNumber,i,j);
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
            if (startWidth == endWidth)
            {
                if (startLength > endLength)
                {
                    int temp;
                    temp = startLength;
                    startLength = endLength;
                    endLength = temp;
                }
                

            }
            if(startLength == endLength){
                if(startWidth > endWidth){
                    int temp;
                    temp = startWidth;
                    startWidth = endWidth;
                    endWidth = temp;
                }
            }
            
          for(int i = startWidth; i <= endWidth; i++ ){
            for(int j = startLength; j <= endLength;  j++){
                Cell *temp = cell(floorNumber,i,j);
                temp->type = WALL;
                inValidBlock++;
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
        return NULL;
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
void insertStair(Stair **head, int data[6]){
    Stair* newStair = createStair(data);
    newStair->next = *head;
    *head = newStair;

}
//create pole node
Pole* createPole(int data[5]){
    Pole* newPole = (Pole*)malloc(sizeof(Pole));
    if(newPole == NULL){
        logWrite("can't memory allocate for pole \n");
        return NULL;
    }
    newPole->startFloor = data[0];
    newPole->endFloor = data[1];
    newPole->width = data[2];
    newPole->length = data[3];
    newPole->isMiddle = data[4];
    newPole->next = NULL;
    return newPole;
}
//insert pole node to linked list
void insertPole(Pole **head, int data[5]){
    Pole* newPole = createPole(data);
    newPole->next = *head;
    *head = newPole;
}
//load stairs
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
        insertStair(&stairHead,data);
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
//load poles
int loadPoles(){
    int lineCount = 0;
    char line[100];
    char buffer[100];
    int startFloor, endFloor, width,length;
    FILE *fp = fopen("poles.txt","r");
    if(fp == NULL){
        printf("Can't open the poles file");
        return 1;
    }
    //read poles file
    while(fgets(line,sizeof(line),fp)){
        //matching the pole file
        lineCount++;
        int matched = sscanf(line,"[%d, %d, %d, %d]",&startFloor,&endFloor,&width,&length);

        if (matched == 4)
        {
            //pole in valid format
            sprintf(buffer,"The pole [%d, %d, %d, %d] ",startFloor, endFloor, width,length);
            if (
                ( inRange(startFloor,0,3) && inRange(endFloor,0,3))&&(inRange(width,0,10) && inRange(length,0,25))
            )
            {   
                //if pole in range
                Cell *startCell = cell(startFloor,width,length);
                Cell *endCell = cell(endFloor,width, length);
                if (startCell == NULL || endCell == NULL)
                {   
                    strcat(buffer, "on the null cell \n");
                    logWrite(buffer);
                    return 1;
                }
                if (startCell->type == BLOCK || endCell->type == BLOCK)
                {
                    strcat(buffer,"on the blocked cell \n");
                    logWrite(buffer);
                    return 1;
                }
                if (startCell->type == WALL || endCell->type == WALL)
                {
                    strcat(buffer,"on the wall \n");
                    logWrite(buffer);
                    return 1;
                }
                
                //check the pole is cross a floor
                int isCrossFloor = (startFloor > endFloor) ? startFloor - endFloor : endFloor - startFloor;
                if (isCrossFloor == 2)
                {
                    Cell *middleCell = cell(2,width,length);
                    if (middleCell->type == BLOCK || middleCell->type == WALL)
                    {
                        strcat(buffer, "error in the middle cell block cell or wall \n");
                        logWrite(buffer);
                        return 1;
                    }else{
                        //write as a pole cell
                        middleCell->isPole = 1;
                    }
                    isCrossFloor = 1;
                }
                //write as pole cell
                startCell->isPole = 1;
                endCell->isPole = 1;
                int data[5] = {startFloor , endFloor , width , length, isCrossFloor};
                insertPole(&poleHead,data);

                
            }else{
                strcat(buffer,"values are not in the range \n");
                logWrite(buffer);
                return 1;
            }
            
        }else{
            //not a valid pole
            sprintf(buffer,"Not valid pole in %d line \n",lineCount);
            printf("%s \n",buffer);
            logWrite(buffer);
        }
        
    }
    if (lineCount == 0)
    {
        logWrite("There are nothing on poles.txt file \n");
    }
    
    fclose(fp);
}
int initializeFloor(){
    cellTypeWrite(0,6,8,9,16,START);
    printf("in valid cell %d \n",inValidBlock);
    cellTypeWrite(0,7,21,9,24,BAWANA);
    printf("in valid cell %d \n",inValidBlock);
    cellTypeWrite(1,0,8,5,16,BLOCK);
    printf("in valid cell %d \n",inValidBlock);
    printf("state on wall function %d\n",loadWalls());
    printf("in valid cell %d \n",inValidBlock);
    printf("state on stairs function %d\n",loadStairs());
    printf("state on pole function %d\n",loadPoles());
    Cell *ptr = cell(0,9,9);
    printf(" where %d \n", ptr->type);

}

int initialize(){
    FILE *fp = fopen("log.txt","w");
    fclose(fp);
    initializeFloor();
}