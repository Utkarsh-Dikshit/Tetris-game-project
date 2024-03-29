// This is an instruction that ensures that this header file is only
// included once in a compilation unit to avoid duplicate definitions.
#pragma once

#include <vector>
#include <raylib.h>
using namespace std;

class Grid
{
public:
    Grid(); /*Constructor*/
    void Initiaize();
    void Print();
    void Draw();
    int grid [20][10];

private:
    vector <Color> GetCellColor();
    int rows, columns;
    int cellsize;
    /*Using vector to hold the info about colors*/
    vector <Color> colors; 
};