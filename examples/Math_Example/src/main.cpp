#include <SFEX/SFEX.hpp>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

void printDashes(std::size_t n = 30)
{
    for(std::size_t i = 0; i < n; i++) std::cout << '-';
    std::cout << std::endl;
}

void printVector(const sfex::Vec2 &v, const std::string &name = std::string())
{
    std::cout << name << ": <" << v.x << ", " << v.y << ">" << std::endl;
}

int main()
{
    std::cout << "180 degrees to radians: " << sfex::Math::deg2rad(180) << std::endl;
    std::cout << "pi radians to degrees: " << sfex::Math::rad2deg(sfex::Math::pi) << std::endl;
    printDashes();

    sfex::Vec2 v = sfex::Math::lerp(sfex::Vec2::down, sfex::Vec2::one, 0.4f);
    printVector(sfex::Vec2::down, "down");
    printVector(sfex::Vec2::one, "one");
    printVector(v, "lerp(down, one, 0.4)");
    printDashes();

    std::vector<sfex::Vec2> points = {
        sfex::Vec2(1, 1),
        sfex::Vec2(5, 6),
        sfex::Vec2(6, 1.5),
        sfex::Vec2(7.5, 7),
    };
    std::cout << "BEZIER POINTS" << std::endl;
    for(std::size_t i = 0; i < points.size(); i++)
        printVector(points[i], std::string("P") + std::to_string(i));

    for(int i = 0; i <= 10; i ++)
    {
        float t = float(i) / 10.0f;
        sfex::Vec2 point = sfex::Math::bezier(
            points,
            t,
            true
        );
        printVector(point, std::string("Bezier curve at t=") + std::to_string(t).substr(0, 3));
    }
    printDashes();
    
    
    return 0;
}
