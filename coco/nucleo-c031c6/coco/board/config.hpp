#pragma once

#include <coco/Frequency.hpp>


using namespace coco::literals;

// make sure the board specific SystemInit() configures the clocks to the given frequencies

constexpr auto SYS_CLOCK = 48MHz;
constexpr auto AHB_CLOCK = SYS_CLOCK;

constexpr auto APB_CLOCK = AHB_CLOCK / 2; // 24MHz
constexpr auto APB_TIMER_CLOCK = APB_CLOCK * 2; // 48MHz


constexpr auto USART1_CLOCK = APB_CLOCK;
constexpr auto USART2_CLOCK = APB_CLOCK;
constexpr auto I2C1_CLOCK = APB_CLOCK;


// flash start address and size
constexpr int FLASH_ADDRESS = 0x8000000;
constexpr int FLASH_SIZE = 0x8000; // 32K
