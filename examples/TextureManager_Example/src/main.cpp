#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Shapes");
    window.setFramerateLimit(60);

    sfex::TextureManager textureManager;
    textureManager.loadFromFile("lenna", "lenna.png");
    
    sfex::Vector2<unsigned> textureSize = textureManager.getTexture("lenna").getSize();
    textureManager.getSprite("lenna").setOrigin(textureSize / 2);
    textureManager.getSprite("lenna").setRotation(45);
    textureManager.getSprite("lenna").setPosition(640, 360);
    

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        window.clear();

        window.draw(textureManager.getSprite("lenna"));

        window.display();
    }

    return 0;
}
