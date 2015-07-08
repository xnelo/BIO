/**
* @file BIOEngineClass.cpp
* @author Spencer Hoffa
*
* This file implements the BIOEngine class
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

#include <vld.h> //check for leaks

#include "BIOEngineClass.hpp"
#include "EngineTypes.hpp"

#include <iostream>
#include "../../Core//include/Logger.hpp"

namespace BIO
{
	namespace ENGINE
	{

		/**
		* Engine Rendering Driver to Rendering type. This converts the RENDERING_DRIVER BIO Engine
		* enumeration to the Graphics engines rendering type.
		*/
		inline irr::video::E_DRIVER_TYPE _RenderingDriverToGraphicsType(RENDERING_DRIVER rd)
		{
			switch (rd)
			{
			case RD_NULL:
				return irr::video::EDT_NULL;
			case RD_DIRECT_3D8:
				return irr::video::EDT_DIRECT3D8;
			case RD_DIRECT_3D9:
				return irr::video::EDT_DIRECT3D9;
			case RD_OPEN_GL:
			default:
				return irr::video::EDT_OPENGL;
			}
		}

		BIOEngine::~BIOEngine()
		{
			BIO_LOG_INFO("BIOEngine Destructor Called");

			if (_device)
			{
				delete _device;
				_device = NULL;
			}
		}

		void BIOEngine::_InitEngine(BIOEngineConfiguration * config)
		{
			BIO_LOG_INFO("BIOEngine Initializing");

			//Set all the variable to default values --------------------------
			_device = NULL;
			//-----------------------------------------------------------------

			//initialize the device
			_device = irr::createDevice(_RenderingDriverToGraphicsType(config->renderingDriver),
										irr::core::dimension2du(config->screenWidth, config->screenHeight), 
										config->bits, 
										config->fullscreen, 
										config->enableStencilBuffer, 
										config->enableVeticalSync);
		}
	}//end namespace ENGINE
}//end namespace BIO