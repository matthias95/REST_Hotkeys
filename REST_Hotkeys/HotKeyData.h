/**
@author Matthias Bernard
@date May 2017
*/

#pragma once

#include <iostream>
#include <cpprest/http_client.h>
#include "Utils.h"

namespace resthotkeys 
{
	static const std::map<const std::wstring, const int> keyCodeMap{ { L"0",0x30 },{ L"1", 0x31 },{ L"2", 0x32 },{ L"3", 0x33 },{ L"4", 0x34 },{ L"5", 0x35 },{ L"6", 0x36 },{ L"7", 0x37 },{ L"8", 0x38 },{ L"9", 0x39 },{ L"F1", 0x70 },{ L"F2", 0x71 },{ L"F3", 0x72 },{ L"F4", 0x73 },{ L"F5", 0x74 },{ L"F6", 0x75 },{ L"F7", 0x76 },{ L"F8", 0x77 },{ L"F9", 0x78 },{ L"F10", 0x79 },{ L"F11", 0x7a },{ L"F12", 0x7b } };
	static const std::map<const std::wstring, const web::http::method> methodMap{ { L"GET", web::http::methods::GET },{ L"POST", web::http::methods::POST }, { L"PUT", web::http::methods::PUT },{ L"DEL", web::http::methods::DEL } };

	class HotKeyData 
	{
	public:
		static const std::wstring KEY;
		static const std::wstring URL;
		static const std::wstring DATA;
		static const std::wstring METHOD;

		HotKeyData(const web::json::value& jsonData);

		void sendHttpRequest();

		const int getKeyCode() const 
		{
			return keyCode;
		}
	 
	private:
		int keyCode;
		std::wstring url;
		std::wstring data;
		web::http::method method;
		web::http::client::http_client_config httpClientConfig;

	};
}
