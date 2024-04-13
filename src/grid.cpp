#include "grid.h"
using namespace std;

Grid::Grid()
{
    numRows= 20;
    numColumns = 11;
    cellsize = 30;
    Initialize();
    colors = GetCellColor();
}

void Grid::Initialize()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grid::Draw()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            int cellValue = grid[i][j];
            DrawRectangle(j * cellsize + 1, i * cellsize + 1, cellsize - 1, cellsize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numColumns){
        return false;
    }
    return true;
}
