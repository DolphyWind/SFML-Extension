#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "Waiting for a joystick connection..." << std::endl;
    while(!sfex::Joystick::isConnected(0)) sfex::Joystick::update();
    std::cout << "Connection successfull!" << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Joystick");
    window.setFramerateLimit(60);

    sf::RectangleShape rectangle({10, 10});
    rectangle.setOrigin((sfex::Vec2)rectangle.getSize() / 2);
    rectangle.setPosition((sfex::Vec2u)window.getSize() / 2);
    const float speed = 25.0f;

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        if(sfex::Joystick::getButtonDown(0, 0))
        {
            std::cout << "0 button is down!" << std::endl;
        }

        if(sfex::Joystick::getButtonDown(0, 0))
        {
            std::cout << "0 button is down! You are using update based input handling." << std::endl;
        }

        if(sfex::Joystick::getButton(0, 0))
        {
            std::cout << "0 button is preessed!" << std::endl;
        }

        if(sfex::Joystick::getButtonUp(0, 0))
        {
            std::cout << "0 button is up!" << std::endl;
        }

        float horizontal = sfex::Joystick::getAxisPosition(0, sfex::Joystick::Axis::X, 0.3f) * speed;
        float vertical = sfex::Joystick::getAxisPosition(0, sfex::Joystick::Axis::Y, 0.3f) * speed;
        
        rectangle.move({horizontal, vertical});

        sfex::Joystick::update();
        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
