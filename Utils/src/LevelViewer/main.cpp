#include <vld.h> //check for leaks
#include <iostream>
#include "BIOEngine.hpp"

int MainLoop(BIO::ENGINE::BIOEngine * engine)
{
	std::cout << "Running Main Loop" << std::endl;

	while (engine->Run())
	{
		if (engine->IsWindowActive())
		{
			std::cout << "Running Loop" << std::endl;
		}
		else
		{
			engine->Yield();
		}
	}

	return 0;
}

int main(int argc, char * argv)
{
	std::cout << "LevelViewer Starting: " << std::endl;

	BIO::ENGINE::BIOEngine * tmp;
	tmp = new BIO::ENGINE::BIOEngine();

	if (tmp->GetError() == BIO::ENGINE::OK)
	{
		int err = MainLoop(tmp);
	}

	delete tmp;

	return 0;
}