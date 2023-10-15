#include <iostream>
#include <cassert>
#include <cmath>
#include <SFEX/Numeric/Vector2.hpp>
#include <sstream>

int main(int argc, char* argv[])
{
    sfex::Vec2 v1(3, 4);
    assert(v1.magnitude() == 5);
    
    v1.setMagnitude(10);
    assert(v1 == sfex::Vec2(6, 8));
    assert(v1.normalized() == sfex::Vec2(0.6f, 0.8f));
 
    assert(sfex::Vec2i(v1) == sfex::Vec2i(v1.x, v1.y));

    v1 = sfex::Vec2(3, 4);
    sfex::Vec2 v2 = v1;
    assert(v1.dot(v2) == 25);

    assert(sfex::Vec2(3, 0).cross({0, 4}) == 12);
    
    assert(v1.cwiseMul(v2) == sfex::Vec2(9, 16));
    assert(v1.cwiseDiv(v2) == sfex::Vec2::one);
    assert(v1.scaled(2) == sfex::Vec2(6, 8));

    assert(v1.projectedOnto(sfex::Vec2::right) == sfex::Vec2(3, 0));
    assert(v1 + v2 == v2 + v1);
    assert(v1 - v1 == sfex::Vec2::zero);

    assert(2.f * v1 == sfex::Vec2(6, 8));
    assert(2.f * v1 == v1 * 2.f);
    assert(v1 / 10.f == sfex::Vec2(0.3, 0.4));
    assert(v1 != sfex::Vec2::one);

    std::stringstream ss;
    ss << v1;
    assert(ss.str() == std::string("(x: 3, y: 4)"));

    return 0;
}
