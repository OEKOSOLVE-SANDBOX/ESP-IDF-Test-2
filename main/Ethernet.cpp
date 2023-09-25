#include "Ethernet.h"

#include <esp_netif.h>
#include <esp_log.h>
#include <esp_event.h>
#include <esp_netif_sntp.h>

/// Global Variables:
//Supressing warning applying to this struct
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
spi_device_interface_config_t ethSPIDeviceConfigOS = {
        .command_bits = 16,
        .address_bits = 8,
        .mode = 0,
        .clock_speed_hz = ethClockSpeed,
        .spics_io_num = ethSPICS,
        .queue_size = ethQueueSize,
};
#pragma GCC diagnostic pop

spi_device_handle_t ethSPIHandleOS;

eth_mac_config_t macConfigOS = ETH_MAC_DEFAULT_CONFIG();
eth_phy_config_t phyConfigOS = ETH_PHY_DEFAULT_CONFIG();
esp_eth_mac_t* macSPIOS;
esp_eth_phy_t* phySPIPOS;

esp_eth_handle_t ethHandleOS = NULL;
esp_eth_config_t ethConfigSPIOS;

// SNTP
// ESP_NETIF_SNTP_DEFAULT_CONFIG_MULTIPLE does not compile :C
esp_sntp_config_t config = {
        .smooth_sync = false,
        .server_from_dhcp = false,
        .wait_for_sync = true,
        .start = false,
        .sync_cb = NULL,
        .renew_servers_after_new_IP = false,
        .ip_event_to_renew = IP_EVENT_STA_GOT_IP,
        .index_of_first_server = 0,
        .num_of_servers = 0,
        .servers = {},

};

/// Functions

esp_err_t ethInit() {
    esp_err_t error = ESP_OK;

    phyConfigOS.reset_gpio_num = ETHresetGPIO;
    gpio_install_isr_service(0);

    ethSPIHandleOS = NULL;
    macSPIOS = NULL;
    phySPIPOS = NULL;

    eth_w5500_config_t  w5500Config = ETH_W5500_DEFAULT_CONFIG(ethernetSPINum, &ethSPIDeviceConfigOS);
    w5500Config.int_gpio_num = ETHintGPIO;

    macSPIOS = esp_eth_mac_new_w5500(&w5500Config, &macConfigOS);
    phySPIPOS = esp_eth_phy_new_w5500(&phyConfigOS);

    ethConfigSPIOS = ETH_DEFAULT_CONFIG(macSPIOS, phySPIPOS);

    error = esp_eth_driver_install(&ethConfigSPIOS, &ethHandleOS);
    if (error != ESP_OK) {
        ESP_LOGE(ethernetTestTag, "An error occured during installing the driver : 0x%X : %s", error, esp_err_to_name(error));
        return error;
    }

    error = esp_eth_ioctl(ethHandleOS, ETH_CMD_S_MAC_ADDR, ethConfigSPIOS.mac);
    if (error != ESP_OK) {
        ESP_LOGE(ethernetTestTag, "An error occured while configuring the MAC Address : 0x%X : %s", error, esp_err_to_name(error));
        return error;
    }



    return error;
}


esp_err_t networkInterfaceStart() {
    esp_err_t error;

    error = esp_netif_init();

    if (error != ESP_OK) {
        ESP_LOGE(ethernetTestTag, "An error occured during the initialisation of the esp-netif : 0%X , %s", error, esp_err_to_name(error));
        return error;
    }
    
    error = esp_event_loop_create_default();

    if (error != ESP_OK) {
        ESP_LOGE(ethernetTestTag, "An error occured during the initialisation of the event loop : 0x%X , %s", error, esp_err_to_name(error));
        return error;
    }
    

    esp_netif_config_t netIfCfg = ESP_NETIF_DEFAULT_ETH();
    esp_netif_t* eth_netif = esp_netif_new(&netIfCfg);

    error = esp_netif_attach(eth_netif, esp_eth_new_netif_glue(ethHandleOS));

    if (error != ESP_OK) {
        ESP_LOGE(ethernetTestTag, "An error occured during the initialisation of the event loop : 0x%X , %s", error, esp_err_to_name(error));
    }
    return error;
}

esp_err_t networkSNTPStart() {
    esp_err_t error = ESP_OK;
    error = esp_netif_sntp_init(&config);

    if (error != ESP_OK) {
        ESP_LOGE(ethernetTestTag, "An error occured during the initialisation of the SNTP : 0x%X , %s", error, esp_err_to_name(error));
        return error;
    }

    error = esp_netif_sntp_start();

    if (error != ESP_OK) {
        ESP_LOGE(ethernetTestTag, "An error occured during the start of the SNTP : 0x%X , %s", error, esp_err_to_name(error));
    }

    return error;
}
