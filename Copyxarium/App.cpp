#include "App.h"


App::App(unsigned int width, unsigned int height, std::string wname)
{
    initVariables();
    initWindow(width, height, wname);
}

App::~App()
{

}

// Initializers
void App::initWindow(unsigned int width, unsigned int height, std::string wname)
{
    VM.width = width;
    VM.height = height;

    root.create(VM, wname, 7U, sf::ContextSettings(0, 0, 7));
}

void App::initVariables()
{
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
        }
    }
}




void App::update()
{


    pollEvent();

}



void App::render()
{
    root.clear();

    root.display();
}