#include "logic.c"


int main(){
    FILE *fp = fopen("log.txt","w");
    fclose(fp);
    initializeFloor();
    printf("\n\n\n\n\n");
    //checkMoment(NORTH,1,6,1,6,'A',0);
    printf("test stair \n");
    checkMoment(SOUTH,0,1,4,5,'A',0);

    printf("find distance %d \n",findDistance(5,4));
    printf("find distance %d \n",findDistance(3,5));
    
}