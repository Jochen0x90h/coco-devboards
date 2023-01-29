#pragma once

// make sure the board specific SystemInit() configures the clock to the given frequency
constexpr int CLOCK = 64000000;

// flash start address and size
constexpr int FLASH_ADDRESS = 0;
constexpr int FLASH_SIZE = 0x100000;
