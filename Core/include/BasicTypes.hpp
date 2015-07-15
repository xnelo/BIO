/**
* @file BasicTypes.hpp
* @author Spencer Hoffa
*
* Holds basic types that are used in the BIO libraries.
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

#ifndef ___BIO_CORE_BASICTYPES_HPP__2015___
#define ___BIO_CORE_BASICTYPES_HPP__2015___

#include "Config.h"
#include <climits>

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
#include "../../Xnelo-Testing/include/Testing.hpp"

#include <cstdio>
#include <cstdarg>
#if BIO_CORE_PLATFORM == BIO_CORE_WINDOWS
#define SPRINTF(dest, size, format, ...) sprintf_s(dest, size, format, __VA_ARGS__);
#else
#define SPRINTF(dest, size, format, ...) sprintf(dest, format, __VA_ARGS__);
#endif
#endif

#define UINT8_MAX UCHAR_MAX
#define SINT8_MIN SCHAR_MIN
#define SINT8_MAX SCHAR_MAX
#define INT8_MIN SCHAR_MIN
#define INT8_MAX SCHAR_MAX

#define UINT16_MAX USHRT_MAX
#define SINT16_MAX SHRT_MAX
#define SINT16_MIN SHRT_MIN
#define INT16_MAX SHRT_MAX
#define INT16_MIN SHRT_MIN

#define UINT32_MAX 4294967295
#define SINT32_MAX 2147483647
#define SINT32_MIN -2147483648
#define INT32_MAX SINT32_MAX
#define INT32_MIN SINT32_MIN

#define UINT64_MAX 18446744073709551615
#define SINT64_MAX 9223372036854775807 
#define SINT64_MIN -9223372036854775807 
#define INT64_MAX SINT64_MAX
#define INT64_MIN SINT64_MIN

#define FLOAT32_MAX (3.4028234*pow(10,38))
#define FLOAT32_MIN (-(3.4028234*pow(10,38)))

#define FLOAT64_MAX (1.7976931348623157 * pow(10, 308))
#define FLOAT64_MIN (-(1.7976931348623157 * pow(10, 308)))

namespace BIO
{
	namespace CORE
	{
		/**Defines an unsigned 8 bit integer type.*/
		typedef unsigned char uint8;
		/**Defines a signed 8 bit integer type.*/
		typedef signed char sint8;
		typedef char int8;

		/**Defines an unsigned 16 bit integer type.*/
		typedef unsigned short uint16;
		/**Defines a signed 16 bit integer type.*/
		typedef signed short sint16;
		typedef short int16;

		/**Defines an unsigned 32 bit integer type.*/
		typedef unsigned int uint32;
		/**Defines a signed 32 bit integer type.*/
		typedef signed int sint32;
		typedef int int32;

		/**Defines an unsigned 64 bit integer type.*/
		typedef unsigned long long uint64;
		/**Defines a signed 64 bit integer type.*/
		typedef signed long long sint64;
		typedef long long int64;

		/**Defines a 32 bit floating point number*/
		typedef float float32;
		/**Defines a 64 bit floating point number*/
		typedef double float64;

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
		/**
		* Execute tests on the Basic types part of the BIO Core
		*
		* @param test A testing object from the XNELO library.
		*
		* @return Returns a boolean object
		*/
		bool TestBasicTypes(XNELO::TESTING::Test * test);
#endif
	}//end namespace CORE
}//end namespace BIO

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
template <typename Type>
bool TestBasicMath(XNELO::TESTING::Test * test, int expectedSize, char * typeString)
{
	const int testNameBufferSize = 256;
	char testNameBuffer[testNameBufferSize];

	Type ub1 = 0;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s == 0", typeString);
	test->UnitTest(ub1 == 0, testNameBuffer);
	ub1++;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s ++ operator", typeString);
	test->UnitTest(ub1 == 1, testNameBuffer);
	ub1 *= 2;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s * operator", typeString);
	test->UnitTest(ub1 == 2, testNameBuffer);
	ub1 /= 2;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s / operator", typeString);
	test->UnitTest(ub1 == 1, testNameBuffer);
	ub1--;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s -- operator", typeString);
	test->UnitTest(ub1 == 0, testNameBuffer);
	ub1 = 12;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s = operator", typeString);
	test->UnitTest(ub1 == 12, testNameBuffer);
	Type ub2 = 10;
	Type ub3 = ub1 + ub2;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s + operator[2]", typeString);
	test->UnitTest(ub3 == 22, testNameBuffer);
	ub3 = ub3 - ub1;
	SPRINTF(testNameBuffer, testNameBufferSize, "Test %s - operator[2]", typeString);
	test->UnitTest(ub3 == 10, testNameBuffer);
	
	SPRINTF(testNameBuffer, testNameBufferSize, "Expected size of %s at least %i", typeString, expectedSize);
	test->UnitTest(sizeof(Type) >= expectedSize, testNameBuffer);

	return test->GetSuccess();
}

