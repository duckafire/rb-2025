#pragma once

typedef struct
{
	bool failing;
	int minResponseTime;
} ResponseJSON;

ResponseJSON* extract_json_data(const char *data);
void free_response(void);
