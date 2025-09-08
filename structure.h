enum Direction {
    NORTH , EAST, SOUTH, WEST
};
enum Type{
    FREE ,WALL, POLE, STAIR, START,BLOCK
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
    short isPole;
    short isStair;
    int momentPoint;
    enum PointType pointType;

} Cell;

typedef struct Pole{
    int startFloor;
    int endFloor;
    int width;
    int length;
    short isMiddle;
    struct Pole *next;
} Pole;
typedef struct Stair{
    int startFloor;
    int endFloor;
    int startWidth;
    int startLength;
    int endWidth;
    int endLength;
    enum StairDirection direction;
    struct Stair *next;
    
}Stair;
