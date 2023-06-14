#include <SecondScene.hpp>

SecondScene::SecondScene()
{
    m_rectangle.setSize({50, 50});
    m_rectangle.setFillColor(sfex::Color::Blue);
    m_rectangleSpeed = 10.0f;
}

void SecondScene::start()
{
    m_rectangle.setPosition(sfex::Vec2::zero);
}

void SecondScene::pollEvent(const sf::Event &e)
{
    
}

void SecondScene::update()
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

void SecondScene::draw(sf::RenderTarget &target)
{
    target.draw(m_rectangle);
}

void SecondScene::destroy()
{
    std::cout << "Second scene got destroyed" << std::endl;
}
