#include "color.h"
#include <vector>

using namespace std;

const Color darkGrey = {26, 31, 40, 150};

const Color OuterGreen = {0, 204, 0, 255};
const Color OuterRed = {204, 0, 0, 255};
const Color OuterOrange = {204, 102, 0, 255};
const Color OuterYellow = {235, 235, 0, 255};
const Color OuterPurple = {204, 0, 204, 255};
const Color OuterCyan = {0, 204, 204, 255};
const Color OuterBlue = {0, 0, 204, 255};

const Color InnerGreen = {41, 225, 41, 255};
const Color InnerRed = {240, 48, 48, 255};
const Color InnerOrange = {230, 128, 27, 255};
const Color InnerYellow = {255, 255, 30, 255};
const Color InnerPurple = {255, 51, 255, 255};
const Color InnerCyan = {51, 255, 255, 255};
const Color InnerBlue = {51, 51, 255, 255};

const Color lightBlue = {0, 191, 255, 150};

vector<Color> GetOuterCellColor()
{
    return {darkGrey, OuterGreen, OuterRed, OuterOrange, OuterYellow, OuterPurple, OuterCyan, OuterBlue};
}

vector<Color> GetInnerCellColor()
{
    return {darkGrey, InnerGreen, InnerRed, InnerOrange, InnerYellow, InnerPurple, InnerCyan, InnerBlue};
}
