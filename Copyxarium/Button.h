#pragma once
#include "GObject.hpp"
#include <SFML/Graphics.hpp>
#include <functional>


namespace gui
{
	enum _status
	{
		_default,
		_hovered,
		_clicked
	};

	class Label;

	class Button : public GObject
	{
		std::function<void(void)> m_callback = [](){};

	protected:
		sf::FloatRect size;
		sf::RectangleShape rectangle;

		Label *label = nullptr;
		bool isPressed = false;
		bool isHovered = false;
		bool isClickedOnThis = false;
		bool multi_click = false;

	public:
		Button(sf::FloatRect size, const sf::Font &font, sf::String str = "Button");
		virtual ~Button();

		void setString(sf::String);

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
		virtual void update(sf::RenderWindow&) override;
		void bind(std::function<void(void)>);
		virtual void setAnc(Anchor anc) override;
		void setMultiClick(bool flag) { multi_click = flag; }

	protected:
		void setByStat(int);
	};

}