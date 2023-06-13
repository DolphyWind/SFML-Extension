#include <PlayerController.hpp>

PlayerController::PlayerController(sfex::GameObject* parent, const sfex::Color& color):
    sfex::GameComponent(parent, "Player Controller"), m_color(color)
{
    m_shape.setSize({50, 50});
    m_shape.setFillColor(m_color);
}

void PlayerController::start()
{
    m_shape.setPosition(sfex::Vec2::zero);
}

void PlayerController::onEvent(const sf::Event &e)
{
    
}

void PlayerController::update()
{
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::D))
    {
        m_shape.move({m_speed, 0});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::A))
    {
        m_shape.move({-m_speed, 0});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::W))
    {
        m_shape.move({0, -m_speed});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::S))
    {
        m_shape.move({0, m_speed});
    }
}

void PlayerController::lateUpdate()
{
    
}

void PlayerController::render(sf::RenderTarget &target)
{
    target.draw(m_shape);
}

void PlayerController::onDestroy()
{
    
}
