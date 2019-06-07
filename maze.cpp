#include "cell.h"
#include "maze.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Maze::Maze(int size, bool printIter){
        Maze::size = size;
        Maze::printIter = printIter;
        Maze::cells = new Cell*[Maze::size];
        for(int i = 0; i < Maze::size; i++)
            Maze::cells[i] = new Cell[Maze::size];
    }

// Depth First Maze Generation
void Maze::DFGeneration(){
    
    // Seeding random directon
    srand(time(NULL));
    rand();

    // Initializing cells visited and current cell visited
    int cellsVisited = 1;
    int currentCellIndex[2] = {0, 0};

    // Removing wall from end of maze
    cells[Maze::size-1][Maze::size-1].removeWall(0);

    while(cellsVisited < Maze::size * Maze::size){
        if(Maze::printIter){
            Maze::displayMaze();
        }


        //Set current cell to be visited
        Maze::cells[currentCellIndex[0]][currentCellIndex[1]].setVisited();

        // If reached end of maze set solution stack to current stack
        if(currentCellIndex[0]==Maze::size-1 && currentCellIndex[1]==Maze::size-1){
            Maze::solutionCellStack1 = Maze::cellStack1;
            Maze::solutionCellStack2 = Maze::cellStack2;
        }

        // Generating a random Direction to move
        // 0 = vertical, 1 = horizontal
        bool direction = rand() % 2;
        bool perpDirection = direction == 0;

        //Choosing a random positive or negative movement
        // Negative Sign = up or left | Positive Sign = down or right
        int x = rand() - 16383;
        int sign;
        if(x > 0) sign = 1;
        else sign = -1;

        // Finding the first possible neighbor
        if(currentCellIndex[direction] + sign >= 0 && currentCellIndex[direction] + sign < Maze::size){
            int newIndex[2];
            // Setting new cell index based on random direction and sign
            if(direction == 0){
                newIndex[0] = currentCellIndex[direction] + sign;
                newIndex[1] = currentCellIndex[perpDirection];
            } 
            else{
                newIndex[0] = currentCellIndex[perpDirection];
                newIndex[1] = currentCellIndex[direction] + sign;
            }
            // Checking if new cell is visited
            if(!Maze::cells[newIndex[0]][newIndex[1]].getVisited()){
                // Removing walls
                if(sign < 0){
                    Maze::cells[newIndex[0]][newIndex[1]].removeWall(direction);
                } else {
                    Maze::cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(direction);
                }
                cellsVisited ++;
                // Updating stack and current cell
                Maze::cellStack1.push(currentCellIndex[0]);
                Maze::cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=Maze::size-1 || newIndex[1]!=Maze::size-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    Maze::cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        if(currentCellIndex[direction] - sign >= 0 && currentCellIndex[direction] - sign < Maze::size){
            int newIndex[2];
            if(direction == 0){
                newIndex[0] = currentCellIndex[direction] - sign;
                newIndex[1] = currentCellIndex[perpDirection];
            }
            else{
                newIndex[0] = currentCellIndex[perpDirection];
                newIndex[1] = currentCellIndex[direction] - sign;
            }
            if(!cells[newIndex[0]][newIndex[1]].getVisited()){
                if(-sign < 0){
                    Maze::cells[newIndex[0]][newIndex[1]].removeWall(direction);
                } else {
                    Maze::cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(direction);
                }
                cellsVisited ++;
                Maze::cellStack1.push(currentCellIndex[0]);
                Maze::cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=Maze::size-1 || newIndex[1]!=Maze::size-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    Maze::cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        if(currentCellIndex[perpDirection] + sign >= 0 && currentCellIndex[perpDirection] + sign < Maze::size){
            int newIndex[2];
            if(perpDirection == 0){ 
                newIndex[0] = currentCellIndex[perpDirection] + sign;
                newIndex[1] = currentCellIndex[direction];
            } 
            else{
                newIndex[0] = currentCellIndex[direction];
                newIndex[1] = currentCellIndex[perpDirection] + sign;
            }
            if(!cells[newIndex[0]][newIndex[1]].getVisited()){
                if(sign < 0){
                    Maze::cells[newIndex[0]][newIndex[1]].removeWall(perpDirection);
                } else {
                    Maze::cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(perpDirection);
                }
                cellsVisited ++;
                Maze::cellStack1.push(currentCellIndex[0]);
                Maze::cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=Maze::size-1 || newIndex[1]!=Maze::size-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    Maze::cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        if(currentCellIndex[perpDirection] - sign >= 0 && currentCellIndex[perpDirection] - sign < Maze::size){
            int newIndex[2];
            if(perpDirection == 0){ 
                newIndex[0] = currentCellIndex[perpDirection] - sign;
                newIndex[1] = currentCellIndex[direction];
            }
            else{
                newIndex[0] = currentCellIndex[direction];
                newIndex[1] = currentCellIndex[perpDirection] - sign;
            }
            if(!cells[newIndex[0]][newIndex[1]].getVisited()){
                if(-sign < 0){
                    Maze::cells[newIndex[0]][newIndex[1]].removeWall(perpDirection);
                } else {
                    Maze::cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(perpDirection);
                }
                cellsVisited ++;
                Maze::cellStack1.push(currentCellIndex[0]);
                Maze::cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=Maze::size-1 || newIndex[1]!=Maze::size-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    Maze::cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        // If no available neighbors, pop back on the stack until available neighbors are found.
        currentCellIndex[0] = Maze::cellStack1.top();
        currentCellIndex[1] = Maze::cellStack2.top();
        Maze::cellStack1.pop();
        Maze::cellStack2.pop();

    }
}

void Maze::displayMaze(){
    std::cout << "  ";
    for(int i = 0; i < Maze::size - 1; i++){
        std::cout << "__";
    }
    std::cout << std::endl;
    for(int j = 0; j < Maze::size; j++){
        std::cout << "|";
        for(int i = 0; i < Maze::size; i++){
            if(Maze::cells[j][i].getWall(0)){
                std::cout << "_";
            } else {
                std::cout << " ";
            }
            if(Maze::cells[j][i].getWall(1)){
                std::cout << "|";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}