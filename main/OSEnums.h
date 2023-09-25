#ifndef OSENUMS_H
#define OSENUMS_H

#include <stdint.h>
#include <stdbool.h>

/** @file */

/**
 * @brief Constant for 1 MHz Definition
 */
constexpr int ONE_MHZ = 1000 * 1000;

/**
 * @brief CS Numbers to pass to Functions in csGenerator.h .
 * Values and naming follows from PCB OS-ESP-CTRL v0.1
 * @note There are another 16 possible values however, all of them are currently unused and therefore not represented. The only unused member that exists is UNUSED at CSGen Pin 15
 */
enum class ChipSelectGeneratorPorts : uint8_t{
CS1    =  7U,  ///< CS Pin associated to the Current Measurement of wM1 at X208
CS2    = 29U,  ///< CS Pin associated to the Current Measurement of wM2 at X201
CS3    =  6U,  ///< CS Pin associated to the Current Measurement of wM3 at X207
CS4    =  3U,  ///< CS Pin associated to the Current Measurement of wm5 at X101
CS5    =  2U,  ///< CS Pin associated to the Current Measurement of wm4 at X101
CS6    =  4U,  ///< CS Pin associated to the Current Measurement of wm6 at X101
CS7    =  5U,  ///< CS Pin associated to the Current Measurement of wM7 at X102
CS8    = 30U,  ///< CS Pin associated to the Current Measurement of wM8 at X205
CS9    =  8U,  ///< CS Pin associated to the Current Measurement of wM9 at X209
CS10   =  9U,  ///< CS Pin associated to the Current Measurement of wM10 at X2010
CS11   = 31U,  ///< CS Pin associated to the Current Measurement of wM11 at X204
CS12   = 27U,  ///< CS Pin associated to the Current Measurement of wMA2/wMB2 at X302
CS13   = 28U,  ///< CS Pin associated to the Current Measurement of wMA1/wMB1 at X301
CS14   =  1U,  ///< CS Pin associated to MCP23S17 at Position U7_3
CS15   =  0U,  ///< CS Pin associated to MCP23S17 at Position U7_2
CS16   = 10U,  ///< CS Pin associated to MCP23S17 at Position U7_1
CS_EX1 = 16U,  ///< Expansion Board CS Pin 1
CS_EX2 = 17U,  ///< Expansion Board CS Pin 2
CS_EX3 = 18U,  ///< Expansion Board CS Pin 3
CS_EX4 = 19U,  ///< Expansion Board CS Pin 4
CS_TC1 = 26U,  ///< CS Pin associated to thermocouple0
CS_TC2 = 25U,  ///< CS Pin associated to thermocouple1
CS_TC3 = 24U,  ///< CS Pin associated to thermocouple2
UNUSED = 15U   ///< Unused CS Pin currently used to not select any associated device
};

#endif
