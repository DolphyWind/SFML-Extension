#include <SFEX/SFEX.hpp>
#include <iostream>

void printDashes(std::size_t n = 30)
{
    std::cout << std::string(n, '-') << std::endl;
}

int main()
{
    sfex::Gradient<sfex::Vec2> gradient;
    gradient[0] = sfex::Vec2::right;
    gradient[1] = sfex::Vec2::up;
    gradient[2] = sfex::Vec2::left;
    gradient[3] = sfex::Vec2::down;


    for(float i = 0; !sfex::Math::isClose(i, 3.1f, 0.01f); i += 0.1)
    {
        std::cout << "Gradient at t=" << i << ": " << gradient(i) << std::endl; 
    }
    printDashes();
    sfex::Gradient<sfex::Color> colorGradient;
    colorGradient.setKey(0, sfex::Color::Red);
    colorGradient.setKey(1, sfex::Color::Blue);

    for(float i = 0; !sfex::Math::isClose(i, 1.1f, 0.001f); i += 0.1)
    {
        std::cout << "Gradient at t=" << i << ": " << colorGradient(i) << std::endl;
    }
    
    return 0;
}
