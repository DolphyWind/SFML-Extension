#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(360, 360), "Input");
    window.setFramerateLimit(60);

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
            std::cout << "Left button pressed!" << std::endl;
        }

        if(sfex::Mouse::getButtonUp(sfex::Mouse::Button::Left))
        {
            std::cout << "Left button released!" << std::endl;
        }

        if(sfex::Mouse::getButton(sfex::Mouse::Button::Left))
        {
            std::cout << "Left button is being held down!" << std::endl;
        }

        window.clear();

        window.display();
    }

    return 0;
}
