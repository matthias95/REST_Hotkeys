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

		const std::vector<HotKeyData> readHotKeyData();
		const void writeDefaultSettingsFile();

	private:
		const std::wstring fileName;
	};
}
