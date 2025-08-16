#include <crow.h>

#define PORT argv[1]

int main(int argc, char *argv[]){
	if(argc == 1)
		return EXIT_SOLUTION_NO_PORT;

	crow::SimpleApp app;

	app.router_dynamic([](){
		return "Hello world!";
	});

	app.port(PORT)
		.multithreaded()
		.run();
}
