#include <stdio.h>
#include <stdlib.h>
#include "structure.h"


Player player1;
Player player2;
Player player3;

Player *ptrPlayer1 = &player1;    
Player *ptrPlayer2 = &player2;    
Player *ptrPlayer3 = &player3;

int floor1[25][10]={};
int floor2[25][10]={};

int drwCount = 1;

int drawDies(){
    int diceNumber = (rand()%6)+1;
    return diceNumber;
}

void definePlayerPoint(){
   //player 1
   player1.floor = 0;
   player1.direction = 'n';
   player1.width = 6;
   player1.length = 12;
   player1.state = 1;
   player1.throwNumber = 0;
   player1.startingDirection = 'n';
   player1.startPositionWidth = 6;
   player1.startPositionLength = 12;

   //player 2
   player2.floor = 0;
   player2.direction = 'w';
   player2.width = 9;
   player2.length = 8;
   player2.state = 1;
   player2.throwNumber = 0;
   player2.startingDirection = 'w';
   player2.startPositionWidth = 9;
   player2.startPositionLength = 8;

   //player 3
   player3.floor = 0;
   player3.direction = 'e';
   player3.width = 9;
   player3.length = 17;
   player3.state = 1;
   player3.throwNumber = 0;
   player3.startingDirection = 'e';
   player3.startPositionWidth = 9;
   player3.startPositionLength = 17;
}


void inputFileRead(){

}

int addMoment(Player* player, char direction){
    switch(direction){
        case 'n':
            *player.width -=1;
            break;
        case 'e':
            *player.length +=1;
            break;
        case 's':
            *player.width += 1;
            break:
        case 'w':
            *player.length -= 1;
            break;
        default:
            return 1;
            break;
    }
}

void playerMoment(Player* player,int diceNumber){
    int state = *player.state;
    if(state = 1){
        if(diceNumber == 6){
            addMoment(player,*player.startingDirection);
        }
        
    }
}

void momentPlay(int number){
    
    switch(drwCount){
        case 1:
            playerMoment(*ptrPlayer1,number);
            break;
        case 2:
            playerMoment(*ptrPlayer2 , number);
            break;
        case 3:
            playerMoment(*ptrPlayer3,number);
            break;
        default:
            break;
    } 

}
