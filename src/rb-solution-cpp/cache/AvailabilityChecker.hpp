#pragma once

#include <cstddef>
#include <valkey/valkey.h>
#include "PaymentStatus.hpp"

#define PAYM_DEF_URL_PAY "http://payment-processor-default:8080/payments"
#define PAYM_FAL_URL_PAY "http://payment-processor-fallback:8080/payments"

class AvailabilityChecker {
private:
	valkeyContext &context;
	PaymentStatus *paymDef;
	PaymentStatus *paymFal;

public:
	AvailabilityChecker(void);

	~AvailabilityChecker(void);

	char* get_best_payment_server(void);
};
