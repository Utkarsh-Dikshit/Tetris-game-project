#pragma once

#include "position.h"
#include "color.h"
#include <vector>
#include <map>

using namespace std;

class block
{
public:
    block();
    void DrawBlock(int move_in_x, int move_in_y);
    void DrawReferenceBlock(int move_in_x, int move_in_y);
    void Move(int rows, int column);
    vector<position> GetcellPosition();
    vector<position> GetcellPositionForReferenceBLock();
    void MoveReferenceBlock(int rows);
    int id;
    void Rotate();
    void UnDoRoatation();
    int row_offset_referenceBlock;

    /* Here 'key' -> rotation state */
    /* Here 'value' -> vector containing the position of occupied cell */
    map<int, vector<position>> cells;

private:
    int cellsize;
    int rotationState;
    int row_offset, col_offset;
    vector<Color> OuterBlockColor, InnerBlockColor;
};