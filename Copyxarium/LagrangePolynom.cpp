#include "LagrangePolynom.h"

// \returns denominator of lagrange polynom
float _calcDenominator(p_vec& points, int id)
{
	if (id >= points.size())
		throw std::exception("Id more that points size");

	float res = 1;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i == id)
			continue;

		res *= points[id].x - points[i].x;
	}
	return res;
}

float _calcRecLoop(p_vec& points, int id, int num_left, int start_pos)
{
	if (!num_left || start_pos >= points.size())
	{
		if (num_left)
			return 0;
		return 1;
	}
	float res = 0;

	for (int i = start_pos; i < points.size(); ++i)
	{
		if (i == id)
			continue;
		res += (-points[i].x) * _calcRecLoop(points, id, num_left - 1, i+1);

	}
	return res;
}

axis_vec _calcProxyPolynom(p_vec& points, int id)
{
	if (id >= points.size())
		throw std::exception("Id more that points size");
	
	axis_vec proxyPol(points.size());
	float value;

	for (int k = points.size()-1; k >= 0; --k) // k - amount of num that must be multiplied
	{
		value = _calcRecLoop(points, id, k, 0);
		proxyPol[points.size()-1 - k] = value;
	}
	return proxyPol;
}


axis_vec LagrPol(p_vec& points)
{
	axis_vec polynom;
	axis_vec result(points.size());

	float denom;
	for (int i = 0; i < points.size(); ++i)
	{
		denom = _calcDenominator(points, i);
		polynom = _calcProxyPolynom(points, i);

		for (int j = 0; j < polynom.size(); ++j)
			result[j] += (points[i].y * polynom[j]) / denom;
		
	}
	return result;
}
