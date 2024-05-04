#include "block.h"

block::block()
{
    cellsize = 30;
    rotationState = 0;
    OuterBlockColor = GetOuterCellColor();
    InnerBlockColor = GetInnerCellColor();
    row_offset = 0;
    col_offset = 0;
    row_offset_referenceBlock = 0;
}

void block::DrawBlock(int move_in_x, int move_in_y)
{
    vector<position> tiles = GetcellPosition();

    for (position item : tiles)
    {
        DrawRectangle((float)(GetScreenWidth() - 630)/2 + item.column_index * cellsize + move_in_x, (float)((GetScreenHeight() - 620)/ 2) + item.row_index * cellsize + move_in_y, cellsize - 1, cellsize - 1, OuterBlockColor[id]);
        DrawRectangle((float)(GetScreenWidth() - 630)/2 + item.column_index * cellsize + move_in_x + (cellsize) / 6, (float)((GetScreenHeight() - 620)/ 2) + item.row_index * cellsize + move_in_y + (cellsize) / 6, (cellsize - 1) * 4 / 6, (cellsize - 1) * 4 / 6, InnerBlockColor[id]);
    }
}

void block::DrawReferenceBlock(int move_in_x, int move_in_y)
{
    vector<position> tiles = GetcellPositionForReferenceBLock();

    for (position item : tiles)
    {

        Rectangle rec = {(float) (float)(GetScreenWidth() - 630)/2 + item.column_index * cellsize + move_in_x, (float)((GetScreenHeight() - 620)/ 2) + (item.row_index) * cellsize + move_in_y, (float)cellsize - 1, (float)cellsize - 1};
        DrawRectangleLinesEx(rec, 2, OuterBlockColor[id]);
    }
}

void block::Move(int move_by_rows, int move_by_columns)
{
    row_offset += move_by_rows;
    col_offset += move_by_columns;
}

vector<position> block::GetcellPosition()
{
    vector<position> tiles = cells[rotationState];
    vector<position> movedTiles;
    for (position item : tiles)
    {
        position newPostion = position(item.row_index + row_offset, item.column_index + col_offset);
        movedTiles.push_back(newPostion);
    }
    return movedTiles;
}

void block::MoveReferenceBlock(int move_by_rows)
{
    row_offset_referenceBlock += move_by_rows;
}

vector<position> block::GetcellPositionForReferenceBLock()
{
    vector<position> tiles = GetcellPosition();
    vector<position> movedTiles;
    for (position item : tiles)
    {
        position newPosition = position(item.row_index + row_offset_referenceBlock, item.column_index);
        movedTiles.push_back(newPosition);
    }
    return movedTiles;
}

void block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void block::UnDoRoatation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = (int)cells.size() - 1;
    }
}
