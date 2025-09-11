#include "main.c"
NextCell handleStair(Cell *currentCell, int id) {
    // If there is one stair
    if (currentCell->isStair == 1) {
        int isStartCell = 0;
        Stair* stair = findStair(stairHead, currentCell, &isStartCell);
        if (stair != NULL) {
            NextCell nextCell = getNextCell(stair, isStartCell);
            return nextCell; // Always return the next cell for single stair
        } else {
            NextCell invalid = { .isValid = 0 };
            return invalid;
        }
    } 
    // If there are two stairs
    else if (currentCell->isStair == 2) {
        int isStartCell1 = 0, isStartCell2 = 0;
        Stair* stair1 = findStair(stairHead, currentCell, &isStartCell1);
        Stair* stair2 = NULL;
        if (stair1 != NULL) {
            stair2 = findStair(stair1->next, currentCell, &isStartCell2); // Find second stair starting from next
        }
        
        // If both stairs are found
        if (stair1 != NULL && stair2 != NULL) {
            NextCell nextCell1 = getNextCell(stair1, isStartCell1);
            NextCell nextCell2 = getNextCell(stair2, isStartCell2);

            // If both next cells are valid, choose based on distance and id
            if (nextCell1.isValid && nextCell2.isValid) {
                int distance1 = findDistance(nextCell1.width, nextCell1.length);
                int distance2 = findDistance(nextCell2.width, nextCell2.length);

                // Avoid previous stair if possible
                if (nextCell1.id == id && nextCell2.id != id) {
                    return nextCell2;
                } else if (nextCell2.id == id && nextCell1.id != id) {
                    return nextCell1;
                } else {
                    // Choose based on distance
                    if (distance1 < distance2) {
                        return nextCell1;
                    } else if (distance2 < distance1) {
                        return nextCell2;
                    } else {
                        // Distances equal, choose randomly
                        if (rand() % 2 == 0) {
                            return nextCell1;
                        } else {
                            return nextCell2;
                        }
                    }
                }
            } else if (nextCell1.isValid) {
                return nextCell1;
            } else if (nextCell2.isValid) {
                return nextCell2;
            }
        } 
        // If only one stair is found
        else if (stair1 != NULL) {
            NextCell nextCell = getNextCell(stair1, isStartCell1);
            return nextCell;
        } else if (stair2 != NULL) {
            NextCell nextCell = getNextCell(stair2, isStartCell2);
            return nextCell;
        }
    }
    
    // No valid stair found
    NextCell invalid = { .isValid = 0 };
    return invalid;
}
if(floor != 0 && checkCell->isPole == 1){
                Pole *pole = findPole(width,length);
                if(pole->startFloor != floor){
                    printf("we have pole %d %d %d\n",floor,width,length);
                    int result = checkMoment(direction,pole->startFloor,width,length,steps - (i+1),name,s_id);
                    if(result == 1){
                        //can,t use pole
                        s_id = 0;
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
            printf("Player %c lands on (%d,%d) which is a pole cell. \nPlayer %c slides down and now placed at (%d,%d) infloor %d.\n",name,width,length,name,width,length,floor);
            if(floor != 0 && checkCell->isPole == 1){
                Pole *pole = findPole(width,length);
                if(pole->startFloor != floor){
                    printf("we have pole %d %d %d\n",floor,width,length);
                    int result = checkMoment(direction,pole->startFloor,width,length,steps - (i+1),name,s_id);
                    if(result == 1){
                        //can,t use pole
                        s_id = 0;
                        printf("Pole can't use\n");
                        return 1;
                    }else if(result == 0){
                        floor = pole->startFloor;
                        printf("pole can use \n");
                        printf("Player %c lands on (%d,%d) which is a pole cell. \nPlayer %c slides down and now placed at (%d,%d) infloor %d.\n",name,width,length,name,width,length,floor);
                    }
                    
                    //stepped on a pole~
                }
            }if(floor != 0 && checkCell->isPole == 1){
                Pole *pole = findPole(width,length);
                if(pole->startFloor != floor){
                    printf("we have pole %d %d %d\n",floor,width,length);
                    int result = checkMoment(direction,pole->startFloor,width,length,steps - (i+1),name,s_id);
                    if(result == 1){
                        //can,t use pole
                        s_id = 0;
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
                NextCell nextCell = handleStair(checkCell,s_id);
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
