#include "App.h"

int main()
{
	App lab(1600, 900, "CopyXarium");

    std::vector<sf::Vector2f> gr1 = { sf::Vector2f(0, 0), sf::Vector2f(1, 1), };
    std::vector<sf::Vector2f> gr2 = { sf::Vector2f(0, 0), sf::Vector2f(1, 2), };
    std::vector<sf::Vector2f> gr3 = { sf::Vector2f(0, 0), sf::Vector2f(1, 3), };
    std::vector<sf::Vector2f> gr4 = { sf::Vector2f(0, 0), sf::Vector2f(1, 4), };
    std::vector<sf::Vector2f> gr5 = { sf::Vector2f(0, 0), sf::Vector2f(1, 5), };

    lab.addHBoxSeparate("LSqM");
    lab.graphAdd(gr1, sf::Color::Cyan, "Constant");
    lab.graphAdd(gr2, sf::Color::Cyan, "parabl");
    lab.graphAdd(gr3, sf::Color::Cyan, "square");
    lab.addHBoxSeparate();

    lab.addHBoxSeparate("Simp");
    lab.graphAdd(gr4, sf::Color::Cyan, "gr 4");
    lab.graphAdd(gr5, sf::Color::Cyan, "gr 5");
    while (lab.isOpen())
    {
        lab.update();
        lab.render();
    }

	return 0;
}