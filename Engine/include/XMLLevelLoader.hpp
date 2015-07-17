/**
* @file XMLLevelLoader.hpp
* @author Spencer Hoffa
*
* Parses XML based level files.
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

#ifndef ___BIO_ENGINE_XMLLEVELLOADER_HPP__2015___
#define ___BIO_ENGINE_XMLLEVELLOADER_HPP__2015___

#include "Config.h"
#include "ILevelLoader.hpp"

namespace BIO
{
	namespace ENGINE
	{
		/**
		* A Level Loader that parses an XML based level file.
		*/
		class XMLLevelLoader : public ILevelLoader
		{
		public:
			/**
			* Constructor
			*/
			BIO_ENGINE_API XMLLevelLoader();

			/**
			* Constructor
			*
			* @param filename The name of the file to load the level from.
			*/
			BIO_ENGINE_API XMLLevelLoader(std::string filename);
			BIO_ENGINE_API XMLLevelLoader(const char * filename);

			/**
			* Destructor
			*/
			BIO_ENGINE_API virtual ~XMLLevelLoader();

			/**
			* Clear any data previously loaded.
			*
			* @NOTE This function is also called from the destructor.
			*
			* @NOTE This function must set the _error variable to 0 or BIO::ENGINE::OK and the
			*		_isParsed to false. This is your responsibility as an implementor of this
			*		interface.
			*/
			BIO_ENGINE_API virtual void Clear();

			/**
			* Parses the data (if it wasn't already parsed) then creates a World objects as defined
			* by the level file and returns a pointer to it.
			*
			* @NOTE This function will create the World object on the heap so it is your
			*		responsibility to make sure it is deleted, or passed into an object that will
			*		delete it.
			*
			* @return Returns a pointer to a World object with the level created and ready. This
			*			object is on the heap so make sure it is cleaned up.
			*/
			BIO_ENGINE_API virtual World * LoadLevel();

			/**
			* Parse the level information. All the information is stored internally in a struct
			* which is retrieved using the Get !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			*
			* @NOTE This function should set the _isParsed variable to true and set the _error
			*		variable to 0 or BIO::ENGINE:OK when the parsing is successful. This is your
			*		responsibility as an implementor of this interface.
			*/
			BIO_ENGINE_API virtual void ParseLevel();
		};
	}//end namespace ENGINE
}//end namespace BIO

inline BIO::ENGINE::XMLLevelLoader::XMLLevelLoader() : ILevelLoader()
{
	BIO_LOG_INFO("XMLLevelLoader Constructor");
}

inline BIO::ENGINE::XMLLevelLoader::XMLLevelLoader(std::string filename) : ILevelLoader(filename)
{
	BIO_LOG_INFO("XMLLevelLoader Constructor. filename = %s", filename);
}

inline BIO::ENGINE::XMLLevelLoader::XMLLevelLoader(const char * filename) : ILevelLoader(filename)
{
	BIO_LOG_INFO("XMLLevelLoader Constructor. filename = %s", filename);
}

inline BIO::ENGINE::XMLLevelLoader::~XMLLevelLoader()
{
	BIO_LOG_INFO("XMLLevelLoader Destructor");
}

#endif //___BIO_ENGINE_XMLLEVELLOADER_HPP__2015___


