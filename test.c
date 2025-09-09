#include "logic.c"


int main(){
    FILE *fp = fopen("log.txt","w");
    fclose(fp);
    initializeFloor();
    printf("\n\n\n\n\n");
    checkMoment(NORTH,1,5,1,6,'A');
    printf("find distance %d \n",findDistance(5,4));
    printf("find distance %d \n",findDistance(3,5));
    
}