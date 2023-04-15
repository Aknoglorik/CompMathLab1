#include "App.h"
#include "ExtraColors.hpp"
#include "Graph.h"
#include "CheckButton.h"
#include "Slider.h"
#include "Label.h"
#include "Camera.hpp"
#include <iostream>

#define GRAPH_MARGIN    20

#define HUD_WIDTH       300
#define HUD_MARGIN      20

#define STATBAR_HEIGHT  40.f
#define STATBAR_MARGIN  10.f
#define STATBAR_DEL     120.f

#define CBTN_SIZE       30.f
#define CBTN_DEL        35.f
#define CBTN_HOR_POS    (HUD_WIDTH - HUD_MARGIN)

#define LB_FONT_SIZE    20U

#define SLD_MAX_VAL     100.f
#define SLD_MIN_VAL     0.1f
#define SLD_START_VAL   1.f


App::App(unsigned int width, unsigned int height, std::string wname)
{
    initWindow(width, height, wname);
    initVariables();
}

App::~App()
{
    delete camera;

    for (auto wid : widgets)
        delete wid;
    widgets.clear();
    
    for (auto wid : hud_widgets)
        delete wid;
    hud_widgets.clear();
}

// Initializers
void App::initWindow(unsigned int width, unsigned int height, std::string wname)
{
    VM.width = width;
    VM.height = height;

    isFullscreen = false;
    
    root.create(VM, wname, 7U, sf::ContextSettings(0, 0, 7));
    root.setFramerateLimit(60);

    camera = new gui::Camera(sf::FloatRect(0, 0, width * height / height, height));
    default_view = sf::View(sf::FloatRect(0, 0, width, height));

}

void App::initVariables()
{
    font.loadFromFile("res/pxlfont.ttf");
    graph = nullptr;

    hud_hbox_height = 0;
    
    graph = new Graph(sf::Vector2f(VM.width - 2 * GRAPH_MARGIN - HUD_WIDTH, VM.height - 2 * GRAPH_MARGIN - STATBAR_HEIGHT));
    widgets.push_back(graph);
    graph->setPosition(sf::Vector2f(GRAPH_MARGIN, GRAPH_MARGIN));

    // Side menu
    sf::Vector2f pos;
    gui::Label* lb;

    // Sliders
    {
    pos = sf::Vector2f(-CBTN_HOR_POS, hud_hbox_height * CBTN_DEL + HUD_MARGIN); // HBox pos
    ++hud_hbox_height;

    gui::Slider* sld = new gui::Slider(pos, sf::Vector2f(HUD_WIDTH - 2*HUD_MARGIN, HUD_MARGIN), SLD_START_VAL, SLD_MIN_VAL, SLD_MAX_VAL);

    sld->setValue(1);
    sld->setAnc(gui::TopRight);
    sld->bind([this](float x_factor) {this->graph->setFactor(sf::Vector2f(x_factor, this->graph->getFactor().y)); });

    hud_widgets.push_back(sld);

    pos = sf::Vector2f(-CBTN_HOR_POS, hud_hbox_height * CBTN_DEL + HUD_MARGIN); // HBox pos
    ++hud_hbox_height;

    lb = new gui::Label;
    lb->setCharSize(LB_FONT_SIZE);
    lb->setPosition(pos);// sf::Vector2f(STATBAR_MARGIN, -lb->getCharSizeF() - STATBAR_MARGIN));

    lb->setFont(font);
    lb->setDynamicString(d_slider_x_factor);
    lb->setAnc(gui::TopRight);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);
    }

    addHBoxSeparate();

    pos = sf::Vector2f(-CBTN_HOR_POS, hud_hbox_height * CBTN_DEL + HUD_MARGIN); // HBox pos
    ++hud_hbox_height;
    lb = new gui::Label(pos + sf::Vector2f(CBTN_DEL, 0), LB_FONT_SIZE);

    lb->setFont(font);
    lb->setString("Graph Dot Enabel");
    lb->setAnc(gui::TopRight);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);

    gui::CheckButton* c_btn = new gui::CheckButton(sf::FloatRect(pos.x, pos.y, CBTN_SIZE, CBTN_SIZE), font, "+", true);

    c_btn->setAnc(gui::TopRight);
    c_btn->bind([this](bool flag) { this->graph->setGraphsDotEnable(flag); });

    hud_widgets.push_back(c_btn);


    // status bar
    {
    lb = new gui::Label;
    lb->setCharSize(LB_FONT_SIZE);
    lb->setPosition(sf::Vector2f(STATBAR_MARGIN, -lb->getCharSizeF() - STATBAR_MARGIN));
    
    lb->setFont(font);
    lb->setDynamicString(d_mouse_pos_x);
    lb->setAnc(gui::BottomLeft);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);

    lb = new gui::Label;
    lb->setCharSize(LB_FONT_SIZE);
    lb->setPosition(sf::Vector2f(STATBAR_DEL + STATBAR_MARGIN, -lb->getCharSizeF() - STATBAR_MARGIN));

    lb->setFont(font);
    lb->setDynamicString(d_mouse_pos_y);
    lb->setAnc(gui::BottomLeft);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);
    }
}

