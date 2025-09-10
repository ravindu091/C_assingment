#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "data.h"

#define SEED 12345
#define DEBUG 1
char deBuf[100];

Cell floors[3][10][25];
Player playerA={
    .name = 'A',
    .direction = PA_SD,
    .floor = 0,
    .width = PA_SW,
    .length = PA_SL,
    .startDirection = PA_SD,
    .startWidth = PA_SW,
    .startLength = PA_SL,
    .throwNumber = 0,
    .state = STA
};
Player playerB={
    .name = 'B',
    .direction = PB_SD,
    .floor = 0,
    .width = PB_SW,
    .length = PB_SL,
    .startDirection = PB_SD,
    .startWidth = PB_SW,
    .startLength = PB_SL,
    .throwNumber = 0,
    .state = STA
};
Player playerC={
    .name = 'C',
    .direction = PC_SD,
    .floor = 0,
    .width = PC_SW,
    .length = PC_SL,
    .startDirection = PC_SD,
    .startWidth = PC_SW,
    .startLength = PC_SL,
    .throwNumber = 0,
    .state = STA
};
void printD(char buffer[]){
    if(DEBUG == 1){

    printf("%s \n", buffer);
    }
}

//stair
Stair* stairHead = NULL;
int stairCount =0;
//pole
Pole* poleHead = NULL;
short poleCount = 0;
//flag
Flag flag;
int inValidBlock = 0;
int momentData[3];
int *momentDataPtr = momentData;
int initializePlayers(){
    playerA.direction = PA_SL;
    playerA.floor = 0;
    playerA.width = PA_SW;
    playerA.length = PA_SL;
    
}
void initializeAllCells() {
    for(int x=0;x <3;x++){
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 25; j++) {
                floors[x][i][j].type = FREE;
                floors[x][i][j].isPole = 0;
                floors[x][i][j].isStair = 0;
                floors[x][i][j].momentPoint = 0;
                floors[x][i][j].pointType = NONE;
                floors[x][i][j].floor = x;
                floors[x][i][j].width = i;
                floors[x][i][j].length = j;
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
        return &floors[floorNumber][widthNumber][lengthNumber];
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
            //printf("%d %d %d \n",i , j , ptr->type);
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
    newStair->id = data[6];
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
Stair * findStair(Stair* head, Cell* currentCell,int* isStartCell){
    while(head!=NULL){
        if(((head->startFloor == currentCell->floor)&&(head->startWidth == currentCell->width))&&head->startLength == currentCell->length){
            *isStartCell = 1;
            return head;
        }
        if(((head->endFloor == currentCell->floor)&&(head->endWidth == currentCell->width))&&head->endLength == currentCell->length){
            *isStartCell = 0;
            return head;
        }
        head = head->next;
    }
    return NULL;
}
int loadStairs(){
    char buffer[100];
    char line[100];
    int startFloor, startWidth, startLength, endFloor, endWidth, endLength;
    int validate = 0;
    int stairID = 30;
    FILE *fp = fopen("stairs.txt","r");
    if(fp == NULL){
        printf("Couldn,t open the stairs file \n");
        return 1;
    }
    while (fgets(line,sizeof(line),fp)){
        int matched = sscanf(line,"[%d, %d, %d, %d, %d, %d]",&startFloor,&startWidth,&startLength,&endFloor,&endWidth,&endLength);
        //while(fscanf(fp,"[%d, %d, %d, %d, %d, %d]",&startFloor,&startWidth,&startLength,&endFloor,&endWidth,&endLength)==6){
        if(matched == 6){
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
        startCell->isStair ++;
        endCell->isStair ++;
        stairID++;
        
        //insert to stairs list
        int data[7] = {startFloor,startWidth,startLength,endFloor,endWidth,endLength,stairID};
        printf("Print stair %d %d %d %d %d %d \n", data[0] ,data[1],data[2],data[3],data[4],data[5],data[6]);
        insertStair(&stairHead,data);
        stairCount++;
        }
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
                poleCount++;

                
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
int loadFlag(){
    FILE* fp = fopen("flag.txt","r");
    int floor, width,length;
    if(fp == NULL){
        printf("Can't open the flag file \n");
        logWrite("Cant open the flag file \n");
        return 1;
    }
    while(fscanf(fp, " [ %d , %d , %d ] ", &floor, &width, &length) == 3){
        Cell* currentCell = cell(floor,width,length);
        if(currentCell == NULL){
            printf("Cant locate flag cell \n");
            return 1;
        }
        if((currentCell->type == BLOCK || currentCell->type == WALL)||currentCell->type == START){
            logWrite("Flag can place on that place");
            printf("Flag can't be place");
            return 1;  
        }
        printf("load flag %d %d %d\n",floor,width,length);
        flag.floor = floor;
        flag.width = width;
        flag.length = length;
    }
}
int randomValue(int min , int max){
    int random =  rand()% (max-min +1) + min;
    return random;
}
int addMomentPoint(){
    srand(SEED);
    int validBlocks = 750 - inValidBlock;
    Cell freeCell[validBlocks];
    int index =0;
    for(int x=0;x <3;x++){
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 25; j++) {
                Cell temp = floors[x][i][j];
                if(temp.type == FREE){
                    freeCell[index] = temp;
                    index++;
                } 
            }
        }
    }
    for (int i = 0; i < validBlocks; i++)
    {
        int j = randomValue(0,validBlocks -1);
        Cell temp = freeCell[i];
        freeCell[i] = freeCell[j];
        freeCell[j] = temp;
    }
    int part1 = validBlocks * 25/100;
    int part2 = validBlocks * 35/100;
    int part3 = validBlocks * 25/100;
    int part4 = validBlocks * 10/100;
    int part5 = validBlocks - (part1 + part2 + part3 + part4);

    //consumable zero
    for (int i = 0; i < part1; i++)
    {   
        Cell temp = freeCell[i];
        Cell* currentCell = cell(temp.floor,temp.width,temp.length);
        currentCell->momentPoint = 0;
        currentCell->pointType = NONE;
    }
    //consumable value 1 to 4
    for (int i = part1 ; i < part1 + part2; i++)
    {   
        Cell temp = freeCell[i];
        Cell* currentCell = cell(temp.floor,temp.width,temp.length);
        currentCell->momentPoint = randomValue(1,4);
        currentCell->pointType = DECREASE;
    }
    //bonus 1 to 2
    for (int i = (part1 + part2); i < (part1 + part2 + part3); i++)
    {   
        Cell temp = freeCell[i];
        Cell* currentCell = cell(temp.floor,temp.width,temp.length);
        currentCell->momentPoint = randomValue(1,2);
        currentCell->pointType = ADD;
    }
    //bonus 3 to 5
    for (int i = (part1 + part2 + part3); i < (part1 + part2 + part3+ part4); i++)
    {   
        Cell temp = freeCell[i];
        Cell* currentCell = cell(temp.floor,temp.width,temp.length);
        currentCell->momentPoint = randomValue(3,5);
        currentCell->pointType = ADD;
    }
    //bonus 2 to 3 multiply
    for (int i = (part1 + part2 + part3+ part4); i <(part1 + part2 + part3+ part4 + part5); i++)
    {   
        Cell temp = freeCell[i];
        Cell* currentCell = cell(temp.floor,temp.width,temp.length);
        currentCell->momentPoint = randomValue(2,3);
        currentCell->pointType = MULTIPLY;
    }

    
}
int initializeFloor(){
    //initialize all cells
    initializeAllCells();
    cellTypeWrite(0,6,8,9,16,START);
    printf("in valid cell %d \n",inValidBlock);
    cellTypeWrite(0,7,21,9,24,BAWANA);
    printf("in valid cell %d \n",inValidBlock);
    cellTypeWrite(1,0,8,5,16,BLOCK);
    printf("in valid cell 1st floor %d \n",inValidBlock);
    cellTypeWrite(2,0,17,9,24,BLOCK);
    printf("in valid cell 3rd 1st part floor %d \n",inValidBlock);
    cellTypeWrite(2,0,0,9,7,BLOCK);
    printf("in valid cell 3rd floor %d \n",inValidBlock);
    printf("state on wall function %d\n",loadWalls());
    printf("in valid cell %d \n",inValidBlock);
    printf("state on stairs function %d\n",loadStairs());
    printf("state on pole function %d\n",loadPoles());
    addMomentPoint();
    loadFlag();
    Cell *ptr = cell(0,9,9);
    printf(" where %d \n", ptr->type);

}
Pole * findPole(short width,short length){
    Pole *head = poleHead;
    for(int i =0; i < poleCount ; i++){
        if(head->width == width && head->length==length){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

//get the next cell of the stair
//NextCell nextCell;
NextCell  getNextCell(Stair *currentStair,int isStartCell){
    printD("selecting stair path...");
        NextCell nextCell;
        //set stair id
        nextCell.id = currentStair->id;
        if(currentStair->direction == BOTH){
            printD("Both way can..");
            if(isStartCell == 1){
                printD("upto");
                nextCell.floor= currentStair->endFloor;
                nextCell.width = currentStair->endWidth;
                nextCell.length = currentStair->endLength;
                nextCell.isValid = 1;
                return nextCell;
            }else if(isStartCell == 0){
                printD("down");
                nextCell.floor = currentStair->startFloor;
                nextCell.width = currentStair->startWidth;
                nextCell.length = currentStair->startLength;
                nextCell.isValid = 1;
                return nextCell;
            }
        }else if(currentStair->direction == UP){
            if(isStartCell == 1){
                nextCell.floor = currentStair->endFloor;
                nextCell.width = currentStair->endWidth;
                nextCell.length = currentStair->endLength;
                nextCell.isValid = 1;
                return nextCell;
            }else{
                nextCell.isValid = 0;
                return nextCell;
            }
        }else if(currentStair->direction == DOWN){
            if(isStartCell == 1){
                nextCell.isValid = 0;
                return nextCell;
            }else if(isStartCell == 0){
                nextCell.floor = currentStair->startFloor;
                nextCell.width = currentStair->startWidth;
                nextCell.length = currentStair->startLength;
                nextCell.isValid = 1;
                return nextCell;
            }
        }
}
//
int findDistance(short width, short length){
    printf("flag is %d %d %d \n",flag.floor, flag.width,flag.length);
    return abs(width - flag.width) + abs(length - flag.length);
}
NextCell handleStair(Cell *currentCell,int id){
    int isStartCell1 = 0;
    int isStartCell2 = 0;
    printf("Current cell stairs %d \n",currentCell->isStair);
    if (currentCell->isStair == 1)
    {
        Stair* currentStair = findStair(stairHead,currentCell,&isStartCell1);
        NextCell nextCell = getNextCell(currentStair,isStartCell1);
        if(nextCell.id == id){
            printf("stair id %d \n",nextCell.id);
            nextCell.isValid =0;
            return nextCell;
        }
        printf("stair id %d \n",nextCell.id);
        printD("one stair");
        return nextCell;
    }else if(currentCell->isStair == 2){
        printD("Two stair");
        isStartCell1 = 0;
        isStartCell2 = 0;
        Stair* stair1 = findStair(stairHead,currentCell,&isStartCell1);
        Stair* stair2 = findStair(stair1->next,currentCell,&isStartCell2);
        
        //find distance
        NextCell nextCell1 = getNextCell(stair1,isStartCell1);
        NextCell nextCell2 = getNextCell(stair2,isStartCell2);
        if(nextCell1.id == id){
            nextCell1.isValid =0;
            printD("first stair used");
        }
        if(nextCell2.id == id){
            nextCell2.isValid = 0;
            printD("second stair is used");
        }
        if(nextCell1.isValid == 1 && nextCell2.isValid == 1){
            //find distance of two
            printD("We have two stairs. find distance");
            int distance1 = findDistance(nextCell1.width,nextCell1.length);
            int distance2 = findDistance(nextCell2.width,nextCell2.length);
            if(distance1<distance2){
                printD("select stair 1");
                return nextCell1;
            }else{
                printD("select stair 2");
                return nextCell2;
            }
        }else if(nextCell1.isValid == 0 && nextCell2.isValid == 0){
            printD("both stairs are invalid");
            NextCell nextCell;
            nextCell.isValid = 0;
            return nextCell;
        }else if(nextCell1.isValid == 0){
           printD("stair 1 valid");
            return nextCell2;
        }else if(nextCell2.isValid == 0){
            printD("stair 2 valid");
            return nextCell1;
        }


    }
    NextCell invalid = { .isValid = 0 };
    return invalid;

}
Cell handlePoleStair(Cell currentCell,int s_id){
    
    if(currentCell.isPole == 1){
        Pole *pole = findPole(currentCell.width,currentCell.length);
        if(pole->endFloor == currentCell.floor){
            currentCell.floor = pole->startFloor;
            return currentCell;
        }

    }
    if(currentCell.isStair > 0){
        NextCell nextCell = handleStair(&currentCell, s_id);
        if(nextCell.isValid = 1){
            Cell newCell = *cell(currentCell.floor,currentCell.width,currentCell.length);
            return handlePoleStair(newCell);

        }
    }

    return currentCell;    
}
int checkMoment(enum Direction direction ,short floor,short width,short length,short steps,char name){
    short pastFloor = floor;
    short pastWidth = width;
    short pastLength = length;
    printf("past width %d past length %d \n",pastWidth,pastLength);
    printf("check moment \n");
    const char *directionNames[] = {
        "NORTH","EAST","SOUTH","WEST"
    };
    
    
    for(int i = 0; i < steps; i++){
        //make direction
        switch(direction){
            case NORTH:
                width--;
                break;
            case EAST:
                length++;
                break;
            case SOUTH:
                width++;
                break;
            case WEST:
                length--;
                break;
            default:
                printf("error in direction\n");
                break;
        }
        Cell* checkCell = cell(floor,width,length);
        if (checkCell == NULL || checkCell->type == BLOCK)
        {
            printf("null \n");
            //printf("Player %c rolls and %d on the movement dice and cannot move in the %s. Player remains at (%d,%d)\n",name,diceNumber,directionNames[direction],pastWidth,pastLength);
            return 1 ;
        }else if(checkCell->type == WALL){
            //blocked by wall
            //printf("Player %c rolls and %d on the movement dice and cannot move in the %s. Player remains at (%d,%d)\n",name,diceNumber,directionNames[direction],pastWidth,pastLength);
            printf("wall \n");
            return 1;
        }else if(checkCell->type == START){
            return 1;
        }else{
            if(floor != 0 && checkCell->isPole == 1){
                Pole *pole = findPole(width,length);
                if(pole->startFloor != floor){
                    printf("we have pole %d %d %d\n",floor,width,length);
                    int result = checkMoment(direction,pole->startFloor,width,length,steps - (i+1),name);
                    if(result == 1){
                        //can,t use pole
                        
                        printf("Pole can't use\n");
                        return 1;
                    }else if(result == 0){
                        floor = pole->startFloor;
                        printf("pole can use \n");
                        printf("Player %c lands on (%d,%d) which is a pole cell. \nPlayer %c slides down and now placed at (%d,%d) infloor %d.\n",name,width,length,name,width,length,floor);
                    }
                    
                    //stepped on a pole~
                }
            }
            if(checkCell->isStair > 0){
                if(pastFloor == floor){
                printD("find a stair in");
                NextCell nextCell = handleStair(checkCell,99);
                if(nextCell.isValid == 1){
                    printf("check stair...\n");
                    int result = checkMoment(direction,nextCell.floor,nextCell.width,nextCell.length,steps - (i+1),name,nextCell.id);
                    //s_id=nextCell.id;
                    if(result == 1){
                        //cant use stair
                        printf("cant use stair \n");
                        s_id = 0;
                    }else{
                        pastWidth = width;
                        pastLength = length;
                        floor = nextCell.floor;
                        width = nextCell.width;
                        length = nextCell.length;
                        
                        printf("Player %c lands on [%d , %d] which is a stair cell.\nPlayer %c takes the stairs and now placed at [%d , %d]in floor %d.\n",name,pastWidth,pastLength,name,width,length,floor);
                    }
                }else{
                    s_id=0;
                }

            }
            }

        }
        
        printf("Go %d %d %d \n",floor,width,length);

    }
    return 0;
}

int addMoment(Player * player,short diceNumber){
    
}
int playerMoment(Player* player){

    //if player in start area
    if(player->state == STA){
        short diceNumber = randomValue(1,6);
        if(diceNumber == 6){

        }else{
            printf("Player %c is at the starting area and rolls %d on the movement dice cannot enter the maze.\n",player->name,diceNumber);
        }
    }
}
int play(){
    int count = 0;
    while(count < 10){
        playerMoment(&playerA);
        playerMoment(&playerB);
        playerMoment(&playerC);
        count++;
    }
}
int initialize(){
    FILE *fp = fopen("log.txt","w");
    fclose(fp);
    initializeFloor();
    play();
}