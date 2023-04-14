#pragma once

#include "Graph.h"
#include "CheckButton.h"
#include "Label.h"
#include "Camera.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class App
{
public:
	App(unsigned int width = 640, unsigned int height = 480, std::string wname = "SFML 2.5.1");
	~App();


private:
	sf::VideoMode VM;
	sf::RenderWindow root;
	sf::Event event_;
	Graph *graph; // movable view
	sf::View default_view;

	gui::Camera *camera;
	std::list<gui::GObject*> widgets;
	std::list<gui::GObject*> hud_widgets;

	sf::Font font;

	bool isFullscreen;
	int hud_hbox_height;


	void initWindow(unsigned int width, unsigned int height, std::string wname);
	void initVariables();

public:
	bool isOpen();

	void pollEvent();
	void update();
	void render();

	void graphAdd(std::vector<sf::Vector2f>& grpah, sf::Color color, sf::String str, bool enable = true);
	void addHBoxSeparate(sf::String = "");

};