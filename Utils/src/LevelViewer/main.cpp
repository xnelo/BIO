#include <vld.h> //check for leaks
#include <iostream>
#include "BIOEngine.hpp"

int main(int argc, char * argv)
{
	std::cout << "LevelViewer Starting: " << std::endl;

	BIO::ENGINE::BIOEngine * tmp;
	tmp = new BIO::ENGINE::BIOEngine();

	delete tmp;

	return 0;
}