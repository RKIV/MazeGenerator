#pragma once
#include "cell.h"
#include <stack>

/**
 * Create a maze with given number of cells
 * 
 * @param size Dimensions of the maze in cells
 */
class Maze{
    private:
        int size;
        int cellsVisited;
        int currentCellsIndex[2];
        // Array of cells
        Cell** cells;
        // Creating stacks for backtrace when reach deadend
        std::stack <int> cellStack1;
        std::stack <int> cellStack2;
        // Creating stacks to keep track of final solution
        std::stack <int> solutionCellStack1;
        std::stack <int> solutionCellStack2;
    public:
        Maze(int size);
        void DFGeneration(bool printIter);
        void displayMaze();
};