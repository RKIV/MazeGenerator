#include "cell.h"
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include <limits>


int main(int argc, char *argv[]){

    int SIZE;
    char printIter;

    std::cout << "Size of maze(single integer): ";
    while(!(std::cin >> SIZE)){
        std::cout << "Bad value!\nSize of maze(single integer): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Print every iteration of maze generation('y' for prints)(Not recommended for sizes larger than 10): ";
    while(!(std::cin >> printIter)){
        std::cout << "Bad value!\nPrint every iteration of maze generation('y' for prints)(Not recommended for sizes larger than 10): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    
    const int START_CELL_INDEX[2] = {1, 0};
    const int END_CELL_INDEX[2] = {SIZE-1, SIZE-1};

    std::stack <int> cellStack1;
    std::stack <int> cellStack2;
    std::stack <int> solutionCellStack1;
    std::stack <int> solutionCellStack2;
    srand(time(NULL));
    rand();

    int cellsVisited = 1;
    int currentCellIndex[2] = {0, 0};

    Cell cells[SIZE][SIZE];
    cells[SIZE-1][SIZE-1].removeWall(0);
    


    while(cellsVisited < SIZE * SIZE){
        //Outputing the Maze every iteration
        if(&printIter == "y"){
            std::cout << "  ";
            for(int i = 0; i < SIZE - 1; i++){
                std::cout << "__";
            }
            std::cout << std::endl;
            for(int j = 0; j < SIZE; j++){
                std::cout << "|";
                for(int i = 0; i < SIZE; i++){
                    if(cells[j][i].getWall(0)){
                        std::cout << "_";
                    } else {
                        std::cout << " ";
                    }
                    if(cells[j][i].getWall(1)){
                        std::cout << "|";
                    } else {
                        std::cout << " ";
                    }
                }
                std::cout << std::endl;
            }
        }



        //Set current cell to be visited
        cells[currentCellIndex[0]][currentCellIndex[1]].setVisited();

        // 
        if(currentCellIndex[0]==SIZE-1 && currentCellIndex[1]==SIZE-1){
            solutionCellStack1 = cellStack1;
            solutionCellStack2 = cellStack2;
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
        if(currentCellIndex[direction] + sign >= 0 && currentCellIndex[direction] + sign < SIZE){
            int newIndex[2];
            if(direction == 0){
                newIndex[0] = currentCellIndex[direction] + sign;
                newIndex[1] = currentCellIndex[perpDirection];
            } 
            else{
                newIndex[0] = currentCellIndex[perpDirection];
                newIndex[1] = currentCellIndex[direction] + sign;
            }
            if(!cells[newIndex[0]][newIndex[1]].getVisited()){
                if(sign < 0){
                    cells[newIndex[0]][newIndex[1]].removeWall(direction);
                } else {
                    cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(direction);
                }
                cellsVisited ++;
                cellStack1.push(currentCellIndex[0]);
                cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=SIZE-1 || newIndex[1]!=SIZE-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        if(currentCellIndex[direction] - sign >= 0 && currentCellIndex[direction] - sign < SIZE){
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
                    cells[newIndex[0]][newIndex[1]].removeWall(direction);
                } else {
                    cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(direction);
                }
                cellsVisited ++;
                cellStack1.push(currentCellIndex[0]);
                cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=SIZE-1 || newIndex[1]!=SIZE-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        if(currentCellIndex[perpDirection] + sign >= 0 && currentCellIndex[perpDirection] + sign < SIZE){
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
                    cells[newIndex[0]][newIndex[1]].removeWall(perpDirection);
                } else {
                    cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(perpDirection);
                }
                cellsVisited ++;
                cellStack1.push(currentCellIndex[0]);
                cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=SIZE-1 || newIndex[1]!=SIZE-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        if(currentCellIndex[perpDirection] - sign >= 0 && currentCellIndex[perpDirection] - sign < SIZE){
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
                    cells[newIndex[0]][newIndex[1]].removeWall(perpDirection);
                } else {
                    cells[currentCellIndex[0]][currentCellIndex[1]].removeWall(perpDirection);
                }
                cellsVisited ++;
                cellStack1.push(currentCellIndex[0]);
                cellStack2.push(currentCellIndex[1]);
                if(newIndex[0]!=SIZE-1 || newIndex[1]!=SIZE-1){
                    currentCellIndex[0] = newIndex[0];
                    currentCellIndex[1] = newIndex[1];
                } else {
                    cells[newIndex[0]][newIndex[1]].setVisited();
                }
                continue;
            }
        }
        // If no available neighbors, pop back on the stack until available neighbors are found.
        currentCellIndex[0] = cellStack1.top();
        currentCellIndex[1] = cellStack2.top();
        cellStack1.pop();
        cellStack2.pop();

    }

    // Outputting Final Maze
    std::cout << " S";
    for(int i = 0; i < SIZE - 1; i++){
        std::cout << "__";
    }
    std::cout << std::endl;
    for(int j = 0; j < SIZE; j++){
        std::cout << "|";
        for(int i = 0; i < SIZE; i++){
            if(cells[j][i].getWall(0)){
                std::cout << "_";
            } else {
                std::cout << " ";
            }
            if(cells[j][i].getWall(1)){
                std::cout << "|";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    for(int i = 0; i < SIZE-1; i++) std::cout << "  ";
    std::cout << " E";
};