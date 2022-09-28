#include "Maze.h"

//generates maze at specific dimensions
void Maze::createGrid(int row, int col) {
    for(int i = 0; i < row; i++) {
        std::vector<int> temp;
        for(int j = 0; j < col; j++) {
            if(i == 0 && j == 0) 
                temp.push_back(7);
            else
                temp.push_back(15);
        }
        grid.push_back(temp);
    }
}

//gets neighbors of current cell
void Maze::getNeighbors(int row, int col) {
    //North Neighbor
    std::vector<int> idx = {0, 0};
    if(row - 1 >= 0 && grid[row - 1][col] == 15) {
        idx[0] = row - 1;
        idx[1] = col;
        neighbors.push_back(idx);
    }
    //South Neighbor
    if(row + 1 < grid.size() && grid[row + 1][col] == 15) {
        idx[0] = row + 1;
        idx[1] = col;
        neighbors.push_back(idx);
    }
    //East Neighbor
    if(col + 1 < grid[row].size() && grid[row][col + 1] == 15) {
        idx[0] = row;
        idx[1] = col + 1;
        neighbors.push_back(idx);
    }
    //West Neighbor
    if(col - 1 >= 0 && grid[row][col - 1] == 15) {
        idx[0] = row;
        idx[1] = col - 1;
        neighbors.push_back(idx);
    }
};

//picks random neighbor
int Maze::randNeighbor(int seed) {
    int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
    return idx;
}

void Maze::breakWall(int currentRow, int currentCol, int neighRow, int neighCol) {
    if(currentRow == neighRow + 1) {
        grid[currentRow][currentCol] = grid[currentRow][currentCol] - 8;
        grid[neighRow][neighCol] = grid[neighRow][neighCol] - 4;
    }
    else if(currentRow == neighRow - 1) {
        grid[currentRow][currentCol] = grid[currentRow][currentCol] - 4;
        grid[neighRow][neighCol] = grid[neighRow][neighCol] - 8;
    }
    else if(currentCol == neighCol + 1) {
        grid[currentRow][currentCol] = grid[currentRow][currentCol] - 1;
        grid[neighRow][neighCol] = grid[neighRow][neighCol] - 2;
    }
    else if(currentCol == neighCol - 1) {
        grid[currentRow][currentCol] = grid[currentRow][currentCol] - 2;
        grid[neighRow][neighCol] = grid[neighRow][neighCol] - 1;
    }
}

//updates values of current and neighbor
void Maze::createMaze(int seed) {
    std::srand(seed);
    int currentRow = 0;
    int currentCol = 0;
    std::vector<int> visit = {currentRow, currentCol};
    visitLog.push_back(visit);
    while(visitLog.size() != 0) {
        visit = visitLog[visitLog.size() - 1];
        visitLog.pop_back();
        currentRow = visit[0];
        currentCol = visit[1];
        getNeighbors(currentRow, currentCol);
        if(neighbors.size() != 0) {
            visitLog.push_back(visit);
            int idx = randNeighbor(seed);
            std::vector<int> neighIdxs = neighbors[idx];
            breakWall(currentRow, currentCol, neighIdxs[0], neighIdxs[1]);
            visitLog.push_back(neighIdxs);
            neighbors.clear();
        }
    }
    int rows = grid.size() - 1;
    int cols = grid[rows].size() - 1;
    grid[rows][cols] = grid[rows][cols] - 4;
}

void Maze::outFile(std::string fileName) {
    std::ofstream outFile(fileName);
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            outFile << grid[i][j] << " ";
        }
        outFile << std::endl;
    }
    outFile.close();
}

void Maze::drawMaze() {
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}