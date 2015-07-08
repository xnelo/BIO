/**
* @file BIOEngineConfiguration.hpp
* @author Spencer Hoffa
*
* A structure to hold the configuration for a BIOEngine Instance.
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

#ifndef ___BIO_ENGINE_BIOENGINECONFIGURATION_HPP__2015___
#define ___BIO_ENGINE_BIOENGINECONFIGURATION_HPP__2015___

#include "Config.h"
#include "EngineTypes.hpp"

namespace BIO
{
	namespace ENGINE
	{
		/**
		* Holds all of the properties needed to initialize a BIOEngine intance.
		*/
		class BIOEngineConfiguration
		{
		public:
			/**The driver type to use for rendering.*/
			RENDERING_DRIVER renderingDriver;

			/**The Width of the rendering screen.*/
			unsigned int screenWidth;

			/**The Height of the rendering screen.*/
			unsigned int screenHeight;

			/**Bits Per Pixel*/
			unsigned int bits;

			/**Does the engine render in fullscreen mode.*/
			bool fullscreen;

			/**Enable Stencil Buffer.*/
			bool enableStencilBuffer;

			/**Enable Vertical Sync.*/
			bool enableVeticalSync;

			/**
			* Default Constructor
			*/
			BIO_ENGINE_API BIOEngineConfiguration();

			/**
			* Destructor
			*/
			BIO_ENGINE_API ~BIOEngineConfiguration();
		};
	}//end namespace ENGINE
}//end namespace BIO

inline BIO::ENGINE::BIOEngineConfiguration::BIOEngineConfiguration():
renderingDriver(RD_OPEN_GL),
screenWidth(640),
screenHeight(480),
bits(32),
fullscreen(false),
enableStencilBuffer(false),
enableVeticalSync(true)
{
	//Do Nothing
}

inline BIO::ENGINE::BIOEngineConfiguration::~BIOEngineConfiguration()
{ 
	//Do Nothing 
}

#endif//___BIO_ENGINE_BIOENGINECONFIGURATION_HPP__2015___

