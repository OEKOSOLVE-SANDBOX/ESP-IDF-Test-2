#ifndef NTOYDECODER
#define NTOYDECODER

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file */

/**
 * @brief Simple Function to turn any uint8_t value to an array of 8 booleans.
 * @details The Function simply takes the number and repeatedly checks, starting from 128, the whether the corresponding bit should be set or not.
 *          Example: 129 -> Larger than the 128 Bit therefore the bit is set and 128 subtracted, all following bits except the 1 Bit which is set too.
 * @param num uint8_t value to convert
 * @param returnArray Array of size 8 containing the converted Value as booleans, initial Values when passing to the Function do not matter.
 * @author Dominik Martin Glogowski
 */
void uint8To8Decode(uint8_t num, bool returnArray[8]);

#ifdef __cplusplus
}
#endif

#endif

