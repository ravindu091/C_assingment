enum Direction {
    NORTH , EAST, SOUTH, WEST
};
enum Type{
    WALL, POLE, STAIR, START, FREE,BLOCK
};
enum PointType{
    ADD , DECREASE , MULTIPLY , NONE
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
    short state;
    int momentPoint;
    enum PointType pointType;

} Cell;

typedef struct {
    int startFloor;
    int endFloor;
    int width;
    int length;
} Pole;
typedef struct{
    
} Stair;
