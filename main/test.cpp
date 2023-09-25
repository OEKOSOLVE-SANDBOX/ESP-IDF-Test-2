#include <esp_log.h>
#include <esp_eth.h>
#include <inttypes.h>
#include <esp_freertos_hooks.h>
#include <esp_netif_sntp.h>

#include "Ethernet.h"
#include "PingTest.h"

constexpr char tag[] = "Testing ETH";

esp_err_t networkInterfaceStart();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
spi_bus_config_t spi1Config = {
        .mosi_io_num = GPIO_NUM_17,
        .miso_io_num = GPIO_NUM_18,
        .sclk_io_num = GPIO_NUM_8,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
        .flags = SPICOMMON_BUSFLAG_GPIO_PINS | SPICOMMON_BUSFLAG_MASTER,
};
#pragma GCC diagnostic pop

spi_host_device_t spi1Host = SPI3_HOST;

// Functions

void sntpTestTask(void* unused) {
    uint32_t sec;
    uint32_t uSec;
    vTaskDelay(500 / portTICK_PERIOD_MS);
    if (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000)) != ESP_OK) {
        ESP_LOGE("SNTP Time Test", "Failed to sync time");
    }
    for(;;) {
        sntp_get_system_time(&sec, &uSec);

        ESP_LOGE("SNTP Time Test", "%"PRIi32" : %"PRIi32, sec, uSec);

        vTaskDelay(15000 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(tag, "Setting up");

    spi_bus_initialize(spi1Host, &spi1Config, SPI_DMA_DISABLED);
    ethInit();
    networkInterfaceStart();
    networkSNTPStart();
    //initializePing();

    xTaskCreate(
            sntpTestTask,
            "SNTP TEST TASK",
            1024 * 10,
            NULL,
            10,
            NULL
            );
}

