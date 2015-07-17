/**
* @file ILevelLoader.hpp
* @author Spencer Hoffa
*
* Defines an interface for loading levels in the BIO Engine. This way it is easy for new file types
* and level formats to be loaded.
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

#ifndef ___BIO_ENGINE_ILEVELLOADER_HPP__2015___
#define ___BIO_ENGINE_ILEVELLOADER_HPP__2015___

#include "Config.h"

#include <string>
#include "Error.hpp"
#include "../../Core/include/Logger.hpp"
#include "World.hpp"

namespace BIO
{
	namespace ENGINE
	{
		/**
		* An abstract interface class that defines the needed functions for a level loader.
		*/
		class ILevelLoader
		{
		protected:
			/**
			* Stores the current error code for this class.
			*/
			ErrorType _error;

			/**
			* Stores the filename of the level that is/has/will be loaded.
			*/
			std::string _filename;

			/**
			* Stores if the file has been parsed already.
			*/
			bool _isParsed;

		public:
			/**
			* Default constructor
			*/
			BIO_ENGINE_API ILevelLoader();

			/**
			* Constructor
			*
			* @param filename The file name of the level to load.
			*/
			BIO_ENGINE_API ILevelLoader(std::string filename);
			BIO_ENGINE_API ILevelLoader(const char * filename);

			/**
			* Destructor
			*
			* @NOTE Be sure to make all of your inherited class destructors virtual so that this is
			*		called on shutdown.
			*/
			BIO_ENGINE_API virtual ~ILevelLoader();

			/**
			* Clear any data previously loaded.
			*
			* @NOTE This function is also called from the destructor.
			*
			* @NOTE This function must set the _error variable to 0 or BIO::ENGINE::OK and the 
			*		_isParsed to false. This is your responsibility as an implementor of this 
			*		interface.
			*/
			BIO_ENGINE_API virtual void Clear() = 0;

			/**
			* Retrieve the error code for this class.
			*
			* @return Returns a number that is the error code for this class.
			*/
			BIO_ENGINE_API ErrorType GetError();

			/**
			* Retrieve the filename of the level.
			*
			* @return Return a string with the filename of the level.
			*/
			BIO_ENGINE_API std::string GetFilename();

			/**
			* Retrieve the filename of the level.
			*
			* @return Returns a C-string with the filename of the level.
			*/
			BIO_ENGINE_API const char * GetFilenameC();

			/**
			* Is this file already Parsed.
			*
			* @return Returns a boolean value that is true if the file has already been parsed.
			*/
			BIO_ENGINE_API bool IsParsed();
			 
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
			BIO_ENGINE_API virtual World * LoadLevel() = 0;

			/**
			* Parse the level information. All the information is stored internally in a struct 
			* which is retrieved using the Get !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			*
			* @NOTE This function should set the _isParsed variable to true and set the _error 
			*		variable to 0 or BIO::ENGINE:OK when the parsing is successful. This is your
			*		responsibility as an implementor of this interface.
			*/
			BIO_ENGINE_API virtual void ParseLevel() = 0;

			/**
			* Set the filename of the level to load.
			*
			* @NOTE Calling this function will clear any data that has been parsed or loaded from 
			*		previous load calls.
			*
			* @param filename The new filename to load.
			*/
			BIO_ENGINE_API void SetFilename(std::string filename);
			BIO_ENGINE_API void SetFilename(const char * filename);
		};
	}
}//end namespace BIO

inline BIO::ENGINE::ILevelLoader::ILevelLoader() : _error(OK), _filename(), _isParsed(false)
{
	BIO_LOG_INFO("ILevelLoader Constructed");
}

inline BIO::ENGINE::ILevelLoader::ILevelLoader(std::string filename) : _error(OK), _filename(filename), _isParsed(false)
{
	BIO_LOG_INFO("ILevelLoader Constructed");
}

inline BIO::ENGINE::ILevelLoader::ILevelLoader(const char * filename) : _error(OK), _filename(filename), _isParsed(false)
{
	BIO_LOG_INFO("ILevelLoader Constructed");
}

inline BIO::ENGINE::ILevelLoader::~ILevelLoader()
{
	BIO_LOG_INFO("Destroying ILevelLoader");
	Clear();
	_filename = "";
}

inline BIO::ENGINE::ErrorType BIO::ENGINE::ILevelLoader::GetError()
{
	return _error;
}

inline std::string BIO::ENGINE::ILevelLoader::GetFilename()
{
	return _filename;
}

inline const char * BIO::ENGINE::ILevelLoader::GetFilenameC()
{
	return _filename.c_str();
}

inline bool BIO::ENGINE::ILevelLoader::IsParsed()
{
	return _isParsed;
}

inline void BIO::ENGINE::ILevelLoader::SetFilename(std::string filename)
{
	SetFilename(filename.c_str());
}

inline void BIO::ENGINE::ILevelLoader::SetFilename(const char * filename)
{
	Clear();
	_filename = std::string(filename);
}

#endif //___BIO_ENGINE_ILEVELLOADER_HPP__2015___

