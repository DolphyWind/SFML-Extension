#include <iostream>
#include <SFEX/General/Scheduler.hpp>

int repeatCount = 0;

int funcToSchedule(int a, int b)
{
    return a + b;
}

void funcToRepeat()
{
    std::cout << "I am repeating!" << std::endl;
    ++repeatCount;
}

int main(int argc, char** argv)
{
    sfex::Scheduler scheduler;

    auto result = scheduler.schedule(sf::seconds(0.25f), funcToSchedule, 1, 2);    
    scheduler.repeat("Hello", sf::seconds(0.25f), funcToRepeat);

    while(true)
    {
        if(repeatCount >= 3) 
        {
            scheduler.stopRepeatingJob("Hello");
            break;
        }
    }
    std::cout << "The result of the scheduled function: " << result.get() << std::endl;

    return 0;
}