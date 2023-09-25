#include "csGenerator.h"

gpio_num_t csGenPins[] = {GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_15, GPIO_NUM_16, GPIO_NUM_10};
uint8_t csGenPinsSize = 5;

void enableCS(uint8_t address){
    ESP_LOGI(CSGEN_TAG, "Generating CS on Address %i", address);
    bool outputState[8];
    uint8To8Decode(address, outputState);
    for (size_t i = 0; i < csGenPinsSize; i++)
    {
        gpio_set_level(csGenPins[i], outputState[i]);
    }
    ESP_LOGI(CSGEN_TAG, "CS Generated");
}