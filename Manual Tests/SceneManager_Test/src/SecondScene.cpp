#include <SecondScene.hpp>

SecondScene::SecondScene()
{
    m_rectangle.setSize({50, 50});
    m_rectangle.setFillColor(sfex::Color::Blue);
    m_rectangleSpeed = 500.0f;
}

void SecondScene::start()
{
    m_rectangle.setPosition(sfex::Vec2::zero);
}

void SecondScene::handleEvent(const sf::Event &e)
{
    
}

void SecondScene::update(const sf::Time& deltaTime)
{
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::D))
    {
        m_rectangle.move({m_rectangleSpeed * deltaTime.asSeconds(), 0});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::A))
    {
        m_rectangle.move({-m_rectangleSpeed * deltaTime.asSeconds(), 0});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::W))
    {
        m_rectangle.move({0, -m_rectangleSpeed * deltaTime.asSeconds()});
    }
    if(sfex::Keyboard::getKey(sfex::Keyboard::Key::S))
    {
        m_rectangle.move({0, m_rectangleSpeed * deltaTime.asSeconds()});
    }
}

void SecondScene::render(sf::RenderTarget &target)
{
    target.draw(m_rectangle);
}

void SecondScene::destroy()
{
    std::cout << "Second scene got destroyed" << std::endl;
}
