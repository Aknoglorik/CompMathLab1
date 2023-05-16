#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <SFML/System/Vector2.hpp>

typedef std::vector<std::vector<float>> _fmatrix;
typedef std::vector<sf::Vector2f> p_vec;
typedef std::vector<float> axis_vec;

typedef std::function<float(float)> _ffunc;

inline std::ostream& operator<<(std::ostream& out, _fmatrix matrix)
{
    out << "FMatrix (\n";
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
            out << matrix[i][j] << ' ';
        out << '\n';
    }
    out << ')';
    return out;
}

inline std::ostream& operator<<(std::ostream& out, axis_vec vals)
{
    out << "AxisVec (";
    for (int i = 0; i < vals.size(); ++i)
    {
        out << vals[i];
        if (i < vals.size() - 1)
            out << ' ';
    }
    out << ')';
    return out;
}