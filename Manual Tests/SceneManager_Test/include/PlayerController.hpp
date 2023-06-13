#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_
#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>

class PlayerController : public sfex::GameComponent
{
public:
    PlayerController(sfex::GameObject* parent, const sfex::Color& color);

    virtual void onEvent(const sf::Event &e) override;
    virtual void start() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render(sf::RenderTarget &target) override;
    virtual void onDestroy() override;
private:
    sfex::Color m_color;
    sf::RectangleShape m_shape;
    float m_speed = 10.0f;
};

#endif // !_SQUARE_HPP_