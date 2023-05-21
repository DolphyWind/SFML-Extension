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
    
    sfex::Vector2<unsigned> textureSize = textureManager["lenna"].getSize();
    sfex::SpriteManager spriteManager;
    spriteManager.setTexture("lenna", textureManager.at("lenna"));
    
    spriteManager["lenna"].setOrigin(textureSize / 2);
    spriteManager["lenna"].setRotation(45);
    spriteManager["lenna"].setPosition(640, 360);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        window.clear();

        window.draw(spriteManager["lenna"]);

        window.display();
    }

    // Create some random textures to test some functonalities
    textureManager["ABC123"];
    textureManager["Hello"];
    textureManager["ILoveProgramming"];
    textureManager["I_Use_Arch_BTW"];
    textureManager["Texture"];
    textureManager["Sprite"];
    textureManager["THANKS_TO_SFML"];
    textureManager["AMONGUS_IS_SUS"];

    std::cout << "Size: " << textureManager.size() << std::endl;
    std::cout << "Filter (Startswith \'I\'): " << textureManager.filter("I", sfex::TextureManager::FilterType::Starts_with).size() << std::endl;
    std::cout << "Filter (Contains \'_\'): " << textureManager.filter("_", sfex::TextureManager::FilterType::Contains).size() << std::endl;
    std::cout << "Filter (Endswith \'e\'): " << textureManager.filter("e", sfex::TextureManager::FilterType::Ends_with).size() << std::endl;
    std::cout << "Filter (Does_not_contain \'e\'): " << textureManager.filter("e", sfex::TextureManager::FilterType::Does_not_contain).size() << std::endl;
    
    std::cout << "Removing ABC123" << std::endl;
    textureManager.remove("ABC123");
    std::cout << "New Size: " << textureManager.size() << std::endl;

    std::cout << "Removing everything that contains I" << std::endl;
    textureManager.remove(textureManager.filter("I", sfex::TextureManager::FilterType::Contains));
    std::cout << "New Size: " << textureManager.size() << std::endl;
    std::cout << std::boolalpha;

    std::cout << "Is empty?: " << textureManager.empty() << std::endl;
    std::cout << "All keys: ";
    for(auto &key : textureManager.keys())
    {
        std::cout << key << ", ";
    }
    std::cout << std::endl;

    return 0;
}
