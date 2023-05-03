#include <SFEX/SFEX.hpp>
#include <iostream>
#include <chrono>

int main()
{
    sfex::OptionManager manager;
    manager.addOption("username", "", "username");
    manager.addOption("password", "", "password");
    manager.addOption("hp", 0, 100);
    manager.addOption("attack", 0, 1.0f);

    manager.parseFromFile("options.txt");
    for(auto& [key, option] : manager)
    {
        std::cout << key << "=" << option.value << " (default: " << option.default_value << ")\n";
    }

    return 0;
}
