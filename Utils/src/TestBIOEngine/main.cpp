#include <iostream>

#include "../../../Core/include/Core.hpp"

void RunAll()
{
	std::cout << "BIO CORE TESTS: " << (BIO::CORE::TestCore() ? "SUCCESS" : "FAILURE") << std::endl;
}

int main(int argc, char * argv[])
{
	std::cout << "Welcome to the BIOEngine Tester. "
		      << "This program will run some tests on the current build of the BIOEngine" 
			  << std::endl;
	std::cout << "Which tests would you like to run: " << std::endl;

	RunAll();
}