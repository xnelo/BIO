/**
* @file Logger.cpp
* @author Spencer Hoffa
*
* All the needed logging functions.
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
#include "Logger.hpp"

#if BIO_LOGGING_IS_ENABLED == BIO_LOGGING_ON

#define BIO_LOGGER_INITIAL_BUFFER_SIZE 512
#include <iostream>
#include <ctime>

namespace BIO
{
	namespace LOGGING
	{
		/**The stream to print logging statements to.*/
		std::ostream * _output = &std::cout;

		/**Has the init function already been called?*/
		bool _initCalled = false;

		/**Keeps track of the current logging level*/
		int _level = MaxLoggingLevel;

		///////////////////////////////////////////////////////////////////////////////////////////
		//
		//					PRIVATE FUNCTIONS
		//
		///////////////////////////////////////////////////////////////////////////////////////////
		/**
		* Get the string equivalant of the logging level. This is a private function to this 
		* library.
		*
		* @param[in] level The LOGGING_LEVEL we need the string equivalant to.
		*
		* @return Returns a C-String with the current levels name.
		*/
		inline char * _GetLoggingLevelString(int level)
		{
			switch (level)
			{
			case BIO_LOGGER_LEVEL_OFF:
				return "OFF";
			case BIO_LOGGER_LEVEL_CRITICAL:
				return "CRITICAL";
			case BIO_LOGGER_LEVEL_ERROR:
				return "ERROR";
			case BIO_LOGGER_LEVEL_WARNING:
				return "WARNING";
			case BIO_LOGGER_LEVEL_INFO:
				return "INFO";
				//case XNELO_LOGGING_MESSAGE:--This is taken care of by the 
				//XNELO_LOGGING_INFO... They are equal
			case BIO_LOGGER_LEVEL_DEBUG:
				return "DEBUG1";
				//case DEBUG1:--This is taken care of by the Debug
			case BIO_LOGGER_LEVEL_DEBUG2:
				return "DEBUG2";
			case BIO_LOGGER_LEVEL_DEBUG3:
				return "DEBUG3";
			case BIO_LOGGER_LEVEL_DEBUG4:
				return "DEBUG4";
			default:
				return "DEBUG>4";
			}
		}

		/**
		* This is what takes the format string and all variables passed in for it and creates the 
		* log that get printed to the logging stream. This is a  private function to this library.
		*
		* @param[in] format A C-String with formatting chars to replace.
		*
		* @param[in] args The list of args that will be placed into the format string.
		*
		* @return Returns a C-String with the final string. This string is created on the heap. The 
		*			caller is responsible for deleting it when finished.
		*/
		inline char * _LogInternal(const char * format, va_list args)
		{
			size_t size = BIO_LOGGER_INITIAL_BUFFER_SIZE;

			int charsPrinted;
			char * buffer;

			while (1)
			{
				buffer = new char[size];
				#if BIO_CORE_PLATFORM == BIO_CORE_WINDOWS
					charsPrinted = vsnprintf_s(buffer, size, _TRUNCATE, format, args);
					//check if all the chars were printed.
					if (charsPrinted != -1)
						break;
				#else //Not windows
					charsPrinted = vsnprintf(buffer, size, format, args);
					//check if all the chars were printed.
					if ((charsPrinted != -1) && (charsPrinted < size))
						break;
				#endif

				//std::cout << "Increasing size" << std::endl;
				//delete the old buffer, increase size, and start over.
				delete buffer;
				size = size * 2;
			}

			return buffer;
		}

		/**
		* Generate the current time to place into the log output. This is a private function for 
		* the BIO LOGGING LIBRARY.
		*
		* @return Returns a C-String with the current time. This string is created on the heap. The 
		*			caller is responsible for deleteing it when done.
		*/
		inline char * _LogInternalTime()
		{
			unsigned int buffer_length = 80;

			time_t rawtime;
			struct tm * timeinfo = NULL;
			char * buffer = new char[buffer_length];
			memset(buffer, 0, sizeof(char)* buffer_length);

			time(&rawtime);

			#if BIO_CORE_PLATFORM == BIO_CORE_WINDOWS
				timeinfo = new struct tm;
				localtime_s(timeinfo, &rawtime);
			#else //Not windows
				timeinfo = localtime(&rawtime);
			#endif

			strftime(buffer, buffer_length, "%H:%M:%S", timeinfo);

			delete timeinfo;

			return buffer;
		}

		/**
		* Get the filename only. This function will stripp of all the directories from an 
		* absolute/relative filepath. This is a private function for this libary.
		*
		* @param filename The filename to strip down. Most likely __FILE__ macro
		*
		* @return Returns a char * with the stripped down filename. The returned value will be 
		*			allocated on the stack. The user is responsible for deleting the returned 
		*			pointer.
		*/
		char * _StripPath(const char * filename)
		{
			int filenameLength = strlen(filename);
			int fileStart = filenameLength;
			for (; fileStart >= 0; fileStart--)
			{
				if ((filename[fileStart] == '\\') || (filename[fileStart] == '/'))
				{
					break;
				}
			}

			fileStart++;

			int finalLength = filenameLength - fileStart;
			char * returnVal = new char[finalLength + 1];

			int counter = 0;
			for (int i = fileStart; i < filenameLength; i++)
			{
				returnVal[counter] = filename[i];
				counter++;
			}

			returnVal[finalLength] = '\0';

			return returnVal;
		}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		//				End Private Functions
		///////////////////////////////////////////////////////////////////////////////////////////

		void Init(int level, std::ostream * stream)
		{
			if (_initCalled)
			{
				Log(BIO_LOGGER_LEVEL_WARNING, 
					__LINE__, 
					__FILE__, 
					"Init has already been called. Exiting Init");
				return;
			}

			if (stream == NULL)
				_output = &std::cout;
			else
				_output = stream;

			SetLoggingLevel(level);

			(*_output) <<
				" -----------------------------------\n" <<
				"| Initializing BIO Logger           |\n" <<
				" -----------------------------------\n";

			_initCalled = true;

			atexit(Shutdown);
		}

		void Log(int level, const char * format, ...)
		{
			if (level > _level)
				return;

			va_list args;
			va_start(args, format);

			char * buffer = _LogInternal(format, args);

			va_end(args);

			(*_output) << "[" << _GetLoggingLevelString(level) << "]: " << buffer << std::endl;
			_output->flush();

			delete buffer;
		}

		void Log(int level, unsigned int line, const char * filename, const char * format, ...)
		{
			if (level > _level)
				return;

			va_list args;
			va_start(args, format);

			char * buffer = _LogInternal(format, args);
			char * bufferTime = _LogInternalTime();

			va_end(args);

			char * finalFilename = _StripPath(filename);
			(*_output) << "[" <<
				bufferTime << " " <<
				_GetLoggingLevelString(level) << " " <<
				finalFilename << " " <<
				line << "]: " <<
				buffer << std::endl;

			_output->flush();//std::cout.flush();

			delete finalFilename;
			delete buffer;
			delete bufferTime;
		}

		void SetLoggingLevel(int level)
		{
			if (level <= 0)
			{
				_level = 0;
				return;
			}


			if (level > MaxLoggingLevel)
			{
				_level = MaxLoggingLevel;
				return;
			}

			_level = level;
		}

		void Shutdown()
		{
			if (_initCalled == false)
				return; //no need to shutdown

			(*_output) <<
				" -----------------------------------\n" <<
				"| Shutting Down BIO Logger          |\n" <<
				" -----------------------------------\n";

			_output = &std::cout;

			_initCalled = false;
		}
	}//end namespace LOGGING
}//end namespace BIO

#else
//define empyt implementations
inline void BIO::LOGGING::Init(int level, std::ostream * stream){}
inline void BIO::LOGGING::Log(int level, unsigned int line, const char * filename, const char * format, ...){}
inline void BIO::LOGGING::Log(int level, const char * format, ...){}
inline void BIO::LOGGING::SetLoggingLevel(int level){}
inline void BIO::LOGGING::Shutdown(){}

#endif //BIO_LOGGING_IS_ENABLED