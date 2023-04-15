#include "App.h"
#include "ExtraColors.hpp"

#include "LSqMrealisation.hpp"
#include "LagrangePolynom.h"
#include "SimpsonArea.h"
#include <string>
#include <fstream>

#define POINT_AMOUNT        111
#define EXTRA_BOUND_PERCENT 0.2f


p_vec graph_by_basis(std::vector<_ffunc> basis, axis_vec ratio, float start_point, float end_point, int p_amount)
{
    p_vec result(p_amount+1);

    float dx = (end_point - start_point) / p_amount;
    float x = start_point;

    for (int i = 0; i <= p_amount; ++i)
    {
        result[i].x = x;
        for (int j = 0; j < basis.size(); ++j)
        {
            result[i].y += ratio[j]*basis[j](x);
        }

        x += dx;
    }

    return result;
}

p_vec loadPointsFromFile(std::string fname)
{
    std::ifstream in;
    in.open(fname);

    if (!in.is_open())
        return p_vec();

    int amount;
    in >> amount;
    
    p_vec points(amount);

    for (int i = 0; i < amount; ++i)
    {
        in >> points[i].x >> points[i].y;
    }

    
    in.close();
    return points;
}



int main()
{
    p_vec points =loadPointsFromFile("res/testdata.txt");

    std::vector<_ffunc> basa =
    {
        [](float x)->float { return 1; },                       // const
        [](float x)->float { return x; },                       // line
        //[](float x)->float { return x * x; },                 // parabola
        //[](float x)->float { return x * x * x; },             // cubic parabola
    };

    float start = points[0].x                 - std::abs(points[0].x) * EXTRA_BOUND_PERCENT;
    float end   = points[points.size() - 1].x + std::abs(points[0].x) * EXTRA_BOUND_PERCENT;

    // line
    auto lin_ratio = LSqM_(points, basa);
    p_vec linear        = graph_by_basis(basa,      lin_ratio,      start, end, POINT_AMOUNT);
    
    // parabola
    basa.push_back([](float x)->float { return x * x; });
    auto par_ratio = LSqM_(points, basa);
    p_vec parabola      = graph_by_basis(basa,      par_ratio,      start, end, POINT_AMOUNT);
    
    // cubic parabola
    basa.push_back([](float x)->float { return x * x * x; });
    auto  cub_ratio = LSqM_(points, basa);
    p_vec cub_parabola  = graph_by_basis(basa,      cub_ratio,      start, end, POINT_AMOUNT);

    // Lagrange
    auto lagrange_ratio = LagrPol(points);
    std::vector<_ffunc> lag_basis(lagrange_ratio.size());

    int* power = nullptr;
    for (int i = 0; i < lag_basis.size(); ++i)
    {
        power = new int(i);
        lag_basis[i] = ([power] (float x)->float
            {
                return powf(x, *power);
            }
        );

    }
    std::cout << lagrange_ratio << std::endl;
    p_vec lagrange      = graph_by_basis(lag_basis, lagrange_ratio, start, end, POINT_AMOUNT);


    // Simpson
    float a_line = areaByPoints(linear);
    float a_para = areaByPoints(parabola);
    float a_cubi = areaByPoints(cub_parabola);
    float a_lagr = areaByPoints(lagrange);


    // Graphics
	App lab(1600, 900, "Lab 2");

    lab.pointsAdd(points, "Start points");
    lab.addHBoxSeparate();
    
    lab.addHBoxSeparate("LSqM");
    lab.graphAdd(linear,       sf::Color::Cyan,       "linear"        );
    lab.graphAdd(parabola,     gui::Color::DarkGreen, "parabola"      );
    lab.graphAdd(cub_parabola, gui::Color::DarkRed2,  "cubic parabola");
    lab.addHBoxSeparate();
    
    lab.addHBoxSeparate("Lagrange polinomial");
    lab.graphAdd(lagrange, gui::Color::DarkYellow, "Lagrange");
    lab.addHBoxSeparate();
    
    lab.addHBoxSeparate("Area:");
    lab.addHBoxSeparate("1. Sline = " + std::to_string(a_line));
    lab.addHBoxSeparate("2. Spara = " + std::to_string(a_para));
    lab.addHBoxSeparate("3. Scubi = " + std::to_string(a_cubi));
    lab.addHBoxSeparate("4. Slagr = " + std::to_string(a_lagr));
    while (lab.isOpen())
    {
        lab.update();
        lab.render();
    }

	return 0;
}