/**
* @file Testing.cpp
* @author Spencer Hoffa
*
* Implements and runs all the Tests for the BIO Engine library.
*/
/*
* Copyright (c)
* 2015
* Spencer Hoffa
*
* This software is provided 'as-is', without any express or implied warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose, including commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
*    original software. If you use this software in a product, an acknowledgement in the product
*    documentation would be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
*    being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Testing.hpp"

#if BIOENGINE_TESTING_IS_ENABLED == BIOENGINE_TESTING_ON

//include all of the objects to test
#include "BIOEngineClass.hpp"
#include "XMLLevelLoader.hpp"

bool BIO::ENGINE::TestEngine()
{
	XNELO::TESTING::TestSuite testSuite("BIO ENGINE Tests");
	XNELO::TESTING::OutStreamGenerator output;

	testSuite.SetReportGenerator(&output);

	//add the test functions
	testSuite.AddTestFunction(BIOEngine::Test);
	testSuite.AddTestFunction(XMLLevelLoader::Test);

	//run tests and print out results
	testSuite.ExecuteTests();

	//save the return value
	bool retValue = testSuite.GetSuccess();

	return retValue;
}
#else
#include <iostream>
bool BIO::ENGINE::TestEngine()
{
	std::cout << "TESTING DISABLED" << std::endl;
	return true;
}
#endif