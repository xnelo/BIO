/**
* @file StringUtils.hpp
* @author Spencer Hoffa
*
* String utilities for the BIO Engine.
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

#ifndef ___BIO_CORE_STRINGUTILS_HPP__2015___
#define ___BIO_CORE_STRINGUTILS_HPP__2015___

#include "Config.h"

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
#include "../../Xnelo-Testing/include/Testing.hpp"
#endif

namespace BIO
{
	namespace STRING
	{
		/**
		* String Compare Case Insensitive. Compare two c-strings to see if they are the same 
		* without case sensitivity. A == a in this function. This function checks the entire string 
		* and only stops when the null terminating('\0') character is reached. This function is the 
		* same as standard C's strncmp except it is case insensitive.
		*
		* thanks to: larsmans
		* @see http://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c
		*
		* @param a A c-string of the first string.
		* @param b A c-string for the second string.
		*
		* @returns Returns 0 if the two strings are equivalant. <0 is returned if a and b do not 
		*			match and a comes before b. >0 is returned if a and b do not match and b comes 
		*			before a.
		*/
		int strcmpCI(char const *a, char const *b);

		/**
		* String Compare Case Insensitive. Compare two c-strings to see if they are the same 
		* without case sensitivity. A == a in this function. Only num number of characters are 
		* checked. This function is the same as standard C's strncmp except it is case insensitive.
		*
		* thanks to: larsmans
		* @see http://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c
		*
		* @param a A c-string of the first string.
		* @param b A c-string for the second string.
		* @param num The number of characters to check.
		*
		* @returns Returns 0 if the parts of the two strings are equivalant. <0 is returned if a 
		*			and b do not match and a comes before b. >0 is returned if a and b do not match 
		*			and b comes before a.
		*/
		int strncmpCI(const char *a, const char *b, int num);

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
		/**
		* Execute the unit tests for the BIO String namespace
		*
		* @param test A pointer to a Test object which will hold all tests and results.
		*
		* @return Returns a boolean value. True if all tests pass. False if even one failed.
		*/
		bool TestStringUtils(XNELO::TESTING::Test * test);
#endif

	}//end namespace STRING
}//end namespace BIO

inline int BIO::STRING::strcmpCI(char const *a, char const *b)
{
	while ((a[0] != '\0') && (b[0] != '\0'))
	{
		int d = tolower(*a) - tolower(*b);
		if (d != 0)
			return d;

		a++;
		b++;
	}

	return tolower(*a) - tolower(*b);
}

inline int BIO::STRING::strncmpCI(const char *a, const char *b, int num)
{
	for (int i = 0; i < num; a++, b++, i++)
	{
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a || !*b)
			return d;
	}
	return 0;
}

//Move everything below here to the stringUtils.cpp file when it is created.
#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
inline bool BIO::STRING::TestStringUtils(XNELO::TESTING::Test * test)
{
	test->SetName("String Utilities Tests");

	test->UnitTest(strncmpCI("test", "Test", 4) == 0, "Compare Case Insinsitive numbered[1]");
	test->UnitTest(strncmpCI("teST", "Test", 4) == 0, "Compare Case Insinsitive numbered[2]");
	test->UnitTest(strncmpCI("teSTint", "Test", 4) == 0, "Compare Case Insinsitive numbered[3]");
	test->UnitTest(strncmpCI("NAMING", "naMing", 2) == 0, "Compare Case Insinsitive numbered[4]");
	test->UnitTest(strncmpCI("NAMING", "Tes", 5) < 0, "Compare Case Insinsitive numbered[5]");
	test->UnitTest(strncmpCI("NAMING", "NAMING", 6) == 0, "Compare Case Insinsitive numbered[6]");
	test->UnitTest(strncmpCI("NAMING", "NAMINa", 6) > 0, "Compare Case Insinsitive numbered[7]");

	test->UnitTest(strcmpCI("Test", "tEST") == 0, "Compare Case Insinsitive [1]");
	test->UnitTest(strcmpCI("Test", "tES") > 0, "Compare Case Insinsitive [2]");
	test->UnitTest(strcmpCI("Tes", "tEST") < 0, "Compare Case Insinsitive [3]");
	test->UnitTest(strcmpCI("Test", "Crap") > 0, "Compare Case Insinsitive [4]");
	test->UnitTest(strcmpCI("Crap", "Test") < 0, "Compare Case Insinsitive [5]");

	return test->GetSuccess();
}
#endif

#endif//___BIO_CORE_STRINGUTILS_HPP__2015___


