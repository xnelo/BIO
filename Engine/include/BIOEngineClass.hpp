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
#include "Error.hpp"
#include "../../Core/include/Logger.hpp"

#if BIOENGINE_TESTING_IS_ENABLED == BIOENGINE_TESTING_ON
#include "../../Xnelo-Testing/include/Testing.hpp"
#endif

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
			* The error value of this class. 0, OK, or ERROR_NONE means no error occured and 
			* engine is ok to continue running.
			*/
			ErrorType _error;

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

			/**
			* Get the error code of the engine.
			*
			* @return Returns an integer with the Error value of the engine.
			*/
			BIO_ENGINE_API ErrorType GetError();

			/**
			* Check if the window is active.
			*
			* @return Returns a boolean with true if the engine's window is the active window. If
			*			it isn't then false is returned.
			*/
			BIO_ENGINE_API bool IsWindowActive();

			/**
			* Load a level from the passed in file.
			*
			* @param filename The name of the file to load.
			*
			* @return Returns true if the file was loaded successfully.
			*/
			BIO_ENGINE_API bool LoadLevel(std::string filename);
			BIO_ENGINE_API bool LoadLevel(const char * filename);

			/**
			* Is the engine still ready to continue running?
			*
			* @return Returns a boolean with true if the engine is ready, or false if the engine is
			*			closed/in an error state/ or incapable of continuing.
			*/
			BIO_ENGINE_API bool Run();

			/**
			* Yields the engine to the OS.
			*/
			BIO_ENGINE_API void Yield();

#if BIOENGINE_TESTING_IS_ENABLED == BIOENGINE_TESTING_ON
			/**
			* Tests for the BIOEngine class.
			*
			* @param test A pointer to a Test object.
			*
			* @return Returns true if all the tests succeded. False otherwise.
			*/
			BIO_ENGINE_API static bool Test(XNELO::TESTING::Test * test);
#endif
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

inline BIO::ENGINE::ErrorType BIO::ENGINE::BIOEngine::GetError()
{
	return _error;
}

inline bool BIO::ENGINE::BIOEngine::IsWindowActive()
{
	return _device->isWindowActive();
}

inline bool BIO::ENGINE::BIOEngine::LoadLevel(std::string filename)
{
	return LoadLevel(filename.c_str());
}

inline bool BIO::ENGINE::BIOEngine::Run()
{
	return _device->run();
}

inline void BIO::ENGINE::BIOEngine::Yield()
{
	BIO_LOG_DEBUG4("Yielding Engine.");
	_device->yield();
}

#endif//___BIO_ENGINE_BIOENGINECLASS_HPP__2015___