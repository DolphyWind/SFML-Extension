#include <FirstScene.hpp>

FirstScene::FirstScene()
{
    m_rectangle.setSize({50, 50});
    m_rectangle.setFillColor(sfex::Color::Red);
    m_rectangleSpeed = 500.0f;
}

void FirstScene::start()
{
    m_rectangle.setPosition(sfex::Vec2::zero);
}

void FirstScene::handleEvent(const sf::Event &e)
{
    
}

void FirstScene::update(const sf::Time& deltaTime)
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

void FirstScene::render(sf::RenderTarget &target)
{
    target.draw(m_rectangle);
}

void FirstScene::destroy()
{
    std::cout << "First scene got destroyed!" << std::endl;
}
