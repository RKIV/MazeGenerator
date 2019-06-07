#include "cell.h"

Cell::Cell()
{
    Cell::visited = false;
    Cell::eastWall = true;
    Cell::southWall = true;
}

bool Cell::getVisited(){
    return Cell::visited;
}

void Cell::removeWall(int direction){
    if(direction == 0)Cell::southWall = false;
    else Cell::eastWall = false;
}

void Cell::setVisited(){
    Cell::visited = true;
}

bool Cell::getWall(int direction){
    if(direction == 0) return Cell::southWall;
    else return Cell::eastWall;
}
