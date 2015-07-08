/**
* @file Config.h
* @author Spencer Hoffa
*
* Holds all of the configuration data for the BIO Engine project.
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
#ifndef ___BIO_ENGINE_CONFIG_H__2015___
#define ___BIO_ENGINE_CONFIG_H__2015___

#define BIO_ENGINE_WINDOWS 1
#define BIO_ENGINE_LINUX 2

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32) || \
	defined(__WINDOWS__) || defined(__TOS_WIN__)
	#define BIO_ENGINE_PLATFORM BIO_ENGINE_WINDOWS
#elif defined(__linux__) || defined(linux) || defined(__linux)
	#define BIO_ENGINE_PLATFORM BIO_ENGINE_LINUX
#endif 

//prepare for dll import
#if (!defined(BIO_ENGINE_STATIC_LIB)) && (BIO_ENGINE_PLATFORM == BIO_ENGINE_WINDOWS)
	#ifdef BIO_ENGINE_EXPORTS
		#define BIO_ENGINE_API __declspec(dllexport)
	#else
		#define BIO_ENGINE_API __declspec(dllimport)
	#endif //BIO_ENGINE_EXPORTS
#else //static library
	#define BIO_ENGINE_API
#endif

#endif //___BIO_ENGINE_CONFIG_H__2015___