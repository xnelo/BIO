/**
* @file Testing.hpp
* @author Spencer Hoffa
*
* Holds all of the Logging definitions.
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

#ifndef ___BIO_CORE_TESTING_HPP__2015___
#define ___BIO_CORE_TESTING_HPP__2015___

#include "Config.h"

namespace BIO
{
	namespace CORE
	{
		/**
		* Executes all the tests that are a part of the BIO Core library.
		*
		* @return Returns a boolean value. True iff all the tests successfully pass. Otherwise 
		*			false is returned.
		*/
		BIO_CORE_API bool TestCore();
	}//end namespace TESTING
} //end namespace BIO

#endif //___BIO_CORE_TESTING_HPP__2015___