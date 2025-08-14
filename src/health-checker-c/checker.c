#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>
#include "exit-codes.h"
#include "checker.h"

static CURL *ctx = NULL;
static char *response = NULL;
struct curl_slist *header = NULL;

static void init(void){
	ctx = curl_easy_init();
	header = curl_slist_append(NULL, "Content-Type: application/json; charset=ascii");

	if(ctx == NULL)
		exit(EXIT_IMPOSSIBLE_START_CURL);
}

static size_t writefunction(char *data, size_t size, size_t dataSize, void *buf){
	free_json_response();
	size_t totalSize = size * dataSize;

	response = malloc(totalSize + sizeof(char));
	strncpy(response, data, totalSize);

	return size * dataSize;
}

static void setopt(const char *url){
	// GET by default
	curl_easy_setopt(ctx, CURLOPT_URL,               url);
	curl_easy_setopt(ctx, CURLOPT_PORT,             "8080");
	curl_easy_setopt(ctx, CURLOPT_DEFAULT_PROTOCOL, "http");
	curl_easy_setopt(ctx, CURLOPT_WRITEFUNCTION,     writefunction);
	curl_easy_setopt(ctx, CURLOPT_WRITEDATA,         NULL);
	curl_easy_setopt(ctx, CURLOPT_HTTPGET,           1L);

	// it is a bad idea in real world projects
	curl_easy_setopt(ctx, CURLOPT_SSL_VERIFYHOST, 0L); // +speed?
	curl_easy_setopt(ctx, CURLOPT_SSL_VERIFYPEER, 0L);
}

static void free_json_response(void){
	if(response == NULL)
		return;

	free(response);
	response = NULL;
}

void start_checker(const char *url){
	init();
	setopt(url);
}

char* check_payment_health(const char *url){
	if(curl_easy_perform(ctx) != CURLE_OK)
		exit(EXIT_SOME_CURL_ERROR);

	return response;
}

void free_checker(void){
	if(ctx != NULL)
		curl_easy_cleanup(ctx);

	if(header != NULL)
		curl_slist_free_all(header);

	free_json_response();
}