bool App::isOpen()
{
    return root.isOpen();
}


void App::pollEvent()
{
    while (root.pollEvent(event_))
    {
        switch (event_.type)
        {
        case sf::Event::Closed:
            root.close();
            break;
        case sf::Event::KeyPressed:
        {
            auto pressed_key = event_.key.code;

            if (pressed_key == sf::Keyboard::Escape)
                root.close();
            if (pressed_key == sf::Keyboard::F11)
            {
                root.close();
                root.create(VM, "", (isFullscreen) ? sf::Style::Default : sf::Style::Fullscreen, sf::ContextSettings(0, 0, 7));

                isFullscreen = !isFullscreen;
            }
            if(pressed_key == sf::Keyboard::W)
                camera->moveUp(true);
            if (pressed_key == sf::Keyboard::A)
                camera->moveLeft(true);
            if (pressed_key == sf::Keyboard::S)
                camera->moveDown(true);
            if (pressed_key == sf::Keyboard::D)
                camera->moveRight(true);
            break;
        }
        case sf::Event::KeyReleased:
        {
            auto released_key = event_.key.code;
            if (released_key == sf::Keyboard::W)
                camera->moveUp(false);
            if (released_key == sf::Keyboard::A)
                camera->moveLeft(false);
            if (released_key == sf::Keyboard::S)
                camera->moveDown(false);
            if (released_key == sf::Keyboard::D)
                camera->moveRight(false);
            break;
        }
        case sf::Event::MouseWheelScrolled:
        {
            if (event_.mouseWheelScroll.delta < 0)
            {
                camera->zoom(1.1);
                graph->factorLinesThick(1.1);
            }
            else if (event_.mouseWheelScroll.delta > 0)
            {
                camera->zoom(0.9);
                graph->factorLinesThick(0.9);
            }
            break;
        }
        case sf::Event::Resized:
        {
            default_view = sf::View(sf::FloatRect(0, 0, event_.size.width, event_.size.height));
            break;
        }
        }
    }
}

void App::update()
{
    pollEvent();
    camera->move();

    auto m_pos = sf::Mouse::getPosition(root);
    auto pos = root.mapPixelToCoords(m_pos, camera->view);

    auto g_pos = graph->getPosition();
    auto delta = graph->getOrigin();
    auto factor = graph->getFactor();
    pos += delta - g_pos;

    d_mouse_pos_x = std::to_string(pos.x / factor.x);
    d_mouse_pos_y = std::to_string(pos.y / -factor.y);
    size_t _pos = 0;
    _pos = d_mouse_pos_x.find('.', _pos);
    
    d_mouse_pos_x = "x: " + d_mouse_pos_x.substring(0, d_mouse_pos_x.find(".") + 5);
    d_mouse_pos_y = "y: " + d_mouse_pos_y.substring(0, d_mouse_pos_y.find(".") + 5);

    d_slider_x_factor = "x factor = " + std::to_string(graph->getFactor().x);

    for (auto wid : widgets)
        wid->update(root);
    for (auto wid : hud_widgets)
        wid->update(root);
}

