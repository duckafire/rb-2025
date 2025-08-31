#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define PP_DEF_URL "https://payment-processor-default:8080"
#define PP_FAL_URL "https://payment-processor-fallback:8080"

#define PP_ENDPOINT_PAY    "/payments"
#define PP_ENDPOINT_HEALTH "/payments/service-health"

#ifdef __cplusplus
}
#endif
