#include <SFEX/Numeric.hpp>
#include <iostream>

template<typename T>
void printVector(const sfex::Vector2<T> &vector, const std::string &name = std::string())
{
    std::cout << name << ": <" << vector.x << ", " << vector.y << ">" << std::endl;
}

void printDashes(std::size_t n = 30)
{
    for(std::size_t i = 0; i < n; i++) std::cout << "-";
    std::cout << std::endl;
}

int main()
{
    sfex::Vec2 v1 = {3, 4};
    printVector(v1, "v1");
    printDashes();

    std::cout << "Magnitude of v: " << v1.magnitude() << std::endl;
    printDashes();

    v1.setMagnitude(10);
    std::cout << "After setMagnitude(10);\n"; printVector(v1, "v1");
    printDashes();

    v1.normalize();
    std::cout << "After normalize();\n"; printVector(v1, "v1");
    printDashes();

    sfex::Vec2 v2 = {4, 5};
    printVector(v2, "v2");
    printDashes();

    printVector(v2.normalized(), "v2.normalized()");
    printDashes();

    std::cout << "v1.dot(v2): " << v1.dot(v2) << std::endl;
    std::cout << "v1.cross(v2): " << v1.cross(v2) << std::endl;
    printVector(v1.cwiseMul(v2), "v1.cwiseMul(v2)");
    printVector(v1.cwiseDiv(v2), "v1.cwiseDiv(v2)");
    printDashes();

    v2.scale(2);
    std::cout << "v2 after v2.scale(2);\n"; printVector(v2, "v2");
    printDashes();
    printVector(v1, "v1");
    printVector(v2, "v2");
    printVector(v1 + v2, "v1 + v2");
    printVector(v2 - v1, "v2 - v1");
    printVector(v2 / 2, "v2 / 2");
    printVector(-v2, "-v2");
    printDashes();

    v2 = {1.5, -9.22};
    printVector(v2, "v2");
    std::cout << "You can also convert sfex::Vector2<T> to sf::Vector2<T> or vice versa very easily!" << std::endl;
    std::cout << "Check the source code to understand this part better." << std::endl;
    sf::Vector2f vecf = v2;
    sf::Vector2i veci = v2;
    sf::Vector2u vecu = v2;
    printVector<float>(vecf, "vecf");
    printVector<int>(veci, "veci");
    printVector<unsigned int>(vecu, "vecu");

    printVector((v1=vecf), "v1=vecf");
    printVector((v1=veci), "v1=veci");
    printVector((v1=vecu), "v1=vecu");
    printDashes();

    std::cout << "Static const members." << std::endl;
    printVector(sfex::Vec2::one, "one");
    printVector(sfex::Vec2::zero, "zero");
    printVector(sfex::Vec2::up, "up");
    printVector(sfex::Vec2::down, "down");
    printVector(sfex::Vec2::left, "left");
    printVector(sfex::Vec2::right, "right");
    printDashes();

    v2 = sfex::Vec2::up;
    printVector(v2, "v2");
    printVector(v2.rotated(3.1415926535 / 2), "v2 rotated 90 degrees");
    printVector(v2.rotated(-3.1415926535 / 2), "v2 rotated -90 degrees");
    printVector(v2.rotated(3.1415926535), "v2 rotated 180 degrees");
    printVector(v2.rotated(3.1415926535 / 2, {-1, 0}), "v2 rotated 90 degrees around (-1, 0)");
    std::cout << "Angle of v2: " << v2.angle() << std::endl;
    std::cout << "Angle between v2 and <1, -1>: " << v2.angle({1, -1}) << std::endl;
    printDashes();
    sfex::Vec2 v_first = {1, 0};
    sfex::Vec2 v_second = {3, 4};
    printVector(v_first, "v_first");
    printVector(v_second, "v_second");
    printVector(v_first.projectedOnto(v_second), "v_first.projectedOnto(v_second)");

    return 0;
}
