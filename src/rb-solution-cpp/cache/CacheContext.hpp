#pragma once

#include <valkey/valkey.h>

class CacheContext
{
private:
	static valkeyContext *context = NULL;

public:
	static void start(void);
	static valkeyContext* get(void);
};
