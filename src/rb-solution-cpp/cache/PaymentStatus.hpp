#pragma once

#include <valkey/valkey.h>

#define MAX_FAILING_KEYS 2

class PaymentStatus {
private:
	valkeyContext *context;
	const char *hashkey;

	static const char *const minResponseTime = "minResponseTime";
	static const char *const failingKeys[MAX_FAILING_KEYS] = {
		"failing-after-checking",
		"failing",
	};

public:
	PaymentStatus(const char*);

	bool is_available(void);
	int get_min_response_time(void);
};
