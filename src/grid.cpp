#include <iostream>
#include "grid.h"
using namespace std;

Grid::Grid()
{
    rows = 20;
    columns = 10;
    cellsize = 30;
    Initiaize();
    colors = GetCellColor();
}

void Grid::Initiaize()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grid::Print()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

vector<Color> Grid::GetCellColor()
{
    // 7 colors of different blocks and 1 for the empty cell or space
    Color darkGrey = {26, 31, 40, 255};
    Color grey = {47, 230, 23, 255};
    Color red = {232, 18, 18, 255};
    Color orange = {226, 116, 17, 255};
    Color yellow = {237, 234, 4, 255};
    Color purple = {166, 0, 247, 255};
    Color cyan = {21, 204, 209, 255};
    Color blue = {13, 64, 216, 255};

    return {darkGrey, grey, red, orange, yellow, purple, cyan, blue};
}

void Grid::Draw()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int cellValue = grid[i][j];
            DrawRectangle(j * cellsize + 1, i * cellsize + 1, cellsize - 1, cellsize - 1, colors[cellValue]);
        }
    }
}