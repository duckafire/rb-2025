#include <valkey/valkey.h>
#include "AvailabilityChecker.hpp"
#include "PaymentStatus.hpp"
#include "CacheContext.hpp"
#include "payment-processors.hpp"

AvailabilityChecker::AvailabilityChecker(void)
{
	this->context = CacheContext::get();
	this->paymDef = new PaymentStatus("paym-def");
	this->paymFal = new PaymentStatus("paym-fal");
}

AvailabilityChecker::~AvailabilityChecker(void)
{
	delete this->paymDef;
	delete this->paymFal;
}

char* AvailabilityChecker::get_best_payment_server(void) const
{
	int paymDefDelay = -1;
	int paymFalDelay = -1;


	if(this->paymDef->is_available())
		paymDefDelay = this->paymDef->get_min_response_time();

	if(this->paymFal->is_available())
		paymFalDelay = this->paymFal->get_min_response_time();


	if(paymDefDelay != -1 && paymDefDelay <= paymFalDelay)
		return PP_DEF_URL;

	if(paymFalDelay != -1)
		return PP_FAL_URL;

	// fallback delay in lower, but it is inavailable
	if(paymDefDelay != -1)
		return PP_DEF_URL;

	return NULL;
}
