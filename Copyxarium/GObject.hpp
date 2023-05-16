#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace gui
{
	enum Anchor
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};


	class GObject : public sf::Drawable, public sf::Transformable
	{
	protected:
		Anchor _anchor = TopLeft;

	public:
		bool do_it_close = false;

		virtual ~GObject() {}

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override {}
		virtual void update(sf::RenderWindow&) {}
		virtual void setAnc(Anchor anc) { _anchor = anc; }
		virtual Anchor getAnc() { return _anchor; }
	};


	inline void setOriginByAnchor(GObject* obj, sf::RenderTarget& target)
	{
		sf::Vector2i t_size = (sf::Vector2i)target.getView().getSize();

		switch (obj->getAnc())
		{
		case TopLeft:
			obj->setOrigin(0, 0);
			break;
		case TopRight:
			obj->setOrigin(-t_size.x, 0);
			break;
		case BottomLeft:
			obj->setOrigin(0, -t_size.y);
			break;
		case BottomRight:
			obj->setOrigin(-t_size.x, -t_size.y);
			break;
		default:
			obj->setOrigin(0, 0);
			break;
		}
	}
}
