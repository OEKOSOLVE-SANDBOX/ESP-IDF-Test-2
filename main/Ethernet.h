#ifndef ETHERNET_H
#define ETHERNET_H

#include <esp_eth.h>
#include <driver/gpio.h>
#include <time.h>
#include <sys/time.h>
#include <esp_system.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_attr.h>
#include <esp_sleep.h>
#include <esp_netif_sntp.h>
#include <lwip/ip_addr.h>
#include <esp_sntp.h>


/* This header contains the necessary configuration for W5500 Ethernet
 *
 */

constexpr char ethernetTestTag[] = "EthernetTest";

constexpr spi_host_device_t ethernetSPINum = SPI3_HOST;
constexpr gpio_num_t ethSPICS = GPIO_NUM_3;
constexpr gpio_num_t ETHintGPIO = GPIO_NUM_9;
constexpr gpio_num_t ETHresetGPIO = GPIO_NUM_46;

constexpr int ethClockSpeed = 1 * 1000 * 1000;
constexpr int ethQueueSize = 20;

extern esp_eth_handle_t ethHandleOS;


esp_err_t ethInit();
esp_err_t networkInterfaceStart();
esp_err_t networkSNTPStart();

#endif