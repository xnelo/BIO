#include <iostream>

#include "../../../Core/include/Core.hpp"
#include "../../../Engine/include/BIOEngine.hpp"

void RunAll()
{
	bool coreResults = BIO::CORE::TestCore();
	bool engineResults = BIO::ENGINE::TestEngine();

	std::cout << "BIO CORE TESTS: " << (coreResults ? "SUCCESS" : "FAILURE") << std::endl;
	std::cout << "BIO ENGINE TESTS: " << (engineResults ? "SUCCESS" : "FAILURE") << std::endl;
}

int main(int argc, char * argv[])
{
	std::cout << "Welcome to the BIOEngine Tester. "
		      << "This program will run some tests on the current build of the BIOEngine" 
			  << std::endl;
	std::cout << "Which tests would you like to run: " << std::endl;

	RunAll();
}