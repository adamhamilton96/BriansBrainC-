#include <iostream>
#include <stdlib.h>
#include <thread>  
#include <chrono>        

using namespace std;

void draw();
void calculate();
void createGrid();
void clearBorders();

const int gridWidth = 140;
const int gridHeight = 70;
int grid[gridHeight][gridWidth];
int nextGrid[gridHeight][gridWidth];
int chance = 85;
int speed = 1;
bool leastOne;

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
    leastOne = false;
    for(int i = 0; i < gridHeight; i++) {
        for(int j = 0; j < gridWidth; j++) {
            neighbours = 0;
            if (grid[i-1][j+1] == 1) neighbours++;
            if (grid[i][j+1] == 1) neighbours++;
            if (grid[i+1][j+1] == 1) neighbours++;
            if (grid[i+1][j] == 1) neighbours++;
            if (grid[i-1][j] == 1) neighbours++;
            if (grid[i-1][j-1] == 1) neighbours++;
            if (grid[i][j-1] == 1) neighbours++;
            if (grid[i+1][j-1] == 1) neighbours++;

            if (grid[i][j] == 0 && neighbours == 2) {
                nextGrid[i][j] = 1;
                leastOne = true;
            } else if (grid[i][j] == 1) {
                nextGrid[i][j] = 2;
            }
        }
    }
    clearBorders();
    for (int i = 0; i < gridHeight; i++) {
        for (int j = 0; j < gridWidth; j++) {
            grid[i][j] = nextGrid[i][j];
        }
    }
    for (int i = 0; i < gridHeight; i++) {
        for (int j = 0; j < gridWidth; j++) {
            nextGrid[i][j] = 0;
        }
    }
    if (leastOne == false) {
        createGrid();
    }
}

void draw() {
    for(int i = 0; i < gridHeight; i++) {
        for(int j = 0; j < gridWidth; j++) {
            if(grid[i][j] == 0) {
                cout << "\033[40m  \033[0m";
            } else if(grid[i][j] == 1) {
                cout << "\033[47m  \033[0m";
            } else if (grid[i][j] == 2) {
                cout << "\033[104m  \033[0m";
            }
        }
        cout << endl;
    }
}

void createGrid() {
    srand(time(0));
    for (int i = 0; i < gridHeight; i++) {
        for (int j = 0; j < gridWidth; j++) {
            if (rand() % 100 > chance) grid[i][j] = 1;
            else grid[i][j] = 0;
        }
    }
}

void clearBorders() {
    for (int j = 0; j < gridWidth; j++) {
        nextGrid[0][j] = 0;
        nextGrid[gridHeight - 1][j] = 0;
    }
    for (int i = 1; i < gridHeight - 1; i++) {
        nextGrid[i][0] = 0;
        nextGrid[i][gridWidth - 1] = 0;
    }
}