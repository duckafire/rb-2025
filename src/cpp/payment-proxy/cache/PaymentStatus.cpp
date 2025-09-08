#include <cstdlib>
#include "PaymentStatus.hpp"
#include "CacheContext.hpp"

PaymentStatus::PaymentStatus(const char *hk):
		hashkey(hk)
{
	this->context = CacheContext::get();
}

bool PaymentStatus::is_available(void) const
{
	valkeyReply *reply;

	for(short i = 0; i < MAX_FAILING_KEYS; i++)
	{
		reply = valkeyCommand("HGET %s %s", this->hashkey, PaymentStatus::failingKeys[i]);
		
		// `true` == it is unavailable
		if(reply->str[0] == '1')
		{
			freeReplyObject(reply);
			return false;
		}

		freeReplyObject(reply);
	}

	return true;
}

int PaymentStatus::get_min_response_time(void) const
{
	valkeyReply *reply = valkeyCommand("HGET %s %s", this->hashkey, PaymentStatus::minResponseTime);

	float minResponseTime = std::strtof(this->reply->str, NULL);

	freeReplyObject(reply);
	return minResponseTime;
}
