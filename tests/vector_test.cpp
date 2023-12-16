#include <iostream>
#include <cassert>
#include <cmath>
#include <SFEX/Numeric/Vector.hpp>
#include <sstream>
#include <cassert>
#define SFEX_ASSERT(condition, message) assert((condition) && (message))

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
    sfex::Vector<2, float> floatVec2_1;
    SFEX_ASSERT((arrayToString(floatVec2_1.getComponents()) == "[0, 0]"), "Default constructor error!" );

    sfex::Vector<2, float> floatVec2_2{1, 2, 3};
    SFEX_ASSERT((arrayToString(floatVec2_2.getComponents()) == "[1, 2]"), "Initializer list constructor error!" );
    
    sfex::Vector<2, float> floatVec2_3(floatVec2_2);
    SFEX_ASSERT((arrayToString(floatVec2_3.getComponents()) == "[1, 2]"), "Same dimensional copy constructor error!" );
    
    sfex::Vector<3, float> floatVec3_1(floatVec2_2);
    SFEX_ASSERT((arrayToString(floatVec3_1.getComponents()) == "[1, 2, 0]"), "Different dimensional copy constructor error!" );

    SFEX_ASSERT(floatVec2_3.magnitude2() == 5, "Magnitude2() error!" );
    SFEX_ASSERT(is_close(floatVec2_3.magnitude(), std::sqrt(5), 0.1), "Magnitude() error!" );
    SFEX_ASSERT(floatVec2_1.dot(floatVec2_3) == 0, "Dot product error!" );

    floatVec2_3.setMagnitude(5);
    SFEX_ASSERT(is_close(floatVec2_3.magnitude(), 5, 0.1f), "setMagnitude() error!" );

    // Normalize test
    SFEX_ASSERT(is_close(floatVec2_3.normalized().magnitude(), 1, 0.1f), "Normalized error!");
    floatVec2_3.normalize();
    SFEX_ASSERT(is_close(floatVec2_3.magnitude(), 1, 0.1f), "Normalized error!");

    SFEX_ASSERT(floatVec2_1 == floatVec2_1, "== operator error!");
    SFEX_ASSERT(floatVec2_1 != floatVec2_3, "!= operator error!");
    SFEX_ASSERT(floatVec2_1 != floatVec3_1, "!= operator error!");

    const sfex::Vector<2, float> i_hat_2d{1, 0};
    const sfex::Vector<2, float> j_hat_2d{0, 1};

    SFEX_ASSERT(i_hat_2d.cross(j_hat_2d) == 1, "2D Cross product error!");
    SFEX_ASSERT(j_hat_2d.cross(i_hat_2d) == -1, "2D Cross product error!");

    const sfex::Vector<3, float> i_hat_3d{1, 0, 0};
    const sfex::Vector<3, float> j_hat_3d{0, 1, 0};
    const sfex::Vector<3, float> k_hat_3d{0, 0, 1};
    const sfex::Vector<3, float> zero_vec_3d;

    SFEX_ASSERT(i_hat_3d.cross(j_hat_3d) == k_hat_3d, "3D Cross product error!");
    SFEX_ASSERT(j_hat_3d.cross(j_hat_3d) == zero_vec_3d, "3D Cross product error!");

    const sfex::Vector<3, int> vec_to_scale{1, 2, 3};
    SFEX_ASSERT((vec_to_scale.scaled(2) == sfex::Vector<3, int>{2, 4, 6}), "Scale error!");

    SFEX_ASSERT((sfex::Vector<3, int>{1, 2, 3}.cwiseMul(sfex::Vector<3, int>{9, 8, 7}) == sfex::Vector<3, int>{9, 16, 21}), "CWise mul error");
    SFEX_ASSERT((sfex::Vector<3, int>{16, 25, 9}.cwiseDiv(sfex::Vector<3, int>{4, 5, 3}) == sfex::Vector<3, int>{4, 5, 3}), "CWise div error");

    return 0;
}