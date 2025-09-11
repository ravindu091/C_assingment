enum Direction {
    NORTH , EAST, SOUTH, WEST
};
enum Type{
    FREE ,WALL,START,BLOCK,BAWANA,FLAG
};
enum PointType{
    ADD , DECREASE , MULTIPLY , NONE
};
enum StairDirection{
    UP , DOWN , BOTH
};
enum PlayerState{
    STA,NORMAL,SPECIAL
};
enum BawanaType{
    FOOD,DISORIENTED,TRIGGERED,HAPPY,NO 
};
enum CurrentPlayer{
    NP , A, B,C
};
typedef struct{
    const short position;
    enum Direction direction;
    char name;
    char floor;
    char throwNumber;
    short width;
    short length;
    enum PlayerState state;
    const enum Direction startDirection;
    const short startFloor;
    const short startWidth;
    const short startLength;
    short isFood;
    short isDisoriented;
    short isTriggered;
    int momentPoint;

} Player;

typedef struct{
    enum Type type;
    short floor;
    short width;
    short length;
    short isPole;
    short isStair;
    short momentPoint;
    enum PointType pointType;
    enum CurrentPlayer currentPlayer;

} Cell;

typedef struct Pole{
    short startFloor;
    short endFloor;
    short width;
    short length;
    short isMiddle;
    struct Pole *next;
} Pole;
typedef struct Stair{
    short id;
    short startFloor;
    short endFloor;
    short startWidth;
    short startLength;
    short endWidth;
    short endLength;
    enum StairDirection direction;
    struct Stair *next;
    
}Stair;

typedef struct NextCell {
    short id;
    short floor;
    short width;
    short length;
    short isValid;
}NextCell;

typedef struct Flag{
    short floor;
    short width;
    short length;
} Flag;

typedef struct Bawana {
    short width;
    short length;
    enum BawanaType type;
    short point;
}Bawana;