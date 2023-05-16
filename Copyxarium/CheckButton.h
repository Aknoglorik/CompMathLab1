#pragma once
#include "Button.h"


namespace gui
{
	class CheckButton final : public gui::Button
	{
		bool btn_status;
		std::function<void(bool)> m_callback = [](bool) {};
	
	public:

		CheckButton(sf::FloatRect size, const sf::Font& font, sf::String str = "+", bool stat = false) : Button(size, font, str) { btn_status = stat; }
		void bind(std::function<void(bool)> _callback) { m_callback = _callback; }
		void update(sf::RenderWindow&) override;
	};
}

