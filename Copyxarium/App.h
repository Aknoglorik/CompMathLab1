#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class App
{
public:
	App(unsigned int width = 640, unsigned int height = 480, std::string wname = "SFML 2.5.1");
	~App();


private:
	sf::VideoMode VM;
	sf::RenderWindow root;
	sf::Event event_;

	void initWindow(unsigned int width, unsigned int height, std::string wname);
	void initVariables();

public:
	bool isOpen();
	//bool isProgramEnd();

	void pollEvent();
	void update();
	void render();

};