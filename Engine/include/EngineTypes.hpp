/**
* @file EngineTypes.hpp
* @author Spencer Hoffa
*
* Types defined for the BIO Engine.
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

#ifndef ___BIO_ENGINE_ENGINETYPES_HPP__2015___
#define ___BIO_ENGINE_ENGINETYPES_HPP__2015___

#include "../Irrlicht/include/irrlicht.h"

namespace BIO
{
	namespace ENGINE
	{
		/**
		* Defines the rendering drivers available. These are the libraries/API's that enable 
		* graphics rendering in the BIO ENGINE.
		*/
		enum RENDERING_DRIVER
		{
			/**Doesn't render anything.*/
			RD_NULL,
			/**DirectX 8. Available on Windows.*/
			RD_DIRECT_3D8,
			/**DirectX 9. Available on Windows.*/
			RD_DIRECT_3D9,
			/**Open GL. Available on most platforms. Open source specification.*/
			RD_OPEN_GL
		};
	}//end namespace Engine
}//end namespace BIO



#endif //___BIO_ENGINE_ENGINETYPES_HPP__2015___