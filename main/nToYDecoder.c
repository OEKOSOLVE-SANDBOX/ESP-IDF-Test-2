#include "nToYDecoder.h"

#include <stdint.h>
#include <stdbool.h>

void uint8To8Decode(uint8_t num, bool returnArray[8]){

    if (num >= 128)
    {
        returnArray[7] = true;
        num -= 128;
    } else{
        returnArray[7] = false;
    }
    
    if (num >= 64)
    {
        returnArray[6] = true;
        num -= 64;
    } else{
        returnArray[6] = false;
    }

    
    if (num >= 32)
    {
        returnArray[5] = true;
        num -= 32;
    } else{
        returnArray[5] = false;
    }

    
    if (num >= 16)
    {
        returnArray[4] = true;
        num -= 16;
    } else{
        returnArray[4] = false;
    }

    
    if (num >= 8)
    {
        returnArray[3] = true;
        num -= 8;
    } else{
        returnArray[3] = false;
    }
    
    
    if (num >= 4)
    {
        returnArray[2] = true;
        num -= 4;
    } else{
        returnArray[2] = false;
    }

    
    if (num >= 2)
    {
        returnArray[1] = true;
        num -= 2;
    } else{
        returnArray[1] = false;
    }

    
    if (num >= 1)
    {
        returnArray[0] = true;
        num -= 1;
    } else{
        returnArray[0] = false;
    }
}