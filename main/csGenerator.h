#ifndef CSGENERATOR
#define CSGENERATOR


#ifdef __cplusplus
extern "C" { 
#endif

/** @file */

/**
 * @brief Tag for ESP_LOG
 */
#define CSGEN_TAG "CS Generator"

#include "driver/gpio.h"
#include "nToYDecoder.h"
#include "esp_log.h"

/**
 * @brief Array of Pins to be used by the CS Generator
 */
extern gpio_num_t csGenPins[];

/**
 * @brief Size of the Array csGenPins
 */
extern uint8_t csGenPinsSize;

/**
 * @brief Method to enable a given Chip Select
 * @param address
 * @author Dominik Martin Glogowski
 */
void enableCS(uint8_t address);

#ifdef __cplusplus
}
#endif

#endif