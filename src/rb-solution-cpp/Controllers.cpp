#include <crow.h>
#include "Controllers.hpp"

static void Controllers::payments(void) const
{
	crow::json::wvalue res({
		{"message", "Mr. Stomach is not in home."}
	});

	res.code = 202;

	return res;
}
