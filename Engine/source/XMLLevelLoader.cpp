/**
* @file XMLLevelLoader.cpp
* @author Spencer Hoffa
*
* Implementation of XMLLevelLoader.
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

#include "XMLLevelLoader.hpp"

namespace BIO
{
	namespace ENGINE
	{
		void XMLLevelLoader::Clear()
		{
			_isParsed = false;
			_error = OK;
		}

		void XMLLevelLoader::ParseLevel()
		{
			BIO_LOG_INFO("Parse Level");

			_isParsed = true;
		}

		World * XMLLevelLoader::LoadLevel()
		{
			BIO_LOG_INFO("Loading Level");
			if (_isParsed == false)
			{
				BIO_LOG_DEBUG("Level not parsed... parse level");
				ParseLevel();
			}

			//now load the level
			return NULL;
		}
	}//end namespace ENGINE
}//end namespace BIO

