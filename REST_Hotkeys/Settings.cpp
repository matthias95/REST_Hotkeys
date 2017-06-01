/**
@author Matthias Bernard
@date May 2017
*/

#include "Settings.h"
namespace resthotkeys
{
	const std::vector<HotKeyData> Settings::readHotKeyData()
	{
		std::ifstream settingsFile;
		settingsFile.open(fileName, std::ios::in);
		if (!settingsFile.is_open())
		{
			throw std::exception(("failed to open file: " + std::string(fileName.begin(), fileName.end())).c_str());
		}

		std::vector<HotKeyData> res;

		web::json::array settingJsonArray = web::json::value::parse(settingsFile).as_array();
		for (auto iter = settingJsonArray.cbegin(); iter != settingJsonArray.cend(); ++iter)
		{
			res.push_back(*iter);
		}
		settingsFile.close();
		return res;
	};


	const void Settings::writeDefaultSettingsFile()
	{
		std::wfstream settingsFile;
		settingsFile.open(fileName, std::ios::out | std::ios::trunc);
		if (!settingsFile.is_open())
		{
			throw std::exception(("failed to open file: " + std::string(fileName.begin(), fileName.end())).c_str());
		}
		settingsFile << "// trigger HTTP Request by pressing  ALT + <key>" << std::endl;
		settingsFile << "// for <key> the keys 0-9 and F1-F12 are supported" << std::endl;
		settingsFile << "// for <method> POST, GET, PUT or DEL are supported" << std::endl;
		settingsFile << "// <data> is the data which is send with the request e.g POST data" << std::endl;


		web::json::value el1;
		el1[HotKeyData::KEY] = web::json::value::string(L"1");
		el1[HotKeyData::URL] = web::json::value::string(L"http://127.0.0.1");
		el1[HotKeyData::DATA] = web::json::value::string(L"foo");
		el1[HotKeyData::METHOD] = web::json::value::string(L"POST");

		web::json::value el2;
		el2[HotKeyData::KEY] = web::json::value::string(L"2");
		el2[HotKeyData::URL] = web::json::value::string(L"http://127.0.0.1/index.php?command=bar");
		el2[HotKeyData::DATA] = web::json::value::string(L"");
		el2[HotKeyData::METHOD] = web::json::value::string(L"GET");

		web::json::value el3;
		el3[HotKeyData::KEY] = web::json::value::string(L"3");
		el3[HotKeyData::URL] = web::json::value::string(L"http://127.0.0.1/index.php");
		el3[HotKeyData::DATA] = web::json::value::string(L"'name'='foo';'data'='bar'");
		el3[HotKeyData::METHOD] = web::json::value::string(L"PUT");
		std::vector<web::json::value> vec{ el1, el2, el3 };

		std::wstring jsonString{ web::json::value::array(vec).serialize() };
		Utils::replaceAll(jsonString, std::wstring(L","), std::wstring(L",\n"));
		Utils::replaceAll(jsonString, std::wstring(L"["), std::wstring(L"[\n"));
		Utils::replaceAll(jsonString, std::wstring(L"]"), std::wstring(L"\n]"));
		Utils::replaceAll(jsonString, std::wstring(L"{"), std::wstring(L"{\n"));
		Utils::replaceAll(jsonString, std::wstring(L"}"), std::wstring(L"\n}"));
		settingsFile << jsonString;
		settingsFile.close();
	};
}