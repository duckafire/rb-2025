#include <valkey/valkey.h>
#include "CacheContext.hpp"
#include "cache-aside.hpp"

static void CacheContext::start(void)
{
	if(CacheContext::context != NULL)
		return;

	CacheContext::context = valkeyConnect(CA_HOST, CA_PORT);

	if(CacheContext::context == NULL || this->_curl_post->err != 0)
		std::exit(EXIT_DB_CONNECT_FAIL);
}

static valkeyContext* CacheContext::get(void) const
{
	return CacheContext::context;
}
