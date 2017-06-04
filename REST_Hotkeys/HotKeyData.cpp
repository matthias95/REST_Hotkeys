/**
@author Matthias Bernard
@date May 2017
*/

#include "HotKeyData.h"

namespace resthotkeys
{
	const std::wstring HotKeyData::KEY{ L"key" };
	const std::wstring HotKeyData::URL{ L"url" };
	const std::wstring HotKeyData::DATA{ L"data" };
	const std::wstring HotKeyData::METHOD{ L"method" };


	/**
	* construct HotKeyData from jsonObject extracted from settings.json
	*/
	HotKeyData::HotKeyData(const web::json::value& jsonData) :
		keyCode{ keyCodeMap.at(Utils::toUpper(jsonData.at(KEY).as_string())) },
		url{ jsonData.at(URL).as_string() },
		data{ jsonData.at(DATA).as_string() },
		method{ methodMap.at(Utils::toUpper(jsonData.at(METHOD).as_string())) }
	{
		httpClientConfig.set_timeout(utility::seconds(3));

	};

	/**
	* send http request corresponding to hotkey
	*/
	void HotKeyData::sendHttpRequest()
	{
		web::http::client::http_client client{ url, httpClientConfig };
		web::http::http_request http_request;
		http_request.headers().add(L"Accept", L"application/json");
		http_request.headers().add(L"Content-Type", L"text/plain");
		http_request.set_body(data);
		http_request.set_method(method);

		auto requestTask = client.request(http_request).then([=](web::http::http_response response)
		{
			printf("Received response status code:%u\n", response.status_code());
		});

		try
		{
			requestTask.wait();
		}
		catch (const std::exception &e)
		{
			printf("Error exception:%s\n", e.what());
		}
	};
}