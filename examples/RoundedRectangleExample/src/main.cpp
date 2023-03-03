#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Rounded Square");
    window.setFramerateLimit(60);

    sf::Texture lennaTexture;
    if(!lennaTexture.loadFromFile("./lenna.png"))
    {
        std::cout << "ERROR: Cannot load \"lenna.png\"" << std::endl;
        return 1;
    }

    sfex::RoundedRectangle rect({200, 200}, 20);
    rect.setFillColor(sfex::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sfex::Color::White);
    rect.setPosition(200, 200);
    rect.setCornerPointCount(25);
    rect.setTexture(&lennaTexture);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        window.clear();

        window.draw(rect);

        window.display();
    }

    return 0;
}
