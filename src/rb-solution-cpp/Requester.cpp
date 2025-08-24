#include <curl/curl.h>
#include "Requester.hpp"
#include "Ctx.hpp"

static CURL *Requester::context = Ctx::curl();

static bool Requester::send_payment(const char *json)
{
	curl_easy_setopt(this->context, CURLOPT_POSTFIELDS, json);

	if(curl_easy_perform(this->context) != CURL_OK)
		exit(EXIT_SOME_CURL_ERROR);

	long httpcode = 0;
	curl_easy_getinfo(this->context, CURLINFO_RESPONSE_CODE, &httpcode);

	if(httpcode == 500)
		return false;

	return true;
}

