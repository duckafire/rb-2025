#include <crow.h>
#include "Controllers.hpp"
#include "cache/AvailabilityChecker.hpp"
#include "CurlEasy.hpp"

crow::response Controllers::payments(crow::request &req) const
{
	crow::response res { 202 };
	AvailabilityChecker checker;

	const char *url = checker.get_best_payment_server();

	if(url == NULL)
	{
		// TODO: add in the cache queue
		return res;
	}

	CurlEasy requester{ url };
	requester.execute_request( /* TODO: extract JSON from `req` */ );

	// TODO: add operation to the register (cache)

	return res;
}
