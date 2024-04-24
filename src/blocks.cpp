#include "block.h"
#include "position.h"

/* Using Hierarchical Inheritance */

class LBlock : public block
{
public:
    LBlock()
    {
        id = 1;
        cells[0] = {position(0, 2), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(1, 1), position(2, 1), position(2, 2)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 0)};
        cells[3] = {position(0, 0), position(0, 1), position(1, 1), position(2, 1)};
        Move(0, 4);
    }
};

class JBlock : public block
{
public:
    JBlock()
    {
        id = 2;
        cells[0] = {position(0, 0), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(0, 2), position(1, 1), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 2)};
        cells[3] = {position(0, 1), position(1, 1), position(2, 0), position(2, 1)};
        Move(0, 4);
    }
};

class IBlock : public block
{
public:
    IBlock()
    {
        id = 3;
        cells[0] = {position(1, 0), position(1, 1), position(1, 2), position(1, 3)};
        cells[1] = {position(0, 2), position(1, 2), position(2, 2), position(3, 2)};
        cells[2] = {position(2, 0), position(2, 1), position(2, 2), position(2, 3)};
        cells[3] = {position(0, 1), position(1, 1), position(2, 1), position(3, 1)};
        Move(-1, 3);
    }
};

class OBlock : public block
{
public:
    OBlock()
    {
        id = 4;
        cells[0] = {position(0, 0), position(0, 1), position(1, 0), position(1, 1)};
        Move(0, 4);
    }
};

class SBlock : public block
{
public:
    SBlock()
    {
        id = 5;
        cells[0] = {position(0, 1), position(0, 2), position(1, 0), position(1, 1)};
        cells[1] = {position(0, 1), position(1, 1), position(1, 2), position(2, 2)};
        cells[2] = {position(1, 1), position(1, 2), position(2, 0), position(2, 1)};
        cells[3] = {position(0, 0), position(1, 0), position(1, 1), position(2, 1)};
        Move(0, 4);
    }
};

class TBlock : public block
{
public:
    TBlock()
    {
        id = 6;
        cells[0] = {position(0, 1), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(1, 1), position(1, 2), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 1)};
        cells[3] = {position(0, 1), position(1, 0), position(1, 1), position(2, 1)};
        Move(0, 4);
    }
};

class ZBlock : public block
{
public:
    ZBlock()
    {
        id = 7;
        cells[0] = {position(0, 0), position(0, 1), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 2), position(1, 1), position(1, 2), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(2, 1), position(2, 2)};
        cells[3] = {position(0, 1), position(1, 0), position(1, 1), position(2, 0)};
        Move(0, 4);
    }
};
