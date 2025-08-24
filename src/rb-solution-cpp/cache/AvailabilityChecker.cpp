#include <valkey/valkey.h>
#include "AvailabilityChecker.hpp"
#include "PaymentStatus.hpp"
#include "../Ctx.hpp"

AvailabilityChecker::AvailabilityChecker(void)
{
	this->context = Ctx::valkey();
	this->paymDef = new PaymentStatus("paym-def");
	this->paymFal = new PaymentStatus("paym-fal");
}

AvailabilityChecker::~AvailabilityChecker(void)
{
	delete this->paymDef;
	delete this->paymFal;
}

char* get_best_payment_server(void) const
{
	int paymDefDelay = -1;
	int paymFalDelay = -1;


	if(this->paymDef->is_available())
		paymDefDelay = this->paymDef->get_min_response_time();

	if(this->paymFal->is_available())
		paymFalDelay = this->paymFal->get_min_response_time();


	if(paymDefDelay != -1 && paymDefDelay <= paymFalDelay)
		return PAYM_DEF_URL_PAY;

	if(paymFalDelay != -1)
		return PAYM_FAL_URL_PAY;

	// fallback delay in lower, but it is inavailable
	if(paymDefDelay != -1)
		return PAYM_DEF_URL_PAY;

	return NULL;
}
