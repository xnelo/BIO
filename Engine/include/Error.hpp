/**
* @file Error.hpp
* @author Spencer Hoffa
*
* Holds all definitions for error handling.
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

#ifndef ___BIO_ENGINE_ERROR_HPP__2015___
#define ___BIO_ENGINE_ERROR_HPP__2015___

#include "../../Core/include/BasicTypes.hpp"

namespace BIO
{
	namespace ENGINE
	{
		typedef CORE::uint8 ErrorType;

		const ErrorType ERROR_NONE = 0;
		const ErrorType OK = ERROR_NONE;
		const ErrorType ERROR_CREATING_RENDERING_DEVICE = 1;

		char * GetErrorString(ErrorType error);
	}//end namespace ENGINE
}//end namespace BIO

inline char * BIO::ENGINE::GetErrorString(ErrorType error)
{
	switch (error)
	{
	case ERROR_CREATING_RENDERING_DEVICE:
		return "Error Creating Rendering Device.";
	default:
		return "Unrecognized Error.";
	}
}

#endif //___BIO_ENGINE_ERROR_HPP__2015___