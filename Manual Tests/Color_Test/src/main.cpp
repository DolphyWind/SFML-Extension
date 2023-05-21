#include <SFEX/SFEX.hpp>
#include <iostream>

void printDashes(std::size_t n = 30)
{
    std::cout << std::string(n, '-') << std::endl;
}

int main()
{
    std::cout << "Red color: " << sfex::Color::Red << std::endl;
    std::cout << "Red as hexadecimal: 0x" << std::hex << sfex::Color::Red.toHex() << std::dec << std::endl;

    std::cout << "0x23BF00BB to color: " << sfex::Color::fromHex(0x23BF00BB) << std::endl;
    std::cout << "White mixed with black: " << sfex::Color::mixColors(sfex::Color::White, sfex::Color::Black) << std::endl;

    std::cout << "Red / 2: "  << sfex::Color::Red / 2.f  << std::endl;
    std::cout << "Gray * 0.7 with noalpha: " << sfex::Color::Gray.multiply(0.7f, true) << std::endl;

    std::cout << "Red + Blue: " << (sfex::Color::Red + sfex::Color::Blue) << std::endl;
    std::cout << "Yellow to grayscale: " << sfex::Color::Yellow.toGrayscale() << std::endl;

    return 0;
}
