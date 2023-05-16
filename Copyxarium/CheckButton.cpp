#include "CheckButton.h"
#include "Label.h"

void gui::CheckButton::update(sf::RenderWindow& target)
{
    sf::Vector2i m_pos = sf::Mouse::getPosition(target);
    
    label->update(target);
    bool isClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    sf::Vector2f pos = target.mapPixelToCoords(m_pos);

    setOriginByAnchor((GObject*)this, target);
    if (label)
        label->setOrigin(this->getOrigin());

    size.left = getPosition().x - getOrigin().x;
    size.top = getPosition().y - getOrigin().y;

    if (isPressed)
    {
        if (!isClick)
            isPressed = false;
        if (multi_click)
            m_callback(btn_status);
        return;
    }

    if (size.contains(pos))
    {
        if (!isClick)
            isClickedOnThis = true;
        if (isClick && isClickedOnThis)
        {
            isPressed = true;
            btn_status = !btn_status;
            setByStat((btn_status)? _status::_clicked : _status::_default);
            m_callback(btn_status);
        }
        else if (!btn_status)
        {
            setByStat(_status::_hovered);
        }

    }
    else
    {
        if (isClick)
            isClickedOnThis = false;
        setByStat((btn_status) ? _status::_clicked : _status::_default);
    }
}
