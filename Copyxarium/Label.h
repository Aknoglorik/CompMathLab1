#pragma once

#include "GObject.hpp"
#include <SFML/Graphics.hpp>


namespace sf
{
	template <class T>
	class Vector2;
	typedef Vector2<float> Vector2f;

	class String;
	class Font;
	class Text;
	class Color;
}


namespace gui
{
	
	class Label : public GObject
	{
		sf::Vector2f pos;
		sf::String* m_string;
		sf::Text text;

	public:
		Label();
		Label(sf::Vector2f, unsigned int size);

		void setFont(const sf::Font &);
		void setString(sf::String);
		void setColor(sf::Color);
		void setCharSize(unsigned int size);

		float getCharSizeF() { return text.getCharacterSize(); }

		/// \param str - string that can be changed outside this method 
		///		 CANN'T BE DELETED EARLIER THAN THIS ENTITY!
		void setDynamicString(sf::String& str);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&) override;
	};

}

