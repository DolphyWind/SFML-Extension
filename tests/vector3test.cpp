#include <iostream>
#include <cassert>
#include <SFEX/Numeric/Vector3.hpp>

int main(int argc, char** argv)
{
    sfex::Vec3 v1(1, 2, 2);
    assert(v1.magnitude() == 3);
    v1.setMagnitude(6);
    assert(v1 == sfex::Vec3(2, 4, 4));
    assert(v1.normalized() == sfex::Vec3(1.f/3.f, 2.f/3.f, 2.f/3.f));
    v1.setMagnitude(3);
    assert(v1.dot(v1) == 9);
    assert(sfex::Vec3::right.cross(sfex::Vec3::up) == sfex::Vec3::forward);
    assert(v1.cwiseMul(v1) == sfex::Vec3(1, 4, 4));
    assert(v1.cwiseDiv(v1) == sfex::Vec3::one);
    assert(v1.scaled(2) == sfex::Vec3(2, 4, 4));
    assert(v1.projectedOnto(sfex::Vec3::right).x == 1);
    assert(v1.projectedOntoPlane(0, 0, 1) == sfex::Vec3(1, 2, 0));
    assert(v1.projectedOntoPlane(sfex::Vec3::up) == sfex::Vec3(1, 0, 2));
    assert(v1+v1 == sfex::Vec3(2, 4, 4));
    assert(v1-v1 == sfex::Vec3::zero);

    return 0;
}