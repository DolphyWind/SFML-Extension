#include <iostream>
#include <cassert>
#include <cmath>
#include <SFEX/Numeric/Vector.hpp>
#include <sstream>
#include <cassert>

template<typename T, std::size_t N>
std::string arrayToString(const std::array<T, N>& arr)
{
    std::stringstream ss;
    ss << '[';

    for(std::size_t i = 0; i < arr.size(); ++i)
    {
        ss << arr[i];
        
        if(i != arr.size() - 1)
        {
            ss << ", ";
        }
    }

    ss << ']';
    return ss.str();
}

bool is_close(double left, double right, double abs_tol)
{
    double abs_diff = std::abs(right - left);
    return (abs_diff < abs_tol);
}

int main(int argc, char* argv[])
{
    sfex::Vector<2, int> intVec2_1;
    assert( (arrayToString(intVec2_1.getComponents()) == "[0, 0]") && "Default constructor error!" );

    sfex::Vector<2, int> intVec2_2{1, 2, 3};
    assert( (arrayToString(intVec2_2.getComponents()) == "[1, 2]") && "Initializer list constructor error!" );
    
    sfex::Vector<2, int> intVec2_3(intVec2_2);
    assert( (arrayToString(intVec2_3.getComponents()) == "[1, 2]") && "Same dimensional copy constructor error!" );
    
    sfex::Vector<3, int> intVec3_1(intVec2_2);
    assert( (arrayToString(intVec3_1.getComponents()) == "[1, 2, 0]") && "Different dimensional copy constructor error!" );

    assert( intVec2_3.magnitude2() == 5 && "Magnitude2() error!" );
    assert( is_close(intVec2_3.magnitude(), std::sqrt(5), 0.1) && "Magnitude() error!" );
    assert( intVec2_1.dot(intVec2_3) == 0 && "Dot product error!" );

    return 0;
}