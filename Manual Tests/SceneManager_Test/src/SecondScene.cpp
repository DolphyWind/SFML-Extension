#include <SecondScene.hpp>

SecondScene::SecondScene():
    sfex::Scene("second_scene")
{
    m_rectangle.setSize({50, 50});
    m_rectangle.setFillColor(sfex::Color::Blue);
    m_rectangleSpeed = 10.0f;
}

void SecondScene::start()
{
    m_rectangle.setPosition(sfex::Vec2::zero);
}

void SecondScene::onEvent(const sf::Event &e)
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

void SecondScene::lateUpdate()
{

}

void SecondScene::render(sf::RenderTarget &target)
{
    target.draw(m_rectangle);
}

void SecondScene::onDestroy()
{
    std::cout << "Second scene got destroyed" << std::endl;
}
