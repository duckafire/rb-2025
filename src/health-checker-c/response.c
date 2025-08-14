#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "response.h"

#define MAX_BREAKCHAR 3

static ResponseJSON *response = NULL;

ResponseJSON* extract_json_data(char *data){
	short breakchar = 0;
	bool getFailingField = true;

	short bufId = 0;
	char buf[6] = {0};

	free_response();
	response = malloc(sizeof(ResponseJSON));

	for(short i = 0; true; i++){
		if(breakchar < MAX_BREAKCHAR){
			if(data[i] == '"' || data[i] == ':')
				breakchar++;

			continue;
		}

		if(getFailingField){
			breakchar       = 0;
			getFailingField = false;

			response->failing = (data[i] == 't');
			continue;
		}

		if(data[i] == '}'){
			buf[ bufId ] = '\0';
			break;
		}

		buf[ bufId ] = data[i];
		bufId++;
	}

	response->minResponseTime = (int)strtoull(buf, NULL, 10);
	return response;
}

void free_response(void){
	if(response == NULL)
		return;

	free(response);
	response = NULL;
}
