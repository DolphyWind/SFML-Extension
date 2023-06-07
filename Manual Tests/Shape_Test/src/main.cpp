#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Shapes");
    window.setFramerateLimit(60);

    sf::Texture lennaTexture;
    if(!lennaTexture.loadFromFile("./lenna.png"))
    {
        std::cout << "ERROR: Cannot load \"lenna.png\"" << std::endl;
        return 1;
    }

    sfex::RoundedRectangle rect({200, 200}, 25);
    rect.setFillColor(sfex::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sfex::Color::White);
    rect.setPosition(200, 120);
    rect.setCornerPointCount(5);
    rect.setTexture(&lennaTexture);

    sfex::Ellipse ellipse(150, 100);
    ellipse.setOutlineThickness(2);
    ellipse.setOutlineColor(sfex::Color::White);
    ellipse.setPosition(800, 120);
    ellipse.setPointCount(60);
    ellipse.setTexture(&lennaTexture);

    sfex::Squircle squircle(100);
    squircle.setOutlineThickness(2);
    squircle.setOutlineColor(sfex::Color::White);
    squircle.setPointCount(60);
    squircle.setPosition(500, 120);
    squircle.setTexture(&lennaTexture);

    sfex::Star star;
    star.setInnerRadius(40);
    star.setOuterRadius(100);
    star.setOutlineThickness(2);
    star.setOutlineColor(sfex::Color::White);
    star.setPosition(300, 500);
    star.setTexture(&lennaTexture);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        window.clear();

        window.draw(rect);
        window.draw(squircle);
        window.draw(ellipse);
        window.draw(star);

        window.display();
    }

    return 0;
}
