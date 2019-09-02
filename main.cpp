#include "cell.h"
#include "maze.h"


int main(int argc, char *argv[]){

    Maze maze(40);

    maze.DFGeneration(false);

    maze.displayMaze();

};