#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Shapes");
    window.setFramerateLimit(60);

    sfex::TextureManager textureManager;
    textureManager.loadFromFile("lenna", "lenna.png");
    
    sfex::Vector2<unsigned> textureSize = textureManager["lenna"]->getSize();
    sf::Sprite sprite(*textureManager["lenna"]);
    
    sprite.setOrigin(textureSize / 2);
    sprite.setRotation(45);
    sprite.setPosition(640, 360);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        window.clear();

        window.draw(sprite);

        window.display();
    }

    return 0;
}
