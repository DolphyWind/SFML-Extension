#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFEX/Graphics/Color.hpp>

void printDashes(std::size_t n = 30)
{
    for(std::size_t i = 0; i < n; i++) std::cout << '-';
    std::cout << std::endl;
}

void printVector(const sfex::Vec2 &v, const std::string &name = std::string())
{
    std::cout << name << ": <" << v.x << ", " << v.y << ">" << std::endl;
}

void printColor(const sf::Color &c, const std::string &name = std::string())
{
    std::cout << name << ": (" << +c.r << ", " << +c.g << ", " << +c.b << ", " << +c.a << ")" << std::endl;
}

int main()
{
    sfex::Gradient<sfex::Vec2> gradient;
    gradient.setKey(0, sfex::Vec2::right);
    gradient.setKey(1, sfex::Vec2::up);
    gradient.setKey(2, sfex::Vec2::left);
    gradient.setKey(3, sfex::Vec2::down);

    for(float i = 0; !sfex::Math::isClose(i, 3.1f, 0.01f); i += 0.1)
    {
        printVector(gradient.evaluate(i), std::string("Gradient at t=") + std::to_string(i));
    }
    printDashes();
    sfex::Gradient<sfex::Color> colorGradient;
    colorGradient.setKey(0, sfex::Color::Red);
    colorGradient.setKey(1, sfex::Color::Blue);

    for(float i = 0; !sfex::Math::isClose(i, 1.1f, 0.001f); i += 0.1)
    {
        printColor(colorGradient.evaluate(i), std::string("Gradient at t=") + std::to_string(i));
    }

    return 0;
}