void App::render()
{
    root.clear(sf::Color(220, 220, 220));

    // Graph
    root.setView(camera->view);
    for (auto wid : widgets)
        root.draw(*wid);


    root.setView(default_view);

    // hud
    sf::RectangleShape hud_background(sf::Vector2f(HUD_WIDTH, root.getSize().y));
    hud_background.setFillColor(gui::Color::DarkGray);
    hud_background.setPosition(default_view.getSize().x - HUD_WIDTH, 0);
    root.draw(hud_background);

    // status bar
    sf::RectangleShape sbar_background(sf::Vector2f(root.getSize().x, STATBAR_HEIGHT));
    sbar_background.setFillColor(sf::Color::White);
    sbar_background.setPosition(0, default_view.getSize().y - STATBAR_HEIGHT);
    root.draw(sbar_background);

    for (auto wid : hud_widgets)
        root.draw(*wid);

    root.display();
}


void App::graphAdd(std::vector<sf::Vector2f>& grpah, sf::Color color, sf::String str, bool enable)
{
    sf::Vector2f pos(-CBTN_HOR_POS, hud_hbox_height*CBTN_DEL + HUD_MARGIN); // HBox pos
    ++hud_hbox_height;
    
    int* id = new int(graph->count());
    graph->addGraph(grpah, color, enable);
    

    // Create CheckBtn
    gui::CheckButton* c_btn = new gui::CheckButton(sf::FloatRect(pos.x, pos.y, CBTN_SIZE, CBTN_SIZE), font, "+", true);
    
    c_btn->setAnc(gui::TopRight);
    c_btn->bind([this, id](bool flag) { this->graph->setEnable(*id, flag); });

    hud_widgets.push_back(c_btn);
    
    // Create label of CheckBtn
    gui::Label *lb = new gui::Label(pos + sf::Vector2f(CBTN_DEL, 0), LB_FONT_SIZE);

    lb->setFont(font);
    lb->setString(str);
    lb->setAnc(gui::TopRight);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);
}

void App::pointsAdd(std::vector<sf::Vector2f>& points, sf::String str)
{
    sf::Vector2f pos(-CBTN_HOR_POS, hud_hbox_height * CBTN_DEL + HUD_MARGIN); // HBox pos
    ++hud_hbox_height;

    graph->addPoints(points);


    // Create CheckBtn
    gui::CheckButton* c_btn = new gui::CheckButton(sf::FloatRect(pos.x, pos.y, CBTN_SIZE, CBTN_SIZE), font, "+", true);

    c_btn->setAnc(gui::TopRight);
    c_btn->bind([this](bool flag) { this->graph->setDotEnable(flag); });

    hud_widgets.push_back(c_btn);

    // Create label of CheckBtn
    gui::Label* lb = new gui::Label(pos + sf::Vector2f(CBTN_DEL, 0), LB_FONT_SIZE);

    lb->setFont(font);
    lb->setString(str);
    lb->setAnc(gui::TopRight);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);
}

void App::addHBoxSeparate(sf::String str)
{
    sf::Vector2f pos(-CBTN_HOR_POS, hud_hbox_height * CBTN_DEL + HUD_MARGIN); // HBox pos
    ++hud_hbox_height;

    gui::Label* lb = new gui::Label(pos + sf::Vector2f(CBTN_DEL/2, 0), LB_FONT_SIZE);

    lb->setFont(font);
    lb->setString(str);
    lb->setAnc(gui::TopRight);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);
}
