enum Direction {
    NORTH , EAST, SOUTH, WEST
};
enum Type{
    FREE ,WALL, POLE, STAIR, START,BLOCK,BAWANA
};
enum PointType{
    ADD , DECREASE , MULTIPLY , NONE
};
enum StairDirection{
    UP , DOWN , BOTH
};
typedef struct{
    char floor;
    enum Direction direction;
    char throwNumber;
    short width;
    short length;
    short state;
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
    short startFloor;
    short endFloor;
    short startWidth;
    short startLength;
    short endWidth;
    short endLength;
    enum StairDirection direction;
    struct Stair *next;
    
}Stair;
