/**
* @file FileUtils.hpp
* @author Spencer Hoffa
*
* File utilities for the BIO library
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

#ifndef ___BIO_CORE_FILEUTILS_HPP__2015___
#define ___BIO_CORE_FILEUTILS_HPP__2015___

#include <string>
#include <sys\stat.h>
#include <cstdio>

#include "Config.h"
#include "Logger.hpp"

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
#include "../../Xnelo-Testing/include/Testing.hpp"
#include <fstream>
#endif

namespace BIO
{
	namespace FILE
	{
		/**
		* Delete a file from the hard disk.
		*
		* @param filename The name of the file to delete.
		*
		* @return Returns true if the file was deleted successfully. False otherwise.
		*/
		bool DeleteFile(std::string filename);
		bool DeleteFile(const char * filename);

		/**
		* Check to see if a file exists.
		*
		* @param file The name of the file to check for.
		*
		* @return Returns true if the file is at the specified location,
		*			otherwise false is returned.
		*/
		bool FileExists(std::string file);
		bool FileExists(const char * file);

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
		bool FileUtilsTests(XNELO::TESTING::Test * test);
#endif
	} //end namespace file
} //end namespace BIO

inline bool BIO::FILE::DeleteFile(std::string filename)
{
	return DeleteFile(filename.c_str());
}

inline bool BIO::FILE::DeleteFile(const char * filename)
{
	int returnCode = remove(filename);

	if (returnCode != 0)
	{
		//error
		BIO_LOG_ERROR("Error deleting '%s'.", filename);
		BIO_LOG_DEBUG("Error code: %i", errno);
		return false;
	}

	return true;
}

inline bool BIO::FILE::FileExists(std::string file)
{
	return FileExists(file.c_str());
}

inline bool BIO::FILE::FileExists(const char * file)
{
	struct stat buffer;
	return (stat(file, &buffer) == 0);
}

#if BIO_TESTING_IS_ENABLED == BIO_TESTING_ON
inline bool BIO::FILE::FileUtilsTests(XNELO::TESTING::Test * test)
{
	test->SetName("FileUtils Tests");

	const char * Cfilename = "XYZ3k283ks8ale.CRP";
	std::string filename = Cfilename;

	//test file does not exists
	test->UnitTest(FileExists(Cfilename) == false, "Test file does not exist[1]");
	test->UnitTest(FileExists(filename) == false, "Test file does not exist[2]");

	//write a test file
	std::ofstream testFile;
	testFile.open(Cfilename);
	testFile << "This is a test file." << std::endl;
	testFile.close();

	//test that a file exists
	test->UnitTest(FileExists(Cfilename) == true, "Test file does exist[1]");
	test->UnitTest(FileExists(filename) == true, "Test file does exist[2]");

	//test deleting that file
	test->UnitTest(DeleteFile(Cfilename) == true, "Test delete file");
	test->UnitTest(DeleteFile(filename) == false, "Test delete file fails");

	return test->GetSuccess();
}
#endif

#endif //___BIO_CORE_FILEUTILS_HPP__2015___

