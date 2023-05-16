#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "GObject.hpp"


namespace gui
{

	class Slider : public GObject
	{
		float max_value;
		float min_value;
		float value;
		int *d_value = nullptr;
		float circle_radius;

		sf::FloatRect hitbox;
		sf::RectangleShape line1, line2;
		sf::CircleShape circle;

		bool isPressed = false;
		bool isHovered = false;
		bool isClickedOnThis = false;
		std::function<void(float)> m_callback;
		

	public:
		Slider(sf::Vector2f p1, sf::Vector2f size, float start_value = 50, float _min_value = 0, float _max_value = 100, std::function<void(int)> callback = [](float) {});
		~Slider();

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&) override;

		void setByStat(int status);
		void setValue(float val);
		//void setDynamicValue(int& val) { d_value = &val; }

		float getValue() { return value; }

		void bind(std::function<void(float)> callback) { m_callback = callback; }

	private:
		void setupByPos(sf::Vector2f pos);
	};

}