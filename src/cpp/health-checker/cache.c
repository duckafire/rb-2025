#include <stdlib.h>
#include <stdbool.h>
#include <valkey/valkey.h>
#include "exit-codes.h"
#include "cache-aside.h"
#include "cache.h"

static valkeyContext *ctx = NULL;

static void check_connection_error(void)
{
	if(ctx != NULL && ctx->err == 0)
		return;

	exit(EXIT_DB_CONNECT_FAIL);
}

void update_cache(const char *hashkey, bool failing, int minResponseTime)
{
	valkeyReply *reply;

	// If the payment processor failing after `failing`
	// to be defined as `false` (0), the "main program"
	// will define `failing-after-checking` as `true` (1).
	// It will continue `true` until that this "auxiliar
	// program" run again.
	// The "main program" will check these two hash-keys
	// and only then it will do its work.
	// It was thinked to low the impact caused by the
	// endpoint ("/payment/service-health") delay.
	reply = valkeyCommand(
		ctx,
			"HSET %s "
			CA_HFIELD_FAILING_AFTER " %hd "
			CA_HFIELD_FAILING       " %hd "
			CA_HFIELD_MIN_RES_TIME  " %d",
		hashkey,
		0,
		failing,
		minResponseTime
	);

	if(reply != NULL)
		freeReplyObject(reply);
}

void connect_cache(const char *hashkey)
{
	ctx = valkeyConnect(CA_HOST, CA_PORT);
	check_connection_error();
	update_cache(hashkey, false, 0); // avoid "nil"
}

void free_cache_connection(void)
{
	if(ctx != NULL)
		valkeyFree(ctx);
}
