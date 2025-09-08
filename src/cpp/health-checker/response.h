#pragma once

#include <stdbool.h>

typedef struct
{
	bool failing;
	int minResponseTime;
} ResponseJSON;

ResponseJSON* extract_json_data(char *data);
void free_response(void);
