
#include <iostream>
#include <string>

#include "Debug.h"

void Debug::Log(int Out)
{

	std::cout << Out << std::endl;

}

void Debug::Log(float Out)
{

	std::cout << Out << std::endl;

}

void Debug::Log(char Out[])
{

	std::cout << Out << std::endl;

}

void Debug::Log(bool Out)
{

	std::string OutString = Out ? "true" : "false";
	std::cout << OutString << std::endl;

}

void Debug::Log(std::string Out)
{

	std::cout << Out << std::endl;

}

void Debug::Log(uint32_t Out)
{

	std::cout << Out << std::endl;

}

void Debug::Prompt()
{

	std::cout << "Press enter to continue..." << std::endl;
	std::cin.get();

}