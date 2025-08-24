#pragma once

#include <crow.h>

#define ENDPOINT_PAYMENT "/payments"

class Controllers
{
public:
	//static void payment(const crow::request &req) const;
	static void payments(void) const;
};
