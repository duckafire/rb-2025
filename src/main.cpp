#include <iostream>
#include <cstdlib>
#include <crow.h>
#include <valkey/valkey.h>

int main(void){
    crow::SimpleApp app;
	valkeyContext *ctx = valkeyConnect("cache-db", 6379);

	const bool IS_AVAILABLE_CACHE = (ctx != NULL && ctx->err == 0);

	if(!IS_AVAILABLE_CACHE){
		std::cerr << "Valkey ERROR: " << (ctx == NULL ? "OOM" : ctx->errstr) << std::endl;
		
		if(ctx != NULL)
			valkeyFree(ctx);
	}else{
		// `"SET hw Hello world!"` (in this function below)
		// do not work and I do not why ;-;
		valkeyReply *reply = (valkeyReply*)valkeyCommand(ctx, "SET %s %s", "hw", "Hello world!");

		if(reply == NULL)
			std::cerr << "An error occur during the write access to the cache" << std::endl;
		else
			freeReplyObject(reply);
	}

    CROW_ROUTE(app, "/")([&ctx, &IS_AVAILABLE_CACHE](){
		valkeyReply *hw = NULL;
		
		if(IS_AVAILABLE_CACHE)
			hw = (valkeyReply*)valkeyCommand(ctx, "GET hw");

		std::string message(
			(!IS_AVAILABLE_CACHE ? "Cache unavailable" :
				(hw->str == NULL ? "Cache value not found" : hw->str)
			)
		);
		std::cout << message << std::endl;

		crow::json::wvalue res({
			{"message", message}
		});

		if(IS_AVAILABLE_CACHE)
			freeReplyObject(hw);

		return res;
    });

	// char* -> int -> uint16
	const std::uint16_t PORT = static_cast<std::uint16_t>(
		std::strtoull(std::getenv("PORT"), NULL, 10)
	);
    app.port(PORT).multithreaded().run();
}
