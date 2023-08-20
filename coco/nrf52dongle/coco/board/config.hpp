#pragma once

#include <coco/Frequency.hpp>


using namespace coco::literals;

// make sure the board specific SystemInit() configures the clock to the given frequency
constexpr auto CLOCK = 64MHz;

// flash start address and size
constexpr int FLASH_ADDRESS = 0;
constexpr int FLASH_SIZE = 0xe0000; // is 0x100000 but leave space for boot loader
