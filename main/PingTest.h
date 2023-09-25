#ifndef ESP_IDF_TEST_2_PINGTEST_H
#define ESP_IDF_TEST_2_PINGTEST_H

#include <ping/ping_sock.h>

void initializePing();

void testOnPingEnd(esp_ping_handle_t handle, void* args);

void testOnPingTimeOut(esp_ping_handle_t handle, void* args);

void testOnPingSuccess(esp_ping_handle_t handle, void* args);

#endif //ESP_IDF_TEST_2_PINGTEST_H
