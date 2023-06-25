#include <SFEX/SFEX.hpp>
#include <iostream>
#include <chrono>

int main()
{
    sfex::OptionManager manager;
    manager.addOption("username", "", "username");
    manager.addOption("password", "", "password");
    manager.addOption("age", 0, 18);
    manager.addOption("favourite_number", 0, 1.0);

    manager.parseFromFile_JSON("options.json");

    for(auto& [key, value] : manager)
    {
        std::cout << key << ": " << value.getValue() << std::endl;
    }
    
    return 0;
}
