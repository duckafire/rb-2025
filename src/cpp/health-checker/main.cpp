#include <cstdlib>
#include <unistd.h>
#include "exit-codes.hpp"
#include "checker.hpp"
#include "cache.hpp"
#include "response.hpp"

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
		case 1: return EXIT::AUX_HASHEY_NOT_SPECIFIED;
		case 2: return EXIT::AUX_URL_NOT_SPECIFIED;
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

	return EXIT::OK;
}
