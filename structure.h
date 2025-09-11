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
typedef struct{
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