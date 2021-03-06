/**
@author Matthias Bernard
@date May 2017
*/

#include <windows.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <conio.h>
#include <cctype>

#include "HotKeyData.h"
#include "Settings.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

using namespace resthotkeys;

	int main(int argc, char* argv[])
	{

		ShowWindow(GetConsoleWindow(), SW_HIDE);
		std::wstringstream ss;
		ss << argv[0];
		ss << L"\\..\\settings.json";
		Settings settings(ss.str());

		/**
		* try to read settings.json and register hotkeys
		* than wait for hotkey in message queue
		*/
		try
		{
			auto vec = settings.readHotKeyData();

			/**
			* ALT + BACKSPACE toggels console window
			*/
			if (!RegisterHotKey(NULL, 0xff, MOD_ALT | MOD_NOREPEAT, 0x08 /*backspace*/))
			{
				throw std::exception("failed to register HotKey!");
			}

			for (int i = 0; i < vec.size(); ++i)
			{
				const HotKeyData& hotKeyData = vec[i];
				if (!RegisterHotKey(NULL, i, MOD_ALT | MOD_NOREPEAT, hotKeyData.getKeyCode()))
				{
					throw std::exception("failed to register HotKey!");
				}
			}

			MSG msg = { 0 };
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (msg.message == WM_HOTKEY)
				{
					std::cout << "HotKey Pressed!" << std::endl;
					if (msg.wParam >= 0 && msg.wParam < 0xff)
					{
						vec[msg.wParam].sendHttpRequest();
					}
					else if (msg.wParam == 0xff)
					{
						ShowWindow(GetConsoleWindow(), IsWindowVisible(GetConsoleWindow()) ? SW_HIDE : SW_SHOW);
					}
				}
			}
		}
		catch (std::exception &e)
		{
			ShowWindow(GetConsoleWindow(), SW_SHOW);
			std::wcout << e.what() << std::endl << std::endl;
			std::wcout << L"enter r to restore default settings file or e to exit: ";
			wchar_t c = std::toupper(std::wcin.get());
			switch (c)
			{
			case L'R':
				settings.writeDefaultSettingsFile();
				break;
			case L'E':
				break;
			default:
				break;
			}
		}

		return 0;
	}
