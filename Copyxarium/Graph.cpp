#include "Graph.h"
#include "ExtraColors.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#define GRAPH_THICKNESS			2
#define GRAPH_DOT_REL_SIZE		2.f


// \brief Finds rect of the graph and union with previus bound
sf::FloatRect recalculateBorder(std::vector<sf::Vector2f>& graph, sf::FloatRect bound)
{
	for (auto point : graph)
	{
		if (point.x == 2)
			sf::Color x = gui::Color::Clay;
		if (point.x > (bound.left + bound.width))
			bound.width = point.x - bound.left;
		if (point.y > (bound.top + bound.height))
			bound.height = point.y - bound.top;

		if (point.x < bound.left)
		{
			bound.width += bound.left - point.x;
			bound.left = point.x;
		}
		if (point.y < bound.top)
		{
			bound.height += bound.top - point.y;
			bound.top = point.y;
		}
	}
	return bound;
}

float distance(sf::Vector2f p1, sf::Vector2f p2)
{
	return powf( (powf((p1.x - p2.x), 2) + powf(p1.y - p2.y, 2)) , 0.5);
}

// \return angle between point in degrees
float angle(sf::Vector2f p1, sf::Vector2f p2)
{
	return atan2f(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI;
}


Graph::Graph(sf::Vector2f size) : _size(size)
{
	dot_color = gui::Color::DarkGray;
	enable_dot = true;
	enable_g_dot = true;

	x_factor = 1;
	y_factor = 1;

	g_thickness = GRAPH_THICKNESS;

	g_rect.top = 0;
	g_rect.left = 0;
	g_rect.width = 0;
	g_rect.height = 0;
}

Graph::~Graph()
{
	for (d_graph graph_info : graphs)
		graph_info._graph.clear();
	graphs.clear();
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	std::vector<sf::Vector2f> *graph;
	sf::Color color;

	sf::Vector2f p1, p2;

	// axis x
	drawLine(target, states, gui::Color::DarkGray2, sf::Vector2f(g_rect.left * x_factor, 0), g_rect.width * x_factor, g_thickness, 0);
	drawLine(target, states, gui::Color::DarkGray2, sf::Vector2f(0, g_rect.top * -y_factor), g_rect.height * -y_factor, g_thickness, 90);

	// graphs
	for (d_graph graph_info : graphs)
	{
		if (!graph_info._enable)
			continue;

		graph = &graph_info._graph;
		color = graph_info._color;
		// lines
		for (int i = 0; i < graph->size() - 1; ++i)
		{
			p1 = (*graph)[i];
			p2 = (*graph)[i+1];
			p1.x *= x_factor;
			p2.x *= x_factor;
			p1.y *= -y_factor;
			p2.y *= -y_factor;
			drawLine(target, states, color, p1, distance(p1, p2), g_thickness, angle(p1, p2));
		}
		// graph dots
		if (enable_g_dot)
		{
			for (int i = 0; i < graph->size(); ++i)
			{
				p1 = (*graph)[i];
				p1.x *= x_factor;
				p1.y *= -y_factor;
				drawDot(target, states, dot_color, p1, g_thickness * GRAPH_DOT_REL_SIZE);
			}
		}
	}

	// dots
	if (!enable_dot)
		return;

	for (sf::Vector2f p : points)
	{
		p.x *= x_factor;
		p.y *= -y_factor;
		drawDot(target, states, dot_color, p, g_thickness * GRAPH_DOT_REL_SIZE);
	}
}

void Graph::drawLine(sf::RenderTarget& target, sf::RenderStates states, sf::Color color, sf::Vector2f pos, float lenght, float thickness, float angle) const
{
	sf::RectangleShape line(sf::Vector2f(lenght, thickness));
	sf::Vector2f _norm(-sin(angle * M_PI / 180), cos(angle * M_PI / 180));
	line.setPosition(pos - _norm * thickness * 0.5f);
	line.setRotation(angle);
	line.setFillColor(color);

	target.draw(line, states);
}

void Graph::drawDot(sf::RenderTarget& target, sf::RenderStates states, sf::Color color, sf::Vector2f pos, float thickness) const
{
	sf::CircleShape dot(thickness);
	dot.setPosition(pos - sf::Vector2f(thickness, thickness));
	dot.setFillColor(color);

	target.draw(dot, states);
}

void Graph::addGraph(std::vector<sf::Vector2f>& graph, sf::Color color, bool enable)
{
	if (!graphs.size() && !g_rect.height && !g_rect.width)
		g_rect = sf::FloatRect(graph[0].x, graph[0].y, 0, 0);

	g_rect = recalculateBorder(graph, g_rect);

	x_factor = _size.x / g_rect.width;
	y_factor = _size.y / g_rect.height;
	setOrigin(g_rect.left * x_factor, (g_rect.top + g_rect.height) * -y_factor);

	graphs.push_back(d_graph(graph, color, enable));
}

void Graph::addPoints(std::vector<sf::Vector2f>& new_points)
{
	int old_size = points.size();
	points.resize(old_size + new_points.size());

	g_rect = recalculateBorder(new_points, g_rect);

	x_factor = _size.x / g_rect.width;
	y_factor = _size.y / g_rect.height;
	setOrigin(g_rect.left * x_factor, (g_rect.top + g_rect.height) * -y_factor);

	for (int i = 0; i < new_points.size(); ++i)
	{
		points[i + old_size] = new_points[i];
	}
}
