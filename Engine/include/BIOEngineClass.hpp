/**
* @file BIOEngineClass.hpp
* @author Spencer Hoffa
*
* This file defines the BIOEngine class that runs a bioengine instance.
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

#ifndef ___BIO_ENGINE_BIOENGINECLASS_HPP__2015___
#define ___BIO_ENGINE_BIOENGINECLASS_HPP__2015___

#include "Config.h"
#include "../Irrlicht/include/irrlicht.h"

#include "BIOEngineConfiguration.hpp"

namespace BIO
{
	namespace ENGINE
	{
		class BIOEngine
		{
		private:
			/**The Irrlicht device that runs the graphics.*/
			irr::IrrlichtDevice * _device;

			/**
			* Initialize the Engine.
			*
			* @param config A BIOEngineConfiguration class with the information to initialize the 
			*			engine.
			*/
			BIO_ENGINE_API void _InitEngine(BIOEngineConfiguration * config);
		public:
			/**
			* Default Constructor
			*
			* @param config [optional] A pointer to the BIOEngineConfiguration class with the 
			*			initialization information. Default value is NULL, all default values will
			*			be used.
			*/
			BIO_ENGINE_API BIOEngine(BIOEngineConfiguration * config = NULL);

			/**
			* Constructor
			* 
			* @param config A reference to the BIOEngineConfiguration class with the initialization
			*			information.
			*/
			BIO_ENGINE_API BIOEngine(BIOEngineConfiguration & config);

			/**
			* Destructor
			*/
			BIO_ENGINE_API ~BIOEngine();
		};
	}//end namespace ENGINE
}//end namespace BIO

inline BIO::ENGINE::BIOEngine::BIOEngine(BIOEngineConfiguration * config)
{
	if (config == NULL)
	{
		BIOEngineConfiguration tmp_config;
		_InitEngine(&tmp_config);
	}
	else
	{
		_InitEngine(config);
	}
}

inline BIO::ENGINE::BIOEngine::BIOEngine(BIOEngineConfiguration & config)
{
	_InitEngine(&config);
}

#endif//___BIO_ENGINE_BIOENGINECLASS_HPP__2015___