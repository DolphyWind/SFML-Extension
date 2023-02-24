#include <iostream>
#include <SFEX/SFEX.hpp>
#include <SFML/System.hpp>

#ifndef SLEEPFOR_DURATION
#define SLEEPFOR_DURATION 2
#endif // SLEEPFOR_DURATION

int main()
{
	double sleepFor = SLEEPFOR_DURATION;

	sfex::Stopwatch stopwatch;
	std::cout << "Created a stopwatch! Sleeping for " << sleepFor << " seconds." << std::endl;
	sf::sleep(sf::seconds(sleepFor));
	std::cout << "getElapsedTime(): " << stopwatch.getElapsedTime().asSeconds() << "s " << std::endl;
	std::cout << "Pausing stopwatch and sleeping for " << sleepFor << " seconds." << std::endl;
	stopwatch.pause();
	sf::sleep(sf::seconds(sleepFor));
	std::cout << "getElapsedTime(): " << stopwatch.getElapsedTime().asSeconds() << "s " << std::endl;
	std::cout << "Resuming stopwatch and sleeping for " << sleepFor << " seconds." << std::endl;
	stopwatch.resume();
	sf::sleep(sf::seconds(sleepFor));
	std::cout << "getElapsedTime(): " << stopwatch.getElapsedTime().asSeconds() << "s " << std::endl;
	std::cout << "Restarting stopwatch." << std::endl;
	stopwatch.restart();
	std::cout << "getElapsedTime(): " << stopwatch.getElapsedTime().asSeconds() << "s " << std::endl;
	std::cout << "Sleeping for " << sleepFor << " seconds." << std::endl;
	sf::sleep(sf::seconds(sleepFor));
	std::cout << "getElapsedTime(): " << stopwatch.getElapsedTime().asSeconds() << "s " << std::endl;
	std::cout << "Example done!" << std::endl;

	return 0;
}
