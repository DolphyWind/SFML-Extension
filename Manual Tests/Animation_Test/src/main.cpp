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
    constexpr float runspeedX = 7;
    float currentSpeedX = speedX;

    sf::Texture walkingTexture;
    walkingTexture.loadFromFile("boy_sprite/Walk.png");
    sf::Texture idleTexture;
    idleTexture.loadFromFile("boy_sprite/Idle.png");
    sf::Texture runTexture;
    runTexture.loadFromFile("boy_sprite/Run.png");
    
    sf::Sprite playerSprite;
    playerSprite.setScale(scaleX, scaleY);
    playerSprite.setPosition(307*scaleX, 500);
    playerSprite.setOrigin(307*scaleX, 0);

    sf::Time animDuration = sf::seconds(1.f / 30.f);

    sfex::Animation walkingAnimation(playerSprite, walkingTexture, true);
    walkingAnimation.autoGenerateFrames({0, 0, 614, 564}, animDuration);
    
    sfex::Animation idleAnimation(playerSprite, idleTexture, true);
    idleAnimation.autoGenerateFrames({0, 0, 614, 564}, animDuration);

    sfex::Animation runAnimation(playerSprite, runTexture, true);
    runAnimation.autoGenerateFrames({0, 0, 614, 564}, animDuration);
    
    sfex::AnimationManager playerAnimationManager;
    playerAnimationManager.addAnimation("walk", walkingAnimation);
    playerAnimationManager.addAnimation("idle", idleAnimation);
    playerAnimationManager.addAnimation("run", runAnimation);
    
    // runAnimation.play();
    sf::Clock timer;
    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }
        sf::Time deltaTime = timer.restart();
        if(!window.hasFocus()) continue;

        playerAnimationManager.update(deltaTime);

        if(sfex::Keyboard::getKey(sfex::Keyboard::Key::Right))
        {
            if(sfex::Keyboard::getKey(sfex::Keyboard::Key::LShift))
            {
                playerAnimationManager.play("run");
                currentSpeedX = runspeedX;
            }
            else
            {
                playerAnimationManager.play("walk");
                currentSpeedX = speedX;
            }

            playerSprite.setScale(scaleX, scaleY);
            playerSprite.move({currentSpeedX, 0});
        }
        else if(sfex::Keyboard::getKey(sfex::Keyboard::Key::Left))
        {
            if(sfex::Keyboard::getKey(sfex::Keyboard::Key::LShift))
            {
                playerAnimationManager.play("run");
                currentSpeedX = runspeedX;
            }
            else
            {
                playerAnimationManager.play("walk");
                currentSpeedX = speedX;
            }

            playerSprite.setScale(-scaleX, scaleY);
            playerSprite.move({-currentSpeedX, 0});
        }
        else
        {
            playerAnimationManager.play("idle");
        }

        window.clear();
        window.draw(playerSprite);

        window.display();
    }

    return 0;
}
