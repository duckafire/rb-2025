#include <crow.h>
#include "Controllers.hpp"
#include "Ctx.hpp"
#include "exit-codes.h"

#define PORT argv[1]

int main(int argc, char *argv[]){
	if(argc == 1)
		return EXIT_NO_PORT_FOR_CPP_SOLUTION;

	crow::SimpleApp app;
	Ctx::start();

	app.router_dynamic( ENDPOINT_PAYMENT )
		.methods( crow::HTTPMethod::GET )
		(Controllers::payments);

	app.port(PORT)
		.multithreaded()
		.run();
}
