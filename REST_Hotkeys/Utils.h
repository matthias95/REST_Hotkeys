/**
@author Matthias Bernard
@date May 2017
*/

#pragma once
#include <iostream>
#include <algorithm>
#include <string>

namespace resthotkeys
{
	class Utils 
	{
	public:
		template <typename STRING_TYPE>
		inline static STRING_TYPE& toUpper(STRING_TYPE& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
			return str;
		};

		template <typename STRING_TYPE>
		inline static STRING_TYPE toUpper(const STRING_TYPE& str)
		{
			STRING_TYPE res(str);

			std::transform(str.begin(), str.end(), res.begin(), ::toupper);
			return res;
		};

		template<typename STRING_TYPE>
		inline static STRING_TYPE& replaceAll(STRING_TYPE& str, STRING_TYPE& from, STRING_TYPE& to)
		{
			size_t pos = 0;
			for (;;)
			{
				pos = str.find(from, pos);
				if (pos == STRING_TYPE::npos)
					break;
				str.replace(pos, from.length(), to);
				pos += to.length();
			}
			return str;
		}
	};
}