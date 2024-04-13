// This is an instruction that ensures that this header file is only
// included once in a compilation unit to avoid duplicate definitions.
#pragma once

#include <raylib.h>
#include "color.h"
#include <vector>

using namespace std;

class Grid
{
public:
    Grid(); /*Constructor*/
    void Initialize();
    void Draw();
    bool IsCellOutside(int row, int column);
    int grid [20][11];

private:
    int cellsize;
    int numRows, numColumns;
    vector <Color> colors;
};