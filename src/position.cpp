#include "position.h"

// 'this -> row_index' means to assign the value of 'row_index' parameter to the 'row_index' (class member) attribute of the current object
// See ImpPoints.txt for more info

/* Constructor */
// position::position(int row_index, int column_index){
//     /*this -> class_member = local parameter*/
//     this -> row_index = row_index;
//     this -> column_index = column_index;
// }

/* Constructor */
position::position(int row_, int column_)
{
    row_index = row_;
    column_index = column_;
}