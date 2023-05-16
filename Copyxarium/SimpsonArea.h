#pragma once
#include "mainDecl.h"

inline float areaByPoints(p_vec& points)
{
	if (points.size() % 2)
		return 0;

	float area = points[0].y + points[points.size() - 1].y;

	for (int i = 1; i < points.size() - 1; ++i)
	{
		if (i % 2)
			area += 4*points[i].y;
		else
			area += 2*points[i].y;
	}

	area *= (points[1].x - points[0].x) / 3;
	return area;
}