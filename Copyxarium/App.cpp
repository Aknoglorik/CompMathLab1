#include "App.h"
#include "ExtraColors.hpp"
#include <iostream>

#define GRAPH_MARGIN    20

#define HUD_WIDTH       200
#define HUD_MARGIN      20

#define CBTN_SIZE       30.f
#define CBTN_DEL        35.f
#define CBTN_HOR_POS    (HUD_WIDTH - HUD_MARGIN)

#define LB_FONT_SIZE    20U


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
    
    graph = new Graph(sf::Vector2f(VM.width - 2 * GRAPH_MARGIN - HUD_WIDTH, VM.height - 2 * GRAPH_MARGIN));
    widgets.push_back(graph);
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
                camera->view.zoom(1.1);
            }
            else if (event_.mouseWheelScroll.delta > 0)
            {
                camera->view.zoom(0.9);
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

    // hud
    root.setView(default_view);
    sf::RectangleShape background(sf::Vector2f(HUD_WIDTH, VM.height));
    background.setFillColor(gui::Color::DarkGray);
    background.setPosition(VM.width - HUD_WIDTH, 0);
    root.draw(background);

    for (auto wid : hud_widgets)
        root.draw(*wid);

    root.display();
}


void App::graphAdd(std::vector<sf::Vector2f>& grpah, sf::Color color, sf::String str, bool enable)
{
    sf::Vector2f pos(-CBTN_HOR_POS, hud_hbox_height*CBTN_DEL + HUD_MARGIN); // HBox pos
    ++hud_hbox_height;
    
    graph->add(grpah, color, enable);
    

    // Create CheckBtn
    gui::CheckButton* c_btn = new gui::CheckButton(sf::FloatRect(pos.x, pos.y, CBTN_SIZE, CBTN_SIZE), font);
    int* id = new int(graph->count());
    
    c_btn->setAnc(gui::TopRight);
    c_btn->bind([this, id](bool flag) { this->graph->setEnable(*id, !flag); });

    hud_widgets.push_back(c_btn);
    
    // Create label of CheckBtn
    gui::Label *lb = new gui::Label(pos + sf::Vector2f(CBTN_DEL, 0), LB_FONT_SIZE);

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

    gui::Label* lb = new gui::Label(pos + sf::Vector2f(CBTN_DEL, 0), LB_FONT_SIZE);

    lb->setFont(font);
    lb->setString(str);
    lb->setAnc(gui::TopRight);
    lb->setColor(gui::Color::DarkRed2);

    hud_widgets.push_back(lb);
}
