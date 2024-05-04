#pragma once

#include <raylib.h>
#include <vector>
using namespace std;

extern const Color darkGrey;
extern const Color OuterGreen;
extern const Color OuterRed;
extern const Color OuterOrange;
extern const Color OuterYellow;
extern const Color OuterPurple;
extern const Color OuterCyan;
extern const Color OuterBlue;

extern const Color InnerOrange;
extern const Color InnerGreen;
extern const Color InnerRed;
extern const Color InnerBlue;
extern const Color InnerPurple;
extern const Color InnerBlue;
extern const Color InnerBlue;

extern const Color lightBlue;

vector<Color> GetOuterCellColor();
vector<Color> GetInnerCellColor();