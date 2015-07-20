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

#include "../rapidxml-1.13/rapidxml_utils.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"

#if BIOENGINE_TESTING_IS_ENABLED == BIOENGINE_TESTING_ON
#include <fstream>
#endif

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

			//parse the xml level file
			rapidxml::file<> xmlFile(_filename.c_str());
			rapidxml::xml_document<> doc;
			doc.parse<0>(xmlFile.data());

			_isParsed = true;

			_error = ERROR_NOT_IMPLEMENTED;
		}

		World * XMLLevelLoader::LoadLevel()
		{
			BIO_LOG_INFO("Loading Level");
			if (_isParsed == false)
			{
				BIO_LOG_DEBUG("Level not parsed... parse level");
				ParseLevel();
			}

			_error = ERROR_NOT_IMPLEMENTED;

			//now load the level
			return NULL;
		}

		bool XMLLevelLoader::Test(XNELO::TESTING::Test * test)
		{
			test->SetName("Tsting XMLLevelLoader class");

			//write the tests level
			std::string testFileName = "TESTLEVEL.level";
			std::ofstream testFile;
			testFile.open(testFileName);
			testFile << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" << std::endl
				<< "<LEVEL>" << std::endl
				<< "   <SETTINGS>" << std::endl
				<< "      <LEVELFILE>mainScreen.obj</LEVELFILE>" << std::endl
				<< "      <GRAVITY><VECTOR x=\"0.0\" y=\"- 9.8\" z=\"0.0\"/></GRAVITY>" << std::endl
				<< "      <LATITUDE><ANGLE type=\"DEGREES\" value=\"41\" /></LATITUDE>" << std::endl
				<< "   </SETTINGS>" << std::endl
				<< "   <!--" << std::endl
				<< "   <CAMERA type=\"Following\">" << std::endl
				<< "   <CAMERAFOLLOW>tank1</CAMERAFOLLOW>" << std::endl
				<< "   <FOLLOWDISTANCE>10.0</FOLLOWDISTANCE>" << std::endl
				<< "   <FOLLOWHEIGHT>5</FOLLOWHEIGHT>" << std::endl
				<< "   </CAMERA>" << std::endl
				<< "   -->" << std::endl
				<< "   <CAMERA type=\"Default\" minview=\"0.1\" maxview=\"1000.0\">" << std::endl
				<< "   <POSITION><VECTOR x=\"0.0\" y=\"3.0\" z=\"0.0\" /></POSITION>" << std::endl
				<< "   <LOOKAT><VECTOR x=\"0.0\" y=\"0.0\" z=\"0.0\" /></LOOKAT>" << std::endl
				<< "   </CAMERA>" << std::endl
				<< "</LEVEL>" << std::endl;
			testFile.close();


			XMLLevelLoader levelLoader;
			levelLoader.SetFilename(testFileName);
			levelLoader.ParseLevel();

			test->UnitTest(levelLoader.IsParsed() == true, "Test isParsed set correctly");

			return test->GetSuccess();
		}
	}//end namespace ENGINE
}//end namespace BIO

