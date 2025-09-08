#pragma once

#include <curl/curl.h>

class CurlEasy
{
private:
	// ConTeXt
	CURL *context;

	// HeaDeR
	static const struct curl_slist *header = curl_slist_append(
		NULL,
		"Content-Type: application/json; charset=ascii"
	);

public:
	CurlEasy(const char *url);
	~CurlEasy(void);

	bool execute_request(const char *json);
};
