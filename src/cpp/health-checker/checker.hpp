#pragma once

#include <cstddef>
#include <curl/curl.h>

static void init(void);
static size_t writefunction(char *data, size_t size, size_t dataSize, void *buf);
static void setopt(const char *url);
static void free_json_response(void);

void start_checker(const char *url);
char* check_payment_health(const char *url);
void free_checker(void);
