#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "exit-codes.h"
#include "checker.h"
#include "cache.h"
#include "response.h"

#define HASHKEY argv[1]
#define URL     argv[2]

void cleanup(void)
{
	free_checker();
	free_cache_connection();
	free_response();
}

int main(int argc, char *argv[])
{
	switch(argc)
	{
		case 1: return EXIT_AUX_HASHEY_NOT_SPECIFIED;
		case 2: return EXIT_AUX_URL_NOT_SPECIFIED;
	}

	atexit(cleanup);

	connect_cache(HASHKEY);
	start_checker(URL);

	ResponseJSON *response;

	while(true)
	{
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
