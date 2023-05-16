#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#define CAM_SPEED 20.f


namespace gui
{
	class Camera
	{
	public:
		Camera(sf::View& cam) : view(cam) {}
		Camera(sf::FloatRect rect) { view = sf::View(rect); }
		
		void zoom(float val)
		{
			_zoom *= val;
			view.zoom(val);
		}

		void moveUp(bool flag)
		{
			up = flag;
		}

		void moveLeft(bool flag)
		{
			left = flag;
		}

		void moveDown(bool flag)
		{
			down = flag;
		}

		void moveRight(bool flag)
		{
			right = flag;
		}

		void move()
		{
			sf::Vector2f offset((float)(right - left), (float)(down - up));
			offset *= speed * _zoom;

			view.move(offset);
		}

		sf::View view;
		float speed = CAM_SPEED;

	private:
		float _zoom = 1;
		bool up = false;
		bool left = false;
		bool down = false;
		bool right = false;
	};
}
