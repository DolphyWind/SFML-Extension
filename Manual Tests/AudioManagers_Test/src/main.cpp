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

    sf::Keyboard::Key toggleKey = sfex::Keyboard::Key::Space;
    sf::Keyboard::Key jumpkey = sfex::Keyboard::Key::Up;

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }

        if(sfex::Keyboard::getKeyDown(toggleKey))
        {
            if(musicManager.getStatus("mainmusic") == sf::Music::Status::Playing)
                musicManager.pause("mainmusic");
            else musicManager.play("mainmusic");
        }
        
        if(sfex::Keyboard::getKeyDown(jumpkey))
        {
            soundManager.play("jump");
        }

        window.clear();

        window.display();
        sfex::Keyboard::update();
    }

    return 0;
}
