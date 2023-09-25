#include "PingTest.h"

#include <esp_log.h>

constexpr char tag[] = "PingTest";

esp_ping_config_t pingConfig = ESP_PING_DEFAULT_CONFIG();
esp_ping_callbacks_t callbacks;
esp_ping_handle_t pingHandle;
ip_addr_t targetAddress = {
        .u_addr = {
                .ip4 = {
                        .addr = 0x08080808,
                },
        },
        .type = IPADDR_TYPE_V4,
};

void initializePing() {
    pingConfig.target_addr = targetAddress;
    pingConfig.count = 10;

    callbacks.cb_args = NULL;
    callbacks.on_ping_end = testOnPingEnd;
    callbacks.on_ping_success = testOnPingSuccess;
    callbacks.on_ping_timeout = testOnPingTimeOut;

    esp_ping_new_session(&pingConfig, &callbacks, &pingHandle);
}

void testOnPingEnd(esp_ping_handle_t handle, void* args) {
    ESP_LOGI(tag, "End");
}

void testOnPingTimeOut(esp_ping_handle_t handle, void* args) {
    ESP_LOGI(tag, "Timeout");
}

void testOnPingSuccess(esp_ping_handle_t handle, void* args) {
    ESP_LOGI(tag, "Success");
}