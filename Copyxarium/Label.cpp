#include "Label.h"


using namespace gui;

Label::Label()
{
	text.setCharacterSize(20U);
	text.setFillColor(sf::Color::Black);

	m_string = nullptr;
}

Label::Label(sf::Vector2f pos, unsigned int size)
{
	text.setCharacterSize(size);
	
	m_string = nullptr;
	text.setFillColor(sf::Color::Black);
	text.setPosition(pos);

}

void Label::setFont(const sf::Font &font)
{
	text.setFont(font);
}

void Label::setString(sf::String str)
{
	m_string = nullptr;
	text.setString(str);
}

void Label::setColor(sf::Color color)
{
	text.setFillColor(color);
}

void gui::Label::setCharSize(unsigned int size)
{
	text.setCharacterSize(size);
}

void Label::setDynamicString(sf::String& str)
{
	m_string = &str;
	text.setString(*m_string);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform = getTransform();

	setOriginByAnchor((GObject*)this, target);
	target.draw(text, state);
}

void Label::update(sf::RenderWindow&)
{
	if (m_string)
		text.setString(*m_string);
}

