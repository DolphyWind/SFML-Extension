#ifndef _SECOND_SCENE_HPP_
#define _SECOND_SCENE_HPP_

#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>

class SecondScene : public sfex::SceneBase
{
public:
    SecondScene();

    virtual void pollEvent(const sf::Event &e);
    virtual void start();
    virtual void update();
    virtual void draw(sf::RenderTarget &target);

private:
    sf::RectangleShape m_rectangle;
    float m_rectangleSpeed;
};

#endif // !_SECOND_SCENE_HPP_
