/**
* @file Testing.cpp
* @author Spencer Hoffa
*
* Testing implementation
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

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_OFF
#include <iostream>
#else
#include "../../Xnelo-Testing/include/Testing.hpp"
#include "BasicTypes.hpp"
#include "StringUtils.hpp"
#include "FileUtils.hpp"
#endif

bool BIO::CORE::TestCore()
{
#if BIO_TESTING_IS_ENABLED == BIO_TESTING_OFF
	std::cout << "Testing is disabled" << std::endl;
	return true;
#else //TESTING IS ENABLED
	//create a test suite for this class
	XNELO::TESTING::TestSuite testSuite("BIO CORE Tests");
	XNELO::TESTING::OutStreamGenerator output;

	testSuite.SetReportGenerator(&output);

	//add the test functions
	testSuite.AddTestFunction(TestBasicTypes);
	testSuite.AddTestFunction(STRING::TestStringUtils);
	testSuite.AddTestFunction(FILE::FileUtilsTests);

	//run tests and print out results
	testSuite.ExecuteTests();

	//save the return value
	bool retValue = testSuite.GetSuccess();

	return retValue;
#endif //BIO_TESTING_IS_ENABLED
}