template <typename type>
bool TestLimits(XNELO::TESTING::Test * test, 
	type upperLimit, 
	type lowerlimit,
	char * typeString,
	bool testOutofLimits = true)
{
	const int testNameBufferSize = 256;
	char testNameBuffer[testNameBufferSize];

	type ub1 = upperLimit;
	SPRINTF(testNameBuffer, testNameBufferSize, "Testing boundaries %s upper[1]", typeString);
	test->UnitTest(ub1 == upperLimit, testNameBuffer);
	if (testOutofLimits)
	{
		ub1 = upperLimit + 1;
		SPRINTF(testNameBuffer, testNameBufferSize, "Testing boundaries %s upper[2]", typeString);
		test->UnitTest(ub1 != upperLimit + 1, testNameBuffer);
	}
	ub1 = lowerlimit;
	SPRINTF(testNameBuffer, testNameBufferSize, "Testing boundaries %s lower[1]", typeString);
	test->UnitTest(ub1 == lowerlimit, testNameBuffer);
	if (testOutofLimits)
	{
		ub1 = lowerlimit - 1;
		SPRINTF(testNameBuffer, testNameBufferSize, "Testing boundaries %s lower[2]", typeString);
		test->UnitTest(ub1 != lowerlimit - 1, testNameBuffer);
	}

	return test->GetSuccess();
}

inline bool BIO::CORE::TestBasicTypes(XNELO::TESTING::Test * test)
{
	test->SetName("Testing Basic Types");

	TestBasicMath<uint8>(test, 1, "uint8");
	TestLimits<uint8>(test, 255, 0, "uint8");

	TestBasicMath<sint8>(test, 1, "sint8");
	TestLimits<sint8>(test, 127, -128, "sint8");

	TestBasicMath<int8>(test, 1, "int8");
	TestLimits<int8>(test, 127, -128, "int8");

	TestBasicMath<uint16>(test, 2, "uint16");
	TestLimits<uint16>(test, 65535, 0, "uint16");

	TestBasicMath<sint16>(test, 2, "sint16");
	TestLimits<sint16>(test, 32767, -32768, "sint16");

	TestBasicMath<int16>(test, 2, "int16");
	TestLimits<int16>(test, 32767, -32768, "int16");

	TestBasicMath<uint32>(test, 4, "uint32");
	TestLimits<uint32>(test, 4294967295, 0, "uint32", false);

	TestBasicMath<sint32>(test, 4, "sint32");
	TestLimits<sint32>(test, 2147483647, -(long long)2147483648, "sint32", false);

	TestBasicMath<int32>(test, 4, "int32");
	TestLimits<int32>(test, 2147483647, -(long long)2147483648, "int32", false);

	TestBasicMath<uint64>(test, 8, "uint64");
	TestLimits<uint64>(test, 18446744073709551615, 0, "uint64", false);

	TestBasicMath<sint64>(test, 8, "sint64");
	TestLimits<sint64>(test, 9223372036854775807, -9223372036854775807, "sint64", false);

	TestBasicMath<int64>(test, 8, "int64");
	TestLimits<int64>(test, 9223372036854775807, -9223372036854775807, "int64", false);

	TestBasicMath<float32>(test, 4, "float32");
	TestLimits<float32>(test, (float)(3.4028234*pow(10, 38)), -(float)(3.4028234*pow(10, 38)), "float32", false);

	TestBasicMath<float64>(test, 8, "float64");
	TestLimits<float64>(test, 1.7976931348623157 * pow(10, 308), -(1.7976931348623157 * pow(10, 308)), "float64", false);

	return test->GetSuccess();
}
#endif //BIO_TESTING_IS_ENABLED

#endif //___BIO_CORE_BASICTYPES_HPP__2015___

