#include "block.h"

block::block()
{
    cellsize = 30;
    rotationState = 0;
    colors = GetCellColor();
    row_offset = 0;
    col_offset = 0;
}

void block::Draw()
{
    vector<position> tiles = GetcellPosition();
    
    /* You can directly use cells[roatationState] */
    for (position item : tiles)
    {
        DrawRectangle(item.column_index * cellsize + 1, item.row_index * cellsize + 1, cellsize - 1, cellsize - 1, colors[id]);
    }
}

void block:: Move(int move_by_rows, int move_by_columns){
    row_offset += move_by_rows;
    col_offset += move_by_columns;
}

vector<position> block:: GetcellPosition(){
    vector <position> tiles = cells[rotationState];
    vector <position> movedTiles;
    for (position item : tiles){
        position newPostion = position(item.row_index + row_offset, item.column_index + col_offset);
        movedTiles.push_back(newPostion);
    }
    return movedTiles;
}