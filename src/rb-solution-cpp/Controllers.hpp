#pragma once

#include <crow.h>

class Controllers
{
public:
	static crow::response payment(const crow::request &req) const;
};
