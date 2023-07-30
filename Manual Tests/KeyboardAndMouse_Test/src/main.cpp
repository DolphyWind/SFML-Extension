#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(360, 360), "Input");
    window.setFramerateLimit(60);

    bool one_time = true;

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        if(sfex::Keyboard::getKeyDown(sfex::Keyboard::Key::Space))
        {
            std::cout << "Space key pressed!" << std::endl;
        }
        
        if(sfex::Keyboard::getKeyDown(sfex::Keyboard::Key::Space))
        {
            std::cout << "Space key pressed! You are using update based input handling." << std::endl;
        }

        if(sfex::Keyboard::getKeyUp(sfex::Keyboard::Key::Space))
        {
            std::cout << "Space key released!" << std::endl;
        }

        if(sfex::Keyboard::getKey(sfex::Keyboard::Key::Space))
        {
            std::cout << "Space key is being held down!" << std::endl;
        }

        if(sfex::Mouse::getButtonDown(sfex::Mouse::Button::Left))
        {
            std::cout << "Left mouse button pressed!" << std::endl;
        }
        if(sfex::Mouse::getButtonDown(sfex::Mouse::Button::Left))
        {
            std::cout << "Left mouse button pressed! You are using update based input handling." << std::endl;
        }

        if(sfex::Mouse::getButtonUp(sfex::Mouse::Button::Left))
        {
            std::cout << "Left mouse button released!" << std::endl;
        }

        if(sfex::Mouse::getButton(sfex::Mouse::Button::Left))
        {
            std::cout << "Left mouse button is being held down!" << std::endl;
        }

        sfex::Keyboard::update();
        sfex::Mouse::update();
        
        if(one_time)
        {
            one_time = false;
            sfex::Mouse::setPosition({100, 100}, &window);

            sfex::Vec2i pos_global = sfex::Mouse::getPosition();
            sfex::Vec2i pos_relative = sfex::Mouse::getPosition(&window);

            std::cout << "Global mouse position: (" << pos_global.x << ", " << pos_global.y << ")" << std::endl;
            std::cout << "Mouse position relative to window: (" << pos_relative.x << ", " << pos_relative.y << ")" << std::endl;
        }

        window.clear();

        window.display();
    }

    return 0;
}
