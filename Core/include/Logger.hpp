/**
* @file logger.hpp
* @author Spencer Hoffa
*
* Holds all of the Logging definitions.
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
#ifndef ___BIO_CORE_LOGGER_HPP__2015___
#define ___BIO_CORE_LOGGER_HPP__2015___

#include "Config.h"
#include <ostream>
#include <stdarg.h>

//define the logging levels
#define BIO_LOGGER_LEVEL_OFF 0
#define BIO_LOGGER_LEVEL_CRITICAL 1
#define BIO_LOGGER_LEVEL_ERROR 2
#define BIO_LOGGER_LEVEL_WARNING 3
#define BIO_LOGGER_LEVEL_INFO 4
#define BIO_LOGGER_LEVEL_MESSAGE BIO_LOGGER_LEVEL_INFO
#define BIO_LOGGER_LEVEL_DEBUG 5
#define BIO_LOGGER_LEVEL_DEBUG1 BIO_LOGGER_LEVEL_DEBUG
#define BIO_LOGGER_LEVEL_DEBUG2 6
#define BIO_LOGGER_LEVEL_DEBUG3 7
#define BIO_LOGGER_LEVEL_DEBUG4 8

#ifndef BIO_LOGGER_MAX_LOGGING_LEVEL
#define BIO_LOGGER_MAX_LOGGING_LEVEL BIO_LOGGER_LEVEL_DEBUG4
#endif //BIO_LOGGER_MAX_LOGGING_LEVEL

namespace BIO
{
	namespace LOGGING
	{
		/**The maximum logging level allowed*/
		const int MaxLoggingLevel = BIO_LOGGER_MAX_LOGGING_LEVEL;

		/**
		* Initialize the Logger.
		*/
		BIO_CORE_API void Init(int level, std::ostream * stream = NULL);

		/**
		* Log a message. This function is similar to the printf strings in C. See printf 
		* documentation for formating information.
		*
		* @note See @link http://www.cplusplus.com/reference/cstdio/printf/ for details.
		*
		* @param[in] level The level of the  message being logged.
		* @param[in] filename The filename the logging is occuring in.
		* @param[in] line The file line number this log statement is in.
		* @param[in] format The formated string to be printed. See documentation of printf on how 
		*				to format a string.
		* @param[in] ... A variable number of arguments that are replaced in the parameter format. 
		*				These can be of any type. See documentation of printf for more details.
		*/
		BIO_CORE_API void Log(int level, unsigned int line, const char * filename, const char * format, ...);

		/**
		* Log a message. This function is similar to the printf strings in C. See printf 
		* documentation for formating information.
		*
		* @note See @link http://www.cplusplus.com/reference/cstdio/printf/ for details.
		*
		* @param[in] level The level of the  message being logged.
		* @param[in] format The formated string to be printed. See documentation of printf on how 
		*				to format a string.
		* @param[in] ... A variable number of arguments that are replaced in the parameter format. 
		*				These can be of any type. See documentation of printf for more details.
		*/
		BIO_CORE_API void Log(int level, const char * format, ...);

		/**
		* Set the logging level to use. Only logging levels that are equal to or less than the set 
		* value will be printed in the log.
		*
		* @param[in] level The new level to log to. If level > MaxLoggingLevel then the level will 
		*				be set to MaxLoggingLevel. If the new level < 0 then it will be set to 0.
		*/
		BIO_CORE_API void SetLoggingLevel(int level);

		/**
		* Shutdown logging. 
		*
		* @note There is no need to explicitly call this function. It will automatically be called 
		*		when the program exits. If it is called earlier nothing is done updon program exit.
		*/
		BIO_CORE_API void Shutdown();
	}//end namespace LOGGING
}//end namespace BIO

//define macros to use instead of the function calls
#if BIO_LOGGING_IS_ENABLED == BIO_LOGGING_ON

#define BIO_LOGGING_INIT(level, stream) BIO::LOGGING::Init(level, stream);

#define BIO_LOG(level, format, ...) BIO::LOGGING::Log(level, __LINE__, __FILE__, format, __VA_ARGS__);

#define BIO_LOG_CRITICAL(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_CRITICAL, format, __VA_ARGS__)
#define BIO_LOG_ERROR(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_ERROR, format, __VA_ARGS__)
#define BIO_LOG_WARNING(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_WARNING, format, __VA_ARGS__)
#define BIO_LOG_INFO(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_INFO, format, __VA_ARGS__)
#define BIO_LOG_MESSAGE(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_MESSAGE, format, __VA_ARGS__)
#define BIO_LOG_DEBUG_N(level, format, ...) BIO_LOG((level + BIO_LOGGER_LEVEL_INFO), format, __VA_ARGS__)
#define BIO_LOG_DEBUG(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_DEBUG, format, __VA_ARGS__)
#define BIO_LOG_DEBUG1(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_DEBUG1, format, __VA_ARGS__)
#define BIO_LOG_DEBUG2(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_DEBUG2, format, __VA_ARGS__)
#define BIO_LOG_DEBUG3(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_DEBUG3, format, __VA_ARGS__)
#define BIO_LOG_DEBUG4(format, ...) BIO_LOG(BIO_LOGGER_LEVEL_DEBUG4, format, __VA_ARGS__)

#define BIO_LOGGING_SET_LOGGING_LEVEL(level) BIO::LOGGING::SetLoggingLevel(level);

#define BIO_LOGGING_SHUTDOWN BIO::LOGGING::Shutdown();

#else //it's off
#define BIO_LOGGING_INIT(level, stream) //DO NOTHING

#define BIO_LOG(level, format, ...) //DO NOTHING

#define BIO_LOG_CRITICAL(format, ...) //DO NOTHING
#define BIO_LOG_ERROR(format, ...) //DO NOTHING
#define BIO_LOG_WARNING(format, ...) //DO NOTHING
#define BIO_LOG_INFO(format, ...) //DO NOTHING
#define BIO_LOG_MESSAGE(format, ...) //DO NOTHING
#define BIO_LOG_DEBUG_N(level, format, ...) //DO NOTHING
#define BIO_LOG_DEBUG(format, ...) //DO NOTHING
#define BIO_LOG_DEBUG1(format, ...) //DO NOTHING
#define BIO_LOG_DEBUG2(format, ...) //DO NOTHING
#define BIO_LOG_DEBUG3(format, ...) //DO NOTHING
#define BIO_LOG_DEBUG4(format, ...) //DO NOTHING

#define BIO_LOGGING_SET_LOGGING_LEVEL(level) //DO NOTHING

#define BIO_LOGGING_SHUTDOWN //DO NOTHING
#endif//BIO_LOGGING_IS_ENABLED

#endif //___BIO_CORE_LOGGER_HPP__2015___