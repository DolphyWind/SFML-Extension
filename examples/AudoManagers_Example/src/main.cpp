#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

// Sounds used
// https://freesound.org/people/ShadyDave/sounds/325647/
// https://freesound.org/people/Lefty_Studios/sounds/369515/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio");
    window.setFramerateLimit(60);

    sfex::MusicManager musicManager;
    if(!musicManager.openFromFile("mainmusic", "music.wav"))
    {
        std::cerr << "Cannot open music.wav" << std::endl;
        return 1;
    }
    musicManager.play("mainmusic");

    sfex::SoundManager soundManager;
    if(!soundManager.loadFromFile("jump", "jump.ogg"))
    {
        std::cerr << "Cannot open jump.ogg" << std::endl;
        return 1;
    }

    sf::SoundBuffer buff;
    buff.loadFromFile("jump.ogg");

    sf::Sound sound(buff);

    sf::Keyboard::Key toggleKey = sf::Keyboard::Key::Space;
    bool isToggleKeyPressed = false;

    sf::Keyboard::Key jumpkey = sf::Keyboard::Key::Up;
    bool isJumpKeyPressed = false;

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        if(sf::Keyboard::isKeyPressed(toggleKey) && !isToggleKeyPressed)
        {
            if(musicManager.getStatus("mainmusic") == sf::Music::Status::Playing)
                musicManager.pause("mainmusic");
            else musicManager.play("mainmusic");
            isToggleKeyPressed = true;
        }
        
        if(sf::Keyboard::isKeyPressed(jumpkey) && !isJumpKeyPressed)
        {
            soundManager.play("jump");
            isJumpKeyPressed = true;
        }


        isToggleKeyPressed = sf::Keyboard::isKeyPressed(toggleKey);
        isJumpKeyPressed = sf::Keyboard::isKeyPressed(jumpkey);
        window.clear();

        window.display();
    }

    return 0;
}
