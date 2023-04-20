#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

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
    
    sf::Sprite walkingSprite(walkingTexture);
    walkingSprite.setScale(scaleX, scaleY);
    walkingSprite.setPosition(307*scaleX, 500);
    walkingSprite.setOrigin(307*scaleX, 0);
    sf::Sprite idleSprite(idleTexture);
    idleSprite.setScale(scaleX, scaleY);
    idleSprite.setPosition(scaleX * 614, 0);

    sf::Time animDuration = sf::seconds(1.f / 30.f);

    sfex::Animation walkingAnimation(walkingSprite, false);
    walkingAnimation.autoGenerateFrames({0, 0, 614, 564}, animDuration);

    sfex::Animation idleAnimation(idleSprite);
    idleAnimation.autoGenerateFrames({0, 0, 614, 564}, animDuration);
    idleAnimation.setAnimationSpeed(-0.5f);

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
            walkingAnimation.play();
            walkingSprite.setScale(scaleX, scaleY);
            walkingSprite.move({speedX, 0});
        }
        else if(sfex::Keyboard::getKey(sfex::Keyboard::Key::Left))
        {
            walkingAnimation.play();
            walkingSprite.setScale(-scaleX, scaleY);
            walkingSprite.move({-speedX, 0});
        }
        else walkingAnimation.pause();

        window.clear();
        window.draw(walkingSprite);
        window.draw(idleSprite);

        window.display();
    }

    return 0;
}
