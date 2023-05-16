#pragma once

#include "GObject.hpp"
#include <vector>


struct d_graph
{
	d_graph(const std::vector<sf::Vector2f>& graph, sf::Color color, bool enable)
		: _graph(graph), _color(color), _enable(enable) {}

	std::vector<sf::Vector2f> _graph;
	sf::Color _color;
	bool _enable;
};

class Graph : public gui::GObject
{
	std::vector<d_graph> graphs;
	std::vector<sf::Vector2f> points; // not graph points

	// graph props
	float x_factor, y_factor;
	float g_thickness;

	sf::Vector2f _size;
	sf::FloatRect g_rect;

	sf::Color dot_color;
	bool enable_dot;
	bool enable_g_dot;

public:
	Graph(sf::Vector2f size);
	~Graph();

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
	virtual void update(sf::RenderWindow&) override {};

	void drawLine(sf::RenderTarget& target, sf::RenderStates states, sf::Color color, sf::Vector2f pos, float lenght, float thickness, float angle) const;
	void drawDot (sf::RenderTarget& target, sf::RenderStates states, sf::Color color, sf::Vector2f pos, float thickness) const;

	void addGraph (std::vector<sf::Vector2f>& graph,  sf::Color color = sf::Color::Cyan, bool enable = true);
	void setEnable(std::size_t id, bool flag)		{ graphs[id]._enable = flag;  }
	void setColor (std::size_t id, sf::Color color) { graphs[id]._color  = color; }
	void setGraphsDotEnable(bool flag) { enable_g_dot = flag; }
	
	void addPoints(std::vector<sf::Vector2f>& points);
	void setDotEnable(bool flag) { enable_dot = flag; }
	void setDotColor (std::size_t id, sf::Color color) { dot_color = color; }

	void factorLinesThick(float factor) { g_thickness *= factor; }
	void setFactor(sf::Vector2f factor) { x_factor = factor.x; y_factor = factor.y; }
	sf::Vector2f getFector() { return sf::Vector2f(x_factor, y_factor); }

	int count() { return graphs.size(); }
	d_graph& getGraphById(std::size_t id) { return graphs[id]; }

	sf::Vector2f getFactor() { return sf::Vector2f(x_factor, y_factor); }
};

