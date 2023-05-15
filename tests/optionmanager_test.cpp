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

    assert(sfex::OptionValue::null == sfex::OptionValue::null);
    assert(sfex::OptionValue::null != val);

    try
    {
        bool x = (sfex::OptionValue::null < val);
        assert(false);
    } catch (const std::runtime_error &e)
    {
        assert(true);
    }

    sfex::OptionValue value = std::vector<sfex::OptionValue>{"Weird", 2, 3};
    assert(value.as_list()[1] * value.as_list()[2] == 6);

    sfex::OptionValue val1 = 7;
    sfex::OptionValue val2 = 9;

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
        val *= sfex::OptionValue::null;
        assert(false);
    }
    catch (const std::runtime_error &e)
    {
        assert(true);
    }

    return 0;
}