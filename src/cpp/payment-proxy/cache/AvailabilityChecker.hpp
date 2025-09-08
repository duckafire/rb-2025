#pragma once

#include <cstddef>
#include <valkey/valkey.h>
#include "PaymentStatus.hpp"

class AvailabilityChecker
{
private:
	valkeyContext &context;
	PaymentStatus *paymDef;
	PaymentStatus *paymFal;

public:
	AvailabilityChecker(void);
	~AvailabilityChecker(void);

	char* get_best_payment_server(void) const;
};
