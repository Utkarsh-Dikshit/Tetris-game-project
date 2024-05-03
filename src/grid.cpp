#include "grid.h"
using namespace std;

Grid::Grid()
{
    numRows = 20;
    numColumns = 11;
    cellsize = 30;
    Initialize();
    colors = GetOuterCellColor();
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
            DrawRectangle(j * cellsize + 11, i * cellsize + 11, cellsize - 1, cellsize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numColumns)
    {
        return false;
    }
    return true;
}

bool Grid::IsRowEmpty(int row)
{
    for (int col = 0; col < numColumns; col++)
    {
        if (grid[row][col] == 0)
        {
            return true;
        }
    }
    return false;
}

void Grid::ClearRow(int row)
{
    for (int col = 0; col < numColumns; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int moveByRow)
{
    for (int column = 0; column < numColumns; column++)
    {
        grid[row + moveByRow][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

int Grid::ClearFullRow()
{
    int completedRow = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowEmpty(row) == false)
        {
            completedRow++;
            ClearRow(row);
        }
        else if (completedRow > 0)
        {
            MoveRowDown(row, completedRow);
        }
    }
    return completedRow;
}