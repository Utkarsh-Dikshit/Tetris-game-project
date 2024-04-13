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
    void Draw();
    void Move(int rows, int column);
    vector<position> GetcellPosition();
    int id;
    
    /* Here 'key' is going to be the rotation state (there will be 4 rotation state) */
    /* Here 'value' is going to be the vector containing the position of occupied cell */
    map<int, vector<position>> cells;

private:
    int cellsize;
    int rotationState;
    int row_offset, col_offset;
    vector<Color> colors;
};