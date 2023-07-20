#ifndef _SECOND_SCENE_HPP_
#define _SECOND_SCENE_HPP_

#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>

class SecondScene : public sfex::Scene
{
public:
    SecondScene();

    virtual void handleEvent(const sf::Event &e) override;
    virtual void start() override;
    virtual void update(float deltaTime) override;
    virtual void draw(sf::RenderTarget &target) override;
    virtual void destroy() override;

private:
    sf::RectangleShape m_rectangle;
    float m_rectangleSpeed;
};

#endif // !_SECOND_SCENE_HPP_
