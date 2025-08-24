#pragma once

#include <curl/curl.h>

class Requester
{
private:
	static CURL *context;

public:
	static bool send_payment(const char *json);
};
