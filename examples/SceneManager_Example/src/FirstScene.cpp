#include <FirstScene.hpp>

FirstScene::FirstScene()
{
    m_rectangle.setSize({50, 50});
    m_rectangle.setFillColor(sfex::Color::Red);
    m_rectangleSpeed = 10.0f;
}

void FirstScene::start()
{
    m_rectangle.setPosition(sfex::Vec2::zero);
}

void FirstScene::pollEvent(const sf::Event &e)
{
    
}

void FirstScene::update()
{
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::D))
    {
        m_rectangle.move({m_rectangleSpeed, 0});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::A))
    {
        m_rectangle.move({-m_rectangleSpeed, 0});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::W))
    {
        m_rectangle.move({0, -m_rectangleSpeed});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::S))
    {
        m_rectangle.move({0, m_rectangleSpeed});
    }
}

void FirstScene::draw(sf::RenderTarget &target)
{
    target.draw(m_rectangle);
}
