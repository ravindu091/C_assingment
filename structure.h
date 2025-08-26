enum Direction {
    NORTH , EAST, SOUTH, WEST
};
enum Type{
    WALL, POLE, STAIR, START, FREE
};

typedef struct
{
    char floor;
    enum Direction direction;
    char startingDirection;
    char throwNumber;
    short width;
    short length;
    short state;
    short startPositionWidth;
    short startPositionLength;

    
} Player;

typedef struct{
    enum Type type;
    short state;
} Cell;
