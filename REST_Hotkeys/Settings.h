/**
@author Matthias Bernard
@date May 2017
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "HotKeyData.h"

namespace resthotkeys 
{
	class Settings
	{
	public:
		Settings(std::wstring fileName) : fileName(fileName) {};


		/**
		* read hotkeys defined in settings.json file
		* throws exception if settings.json file is malformed
		* @return std::vector containing HotKeyData objects
		*/
		const std::vector<HotKeyData> readHotKeyData();

		/**
		* write default settings.json file with some example hotkey definitions
		* throws exception if settings.json connot be written
		*/
		const void writeDefaultSettingsFile();

	private:
		const std::wstring fileName;
	};
}
