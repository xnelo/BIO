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
#include "EngineTypes.hpp"

#include <string>
#include "Error.hpp"
#include "../../Core/include/Logger.hpp"
#include "World.hpp"

namespace BIO
{
	namespace ENGINE
	{
		/**
		* A class that holds all of the information for a level.
		*/
		struct LevelInfo
		{
		public:
			std::string LevelFilename;	/**< The file that hold level geometry.*/
			Vector3 Gravity;			/**< Direction and strength of gravity.*/
			//Camera Data -----------------------------------------------------
			CAMERA_TYPE CameraType;		/**< The type of camera to create.*/
			float MinView;				/**< The minimum view range of the camera.*/
			float MaxView;				/**< The maximum view range of the camera.*/
			std::string ToFollow;		/**< The name of the object to follow.*/
			float FollowDistance;		/**< Distance from the object to follow at.*/
			float FollowHeight;			/**< Height from the object to follow at.*/
			Vector3 Position;			/**< The position of a default camera.*/
			Vector3 LookAt;				/**< The point to look at for the default camera.*/
			//End Camera Data -------------------------------------------------

			/**
			* Constructor
			*/
			LevelInfo() :
				LevelFilename(""),
				Gravity(0.0f, -9.8f, 0.0f),
				CameraType(CAMERA_DEFAULT),
				MinView(0.1f),
				MaxView(1000.0f),
				ToFollow(""),
				FollowDistance(10.0f),
				FollowHeight(5.0f),
				Position(-5, 5, -5),
				LookAt(0.0f, 0.0f, 0.0f)
			{}

			LevelInfo(const LevelInfo & other)
			{
				_DeepCopy(other);
			}

			LevelInfo & operator = (const LevelInfo & other)
			{
				if (this != &other)
				{
					_DeepCopy(other);
				}
				return *this;
			}

			void Clear()
			{
				LevelFilename = "";
				Gravity.set(0.0f, -9.8f, 0.0f);
				CameraType = CAMERA_DEFAULT;
				MinView = 0.1f;
				MaxView = 1000.0f;
				ToFollow = "";
				FollowDistance = 10.0f;
				FollowHeight = 5.0f;
				Position.set(-5, 5, -5);
				LookAt.set(0.0f, 0.0f, 0.0f);
			}

		private:
			void _DeepCopy(const LevelInfo & other)
			{
				LevelFilename = other.LevelFilename;
				Gravity = other.Gravity;
				CameraType = other.CameraType;
				MinView = other.MinView;
				MaxView = other.MaxView;
				ToFollow = other.ToFollow;
				FollowDistance = other.FollowDistance;
				FollowHeight = other.FollowHeight;
				Position = other.Position;
				LookAt = other.LookAt;
			}
		};

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

			/**
			* Stores all the information needed to create a level.
			*/
			LevelInfo _levelInfo;

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
			*		_isParsed to false. If this function is overridden it is your responsibility as 
			*		an implementor of this interface to ensure these are set.
			*/
			BIO_ENGINE_API virtual void Clear();

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
			* Get a copy of the LevelInfo struct which has all the information for this level.
			*
			* @return Returns a LevelInfo struct with the information for this level.
			*/
			BIO_ENGINE_API LevelInfo GetLevelInfo();

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
			* which is retrieved using the GetLevelInfo function.
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

			/**
			* Set the LevelInfo to be used in creating the level.
			*
			* @param[in] info A LevelInfo struct that stores all the needed info for loading a 
			*				level.
			*/
			BIO_ENGINE_API void SetLevelInfo(const LevelInfo & info);
		};
	}
}//end namespace BIO

inline BIO::ENGINE::ILevelLoader::ILevelLoader() : _error(OK), _filename(), _isParsed(false), _levelInfo()
{
	BIO_LOG_INFO("ILevelLoader Constructed");
}

inline BIO::ENGINE::ILevelLoader::ILevelLoader(std::string filename) : _error(OK), _filename(filename), _isParsed(false), _levelInfo()
{
	BIO_LOG_INFO("ILevelLoader Constructed");
}

inline BIO::ENGINE::ILevelLoader::ILevelLoader(const char * filename) : _error(OK), _filename(filename), _isParsed(false), _levelInfo()
{
	BIO_LOG_INFO("ILevelLoader Constructed");
}

inline BIO::ENGINE::ILevelLoader::~ILevelLoader()
{
	BIO_LOG_INFO("Destroying ILevelLoader");
	Clear();
	_filename = "";
}

inline void BIO::ENGINE::ILevelLoader::Clear()
{
	_levelInfo.Clear();
	_error = OK;
	_isParsed = false;
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

inline BIO::ENGINE::LevelInfo BIO::ENGINE::ILevelLoader::GetLevelInfo()
{
	return _levelInfo;
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

inline void BIO::ENGINE::ILevelLoader::SetLevelInfo(const LevelInfo & info)
{
	_levelInfo = info;
}

#endif //___BIO_ENGINE_ILEVELLOADER_HPP__2015___

