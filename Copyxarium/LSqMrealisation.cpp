#include "LSqMrealisation.hpp"


// \brief If src is nllptr will use value of points
float discVectrorProduct(_ffunc* src1, _ffunc* src2, p_vec& points)
{
    float result = 0;
    float delta;

    int i;
    // #pragma omp parallel for private(i) reduce(+:result)
    for (i = 0; i < points.size(); ++i)
    {
        if (src1)
            delta = (*src1)(points[i].x);
        else
            delta = points[i].y;

        if (src2)
            delta *= (*src2)(points[i].x);
        else
            delta *= points[i].y;

        result += delta;
    }

    return result;
}

// \brief subtract horizontal lines (id1 - multipler * id2)
void subtractLine(_fmatrix& matrix, int id1, int id2, float multipler)
{
    if (matrix[id1].size() != matrix[id2].size())
        throw std::exception("lines sizes are not equal.");

    if (id1 == id2)
        return;

    for (int j = 0; j < matrix[id1].size(); ++j)
        matrix[id1][j] -= multipler * matrix[id2][j];
}

// \brief multiple horizontal line by a number
void multiplyLine(_fmatrix& matrix, float multipler, int id)
{
    for (int j = 0; j < matrix[id].size(); ++j)
        matrix[id][j] *= multipler;
}


// \brief Change source matrix
// \returns true - if linear system has finite slolution
bool GaussMethod(_fmatrix& matrix)
{
    bool is_finite = true;

    for (int i = 0; i < matrix.size(); ++i) // up -> down
    {
        if (matrix[i][i])
            multiplyLine(matrix, 1.f / matrix[i][i], i); // make 1 on lead position
        else
            is_finite = false; // zero on main diagonal -> system has infinity solutions or has not solution

        for (int j = i + 1; j < matrix.size(); ++j)
            subtractLine(matrix, j, i, matrix[j][i]);
    }

    return is_finite;
}

// \brief solution on extra column, because "matrix" is identity matrix
// \returns true - if linear system has finite slolution
bool JordanGaussMethod(_fmatrix& matrix)
{
    if (!GaussMethod(matrix))
        return false;

    // matrix is triangular matrix
    for (int i = matrix.size() - 1; i >= 0; --i) // down -> up
        for (int j = i - 1; j >= 0; --j)
            subtractLine(matrix, j, i, matrix[j][i]);

    return true;
}

// \brief Least Squares method
axis_vec LSqM_(p_vec& _points, std::vector<_ffunc>& basis)
{
    if (!basis.size())
    {
        throw std::exception("empty basis was given.");
    }

    _fmatrix eq_sys(basis.size());
    axis_vec result(basis.size());

    for (int i = 0; i < eq_sys.size(); ++i)
        eq_sys[i].resize(eq_sys.size() + 1);

    for (int i = 0; i < eq_sys.size(); ++i)
        for (int j = i; j < eq_sys.size(); ++j)
        {
            // Main matrix
            float result = discVectrorProduct(&basis[i], &basis[j], _points);
            eq_sys[i][j] = result;
            eq_sys[j][i] = result;
        }

    // extra column
    int last_col = eq_sys[0].size() - 1;
    for (int i = 0; i < eq_sys.size(); ++i)
    {
        eq_sys[i][last_col] = discVectrorProduct(&basis[i], nullptr, _points);
    }
    if (!JordanGaussMethod(eq_sys))
    {
        throw std::exception("Unexcepted error.");
    }
    for (int i = 0; i < basis.size(); ++i)
        result[i] = eq_sys[i][last_col];

    return result;
}

