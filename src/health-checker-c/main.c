#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include "exit-codes.h"
#include "checker.h"
#include "cache.h"
#include "response.h"

#define HASHKEY argv[1]
#define URL     argv[2]

void cleanup(void){
	free_checker();
	free_cache_connection();
	free_response();
}

void sigterm_handler(int code){
	exit(EXIT_OK);
}

int main(int argc, char *argv[]){
	switch(argc){
		case 1: return EXIT_AUX_HASHEY_NOT_SPECIFIED;
		case 2: return EXIT_AUX_URL_NOT_SPECIFIED;
	}

	atexit(cleanup);
	signal(SIGTERM, sigterm_handler);

	connect_cache(HASHKEY);
	start_checker(URL);

	ResponseJSON *response;

	while(true){
		// string to ReponseJSON
		response = extract_json_data(
			// get json as a string
			check_payment_health(URL)
		);
		update_cache(
			HASHKEY,
			response->failing,
			response->minResponseTime
		);

		sleep(5);
	}

	return EXIT_OK;
}
