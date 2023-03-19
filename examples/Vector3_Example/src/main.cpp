#include <SFEX/SFEX.hpp>
#include <iostream>

template<typename T>
void printVector(const sfex::Vector3<T> &vector, const std::string &name = std::string())
{
    std::cout << name << ": " << vector << std::endl;
}

void printDashes(std::size_t n = 30)
{
    std::cout << std::string(n, '-') << std::endl;
}

int main()
{
    sfex::Vec3 v = sfex::Vec3::right;
    printVector(v, "v");
    sfex::Vec3 rotated = v.rotated(0, sfex::Math::deg2rad(90), 0);
    printVector(rotated, "rotated");
    printDashes();

    printVector(sfex::Vec3::right.cross(sfex::Vec3::up), "rightxup");
    printDashes();

    

    return 0;
}
