#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Graphical");
    window.setFramerateLimit(60);

    sfex::TextureManager textureManager;
    textureManager.loadFromFile("lenna", "lenna.png");
    textureManager.loadFromFile("lenna_inverted", "lenna_inverted.png");
    
    sfex::Vector2<unsigned> textureSize = textureManager["lenna"]->getSize();
    sfex::SpriteManager spriteManager;
    spriteManager.setTexture("lenna", *textureManager.get("lenna"));
    
    spriteManager.get("lenna")->setOrigin(textureSize / 2);
    spriteManager.get("lenna")->setRotation(45);
    spriteManager.get("lenna")->setPosition(640, 360);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        window.clear();

        window.draw(*spriteManager.get("lenna"));

        window.display();
    }

    return 0;
}
