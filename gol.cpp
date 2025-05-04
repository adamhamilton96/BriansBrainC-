#include <iostream>
#include <stdlib.h>
#include <thread>  
#include <chrono>        

using namespace std;

void draw();
void calculate();
void createGrid();

const int gridSize = 70;
int grid[gridSize][gridSize];
int nextGrid[gridSize][gridSize];
int chance = 85;
int speed = 1;

int main() {
    createGrid();
    while (true) {
        draw();
        std::this_thread::sleep_for (std::chrono::milliseconds(50));
        system("clear");
        for(int i = 0; i < speed; i++) {
            calculate();
        }
    }

    return 0;
}

void calculate() {
    int neighbours;
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            neighbours = 0;
            if (grid[i-1][j+1] == 1) neighbours++;
                if (grid[i][j+1] == 1) neighbours++;
                if (grid[i+1][j+1] == 1) neighbours++;
                if (grid[i+1][j] == 1) neighbours++;
                if (grid[i-1][j] == 1) neighbours++;
                if (grid[i-1][j-1] == 1) neighbours++;
                if (grid[i][j-1] == 1) neighbours++;
                if (grid[i+1][j-1] == 1) neighbours++;

                if (grid[i][j] == 0) {
                    if (neighbours == 3) nextGrid[i][j] = 1;
                    else nextGrid[i][j] = 0;
                } else if (grid[i][j] == 1) {
                    if (neighbours < 2 || neighbours > 3) nextGrid[i][j] = 0;
                    else nextGrid[i][j] = 1;
                }
        }
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = nextGrid[i][j];
        }
    }
        
   for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            nextGrid[i][j] = 0;
        }
    }
}

void draw() {
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            if(grid[i][j] == 0) {
                cout << "\033[40m  \033[0m";
            } else if(grid[i][j] == 1) {
                cout << "\033[47m  \033[0m";
            }
        }
        cout << endl;
    }
}

void createGrid() {
    srand (time(NULL));
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (rand() % 100 > chance) grid[i][j] = 1;
            else grid[i][j] = 0;
        }
    }
}