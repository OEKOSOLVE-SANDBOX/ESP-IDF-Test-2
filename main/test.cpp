#include <esp_log.h>
#include <esp_eth.h>
#include <inttypes.h>
#include <esp_freertos_hooks.h>
#include <esp_netif_sntp.h>
#include <time.h>
#include <sys/time.h>
#include <esp_system.h>
#include <esp_event.h>

#include "Ethernet.h"
#include "SNTP.h"

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

extern "C" void app_main(void) {
    ESP_LOGI(tag, "Setting up");

    spi_bus_initialize(spi1Host, &spi1Config, SPI_DMA_DISABLED);
    ethInit();
    networkInterfaceStart();

}

