#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class Graph;
namespace gui
{
	class Camera;
	class GObject;
}

class App
{
public:
	App(unsigned int width = 640, unsigned int height = 480, std::string wname = "SFML 2.5.1");
	~App();


private:
	sf::VideoMode VM;
	sf::RenderWindow root;
	sf::Event event_;

	Graph *graph;

	sf::View default_view;
	gui::Camera *camera; // movable view

	std::list<gui::GObject*> widgets;
	std::list<gui::GObject*> hud_widgets;

	sf::Font font;
	sf::String d_mouse_pos_x;
	sf::String d_mouse_pos_y;

	sf::String d_slider_x_factor;
	sf::String d_slider_y_factor;

	bool isFullscreen;
	int hud_hbox_height;


	void initWindow(unsigned int width, unsigned int height, std::string wname);
	void initVariables();

public:
	bool isOpen();

	void pollEvent();
	void update();
	void render();

	void graphAdd (std::vector<sf::Vector2f>& grpah,  sf::Color color, sf::String str, bool enable = true);
	void pointsAdd(std::vector<sf::Vector2f>& points, sf::String str);
	void addHBoxSeparate(sf::String = "");

};