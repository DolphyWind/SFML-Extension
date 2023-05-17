#include <iostream>
#include <cassert>
#include <SFEX/Managers/OptionManager.hpp>

int main()
{
    sfex::Multitype val = 1;
    val = 98;
    assert(val.as_int() == 98);
    assert(val.as_double() == 0.0);
    assert(val.to_string() == std::string("98"));

    val = 0.5;
    assert(val.as_int() == 0);
    assert(val.as_double() == 0.5);
    assert(val.to_string() == std::string("0.5"));

    assert(sfex::Multitype::null == sfex::Multitype::null);
    assert(sfex::Multitype::null != val);

    try
    {
        bool x = (sfex::Multitype::null < val);
        assert(false);
    } catch (const std::runtime_error &e)
    {
        assert(true);
    }

    sfex::Multitype value = std::vector<sfex::Multitype>{"Hello!", 2, 3, false, 3.14, std::vector<sfex::Multitype>{1, "World!", 6.28, true}};
    assert(value.as_list()[1] * value.as_list()[2] == 6);
    std::cout << value.to_string() << std::endl;

    sfex::Multitype val1 = 7;
    sfex::Multitype val2 = 9;

    assert(val1 < val2);
    assert(val1 != val2);
    assert(val2 > val1);
    assert(val1 <= val1);
    assert(val1 >= val1);

    val = 50;
    val *= 2;
    assert(val + val == 200);
    assert(val == 100);
    assert(val * 3 == 300);
    assert(val / 2 == 50);

    try
    {
        val *= sfex::Multitype::null;
        assert(false);
    }
    catch (const std::runtime_error &e)
    {
        assert(true);
    }

    return 0;
}