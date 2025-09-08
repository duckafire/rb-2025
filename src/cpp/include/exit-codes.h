#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum {
	EXIT_OK,
	EXIT_AUX_HASHEY_NOT_SPECIFIED,
	EXIT_AUX_URL_NOT_SPECIFIED,
	EXIT_DB_CONNECT_FAIL,
	EXIT_IMPOSSIBLE_START_CURL,
	EXIT_SOME_CURL_ERROR,
	EXIT_NO_PORT_FOR_CPP_SOLUTION,
};

#ifdef __cplusplus
}
#endif
