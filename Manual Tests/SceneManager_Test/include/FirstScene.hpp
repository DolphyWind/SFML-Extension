#ifndef _FIRST_SCENE_HPP_
#define _FIRST_SCENE_HPP_

#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>

class FirstScene : public sfex::Scene
{
public:
    FirstScene();

    virtual void handleEvent(const sf::Event &e) override;
    virtual void start() override;
    virtual void update(const sf::Time& deltaTime) override;
    virtual void render(sf::RenderTarget &target) override;
    virtual void destroy() override;

private:
    sf::RectangleShape m_rectangle;
    float m_rectangleSpeed;
};

#endif // !_FIRST_SCENE_HPP_
