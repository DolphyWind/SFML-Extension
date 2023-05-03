#include <iostream>
#include <cassert>
#include <SFEX/Managers/OptionManager.hpp>

int main()
{
    sfex::OptionValue val = 1;
    val = 98;
    assert(val.as_int() == 98);
    assert(val.as_double() == 0.0);
    assert(val.to_string() == std::string("98"));

    val = 0.5;
    assert(val.as_int() == 0);
    assert(val.as_double() == 0.5);
    assert(val.to_string() == std::string("0.5"));

    return 0;
}