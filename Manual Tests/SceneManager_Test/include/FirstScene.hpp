#ifndef _FIRST_SCENE_HPP_
#define _FIRST_SCENE_HPP_

#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>

class FirstScene : public sfex::Scene
{
public:
    FirstScene();

    virtual void pollEvent(const sf::Event &e);
    virtual void start();
    virtual void update();
    virtual void draw(sf::RenderTarget &target);
    virtual void destroy();

private:
    sf::RectangleShape m_rectangle;
    float m_rectangleSpeed;
};

#endif // !_FIRST_SCENE_HPP_
