#pragma once

// make sure the board specific SystemInit() configures the clock to the given frequency
constexpr int CLOCK = 8000000;

// flash start address and size
constexpr int FLASH_ADDRESS = 0x8000000;
constexpr int FLASH_SIZE = 0x10000;
