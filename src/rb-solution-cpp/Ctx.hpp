#pragma once

#include <curl/curl.h>
#include <valkey/valkey.h>

#define PAYM_PORT "8080"
#define HEADER_DATA_POST "Content-Type: application/json; charset=ascii"

class Ctx {
private:
	static CURL *_curl_post = NULL;
	static struct curl_slist *header_post = NULL;

	static valkeyContext *_valkey = NULL;

	static void set_curl_post(void);
	static void set_valkey(void);

public:
	static void start(void);
	static void cleanup(void);

	static CURL* curl_post(void) const;
	static valkeyContext* valkey(void) const;
};
