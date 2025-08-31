#include <curl/curl.h>
#include "CurlEasy.hpp"
#include "exit-codes.h"
#include "payment-processors.h"

CurlEasy::CurlEasy(const char *url)
{
	this->context = curl_easy_init();

	if(this->context == NULL)
		std::exit(EXIT_IMPOSSIBLE_START_CURL);

	this->cur_url = PAYM_URL::NONE;
	curl_easy_setopt(this->context, CURLOPT_POST,       1L);
	curl_easy_setopt(this->context, CURLOPT_PORT,       PP_PORT);
	curl_easy_setopt(this->context, CURLOPT_HTTPHEADER, CurlEasy::header);

	// it is a bad idea in real world projects
	curl_easy_setopt(this->context, CURLOPT_SSL_VERIFYHOST,   0L); // +speed?
	curl_easy_setopt(this->context, CURLOPT_SSL_VERIFYPEER,   0L);
	curl_easy_setopt(this->context, CURLOPT_SSL_VERIFYSTATUS, 0L);
}

CurlEasy::~CurlEasy(void)
{
	if(this->context != NULL)
		curl_easy_cleanup(this->context);
}

bool CurlEasy::execute_request(const char *json)
{
	curl_easy_setopt(this->context, CURLOPT_POSTFIELDS, json);

	if(curl_easy_perfom( this->context ) != CURL_OK)
		exit(EXIT_SOME_CURL_ERROR);

	long httpcode = 0;
	curl_easy_getinfo(this->context, CURLINFO_RESPONSE_CODE, &httpcode);

	return (httpcode != 500);
}
