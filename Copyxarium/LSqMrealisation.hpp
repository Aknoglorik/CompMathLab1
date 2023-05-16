#pragma once 
#include "mainDecl.h"


// \brief If src is nllptr will use value of points
float discVectrorProduct(_ffunc* src1, _ffunc* src2, p_vec& points);

// \brief subtract horizontal lines (id1 - multipler * id2)
void subtractLine(_fmatrix& matrix, int id1, int id2, float multipler = 1);

// \brief multiple horizontal line by a number
void multiplyLine(_fmatrix& matrix, float multipler, int id);


// \brief Change source matrix
// \returns true - if linear system has finite slolution
bool GaussMethod(_fmatrix& matrix);

// \brief solution on extra column, because "matrix" is identity matrix
// \returns true - if linear system has finite slolution
bool JordanGaussMethod(_fmatrix& matrix);

// \brief Least Squares method
axis_vec LSqM_(p_vec& _points, std::vector<_ffunc>& basis);
