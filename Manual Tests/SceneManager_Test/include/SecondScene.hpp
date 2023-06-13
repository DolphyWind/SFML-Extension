#ifndef _SECOND_SCENE_HPP_
#define _SECOND_SCENE_HPP_

#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>

class SecondScene : public sfex::Scene
{
public:
    SecondScene();

    virtual void onEvent(const sf::Event &e) override;
    virtual void start() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render(sf::RenderTarget &target) override;
    virtual void onDestroy() override;

private:
    sf::RectangleShape m_rectangle;
    float m_rectangleSpeed;
};

#endif // !_SECOND_SCENE_HPP_
