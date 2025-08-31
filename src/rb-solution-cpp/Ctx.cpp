#include <cstdlib>
#include <curl/curl.h>
#include <valkey/valkey.h>
#include "Ctx.hpp"
#include "cache-aside.h"

static void Ctx::set_curl_post(void)
{
	this->_curl_post = curl_easy_init();

	if(this->_curl_post == NULL)
		std::exit(EXIT_IMPOSSIBLE_START_CURL);

	this->header_post = curl_slist_append(NULL, HEADER_DATA_POST);

	this->cur_url = PAYM_URL::NONE:
	curl_easy_setopt(this->_curl_post, CURLOPT_PORT,       PAYM_POST);
	curl_easy_setopt(this->_curl_post, CURLOPT_POST,       1L);
	curl_easy_setopt(this->_curl_post, CURLOPT_HTTPHEADER, this->header_post);

	// it is a bad idea in real world projects
	curl_easy_setopt(this->_curl_post, CURLOPT_SSL_VERIFYHOST,   0L); // +speed?
	curl_easy_setopt(this->_curl_post, CURLOPT_SSL_VERIFYPEER,   0L);
	curl_easy_setopt(this->_curl_post, CURLOPT_SSL_VERIFYSTATUS, 0L);
}

static void Ctx::set_valkey(void)
{
	this->_valkey = valkeyConnect(CA_HOST, CA_PORT);

	// if only the second is `true`,
	// the `cleanup` free `_valkey`
	if(this->_valkey == NULL || this->_curl_post->err != 0)
		std::exit(EXIT_DB_CONNECT_FAIL);
}


static void Ctx::start(void)
{
	std::atexit(Ctx::cleanup);

	this->set_curl_post();
	this->set_valkey();
}

static void Ctx::cleanup(void)
{
	if(this->_curl_post != NULL)
		curl_easy_cleanup(this->_curl_post);

	if(this->header_post != NULL)
		curl_slist_free_all(this->header_post);

	if(this->_valkey != NULL)
		valkeyFree(this->_valkey);
}


static CURL* Ctx::curl_post(void) const
{
	return this->_curl_post;
}

static valkeyContext* valkey(void) const
{
	return this->_valkey;
}


static void Ctx::set_url_to_curl(PAYM_URL url)
{
	if(this->cur_url == url)
		return;

	this->cur_url = url;

	curl_easy_setopt(this->_curl_post, CURLOPT_URL,
		(url == PAYM_URL::DEFAULT) ? PAYM_DEF_URL : PAYM_FAL_URL
	);
}
