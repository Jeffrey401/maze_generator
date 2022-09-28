#include "Maze.h"

int main(int argc, char* argv[]) {
    Maze myMaze;
    myMaze.createGrid(std::stoi(argv[2]), std::stoi(argv[3]));
    myMaze.createMaze(std::stoi(argv[1]));
    myMaze.outFile(argv[4]);
}