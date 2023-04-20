#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

// Sprites are from https://www.gameart2d.com/the-boy---free-sprites.html

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Animations");
    window.setFramerateLimit(60);    

    constexpr float scaleX = 0.3f;
    constexpr float scaleY = 0.3f;
    constexpr float speedX = 5;

    sf::Texture walkingTexture;
    walkingTexture.loadFromFile("boy_sprite/Walk.png");
    sf::Texture idleTexture;
    idleTexture.loadFromFile("boy_sprite/Idle.png");
    
    sf::Sprite walkingSprite;
    walkingSprite.setScale(scaleX, scaleY);
    walkingSprite.setPosition(307*scaleX, 500);
    walkingSprite.setOrigin(307*scaleX, 0);

    sf::Time animDuration = sf::seconds(1.f / 30.f);

    sfex::Animation walkingAnimation(walkingSprite, walkingTexture, false);
    walkingAnimation.autoGenerateFrames({0, 0, 614, 564}, animDuration);

    sfex::Animation idleAnimation(walkingSprite, idleTexture, false);
    idleAnimation.autoGenerateFrames({0, 0, 614, 564}, animDuration);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        walkingAnimation.update();
        idleAnimation.update();

        if(sfex::Keyboard::getKey(sfex::Keyboard::Key::Right))
        {
            if(walkingAnimation.isPaused()) walkingAnimation.play();
            if(!idleAnimation.isPaused()) idleAnimation.pause();
            walkingSprite.setScale(scaleX, scaleY);
            walkingSprite.move({speedX, 0});
        }
        else if(sfex::Keyboard::getKey(sfex::Keyboard::Key::Left))
        {
            if(walkingAnimation.isPaused()) walkingAnimation.play();
            if(!idleAnimation.isPaused()) idleAnimation.pause();
            walkingSprite.setScale(-scaleX, scaleY);
            walkingSprite.move({-speedX, 0});
        }
        else
        {
            if(!walkingAnimation.isPaused()) walkingAnimation.pause();
            if(idleAnimation.isPaused()) idleAnimation.play();
        }

        window.clear();
        window.draw(walkingSprite);

        window.display();
    }

    return 0;
}
