#pragma once

static void check_connection_error(void);

void connect_cache(const char *hashkey);
void update_cache(const char *hashkey, bool failing, int minResponseTime);
void free_cache_connection(void);
