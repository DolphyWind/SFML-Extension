#include <FirstScene.hpp>

FirstScene::FirstScene():
    sfex::Scene("first_scene"), m_player(nullptr, "player")
{
    m_player.addComponent<PlayerController>(sfex::Color::Red);
}

void FirstScene::start()
{
    sfex::Scene::start();
    m_player.start();
}

void FirstScene::onEvent(const sf::Event &e)
{
    sfex::Scene::onEvent(e);
    m_player.onEvent(e);
}

void FirstScene::update()
{
    sfex::Scene::update();
    m_player.update();
}

void FirstScene::lateUpdate()
{
    sfex::Scene::lateUpdate();
}

void FirstScene::render(sf::RenderTarget &target)
{
    sfex::Scene::render(target);
    m_player.render(target);
}

void FirstScene::onDestroy()
{
    sfex::Scene::onDestroy();

    //m_player.removeComponent();
    std::cout << "First scene got destroyed!" << std::endl;
}
