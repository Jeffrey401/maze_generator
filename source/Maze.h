#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class Maze {
    private:
        //All vectors store coordinates [[i, j]]
        std::vector<std::vector<int>> grid;
        std::vector<std::vector<int>> visitLog;
        std::vector<std::vector<int>> neighbors;
    public:
        void createGrid(int row, int col);
        void getNeighbors(int row, int col);
        int randNeighbor(int seed);
        void breakWall(int currentRow, int currentCol, int neighRow, int neighCol);
        void createMaze(int seed);
        void outFile(std::string fileName);
        void drawMaze();
};