#pragma once

#include <curl/curl.h>
#include <valkey/valkey.h>

#define CTX_URL_HEADER "Content-Type: application/json; charset=ascii"

enum PAYM_URL
{
	NONE,
	DEFAULT,
	FALLBACK,
};

class Ctx
{
private:
	static CURL *_curl_post = NULL;
	static struct curl_slist *header_post = NULL;
	static PAYM_CURL cur_url;

	static valkeyContext *_valkey = NULL;

	static void set_curl_post(void);
	static void set_valkey(void);

public:
	static void start(void);
	static void cleanup(void);

	static CURL* curl_post(void) const;
	static valkeyContext* valkey(void) const;

	static void set_url_to_curl(PAYM_URL url);
};
