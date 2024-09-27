#pragma once

#include <coco/Frequency.hpp>


using namespace coco::literals;

// make sure the board specific SystemInit() configures the clock to the given frequency
/*
constexpr auto CLOCK = 8MHz;
constexpr auto AHB_CLOCK = CLOCK;

constexpr auto APB1_CLOCK = AHB_CLOCK;
constexpr auto APB1_TIMER_CLOCK = AHB_CLOCK;
*/

constexpr auto CLOCK = 40MHz;
constexpr auto AHB_CLOCK = CLOCK;

constexpr auto APB1_CLOCK = AHB_CLOCK / 2;
constexpr auto APB1_TIMER_CLOCK = APB1_CLOCK * 2;

constexpr auto USART1_CLOCK = APB1_CLOCK;
constexpr auto USART2_CLOCK = APB1_CLOCK;


// flash start address and size
constexpr int FLASH_ADDRESS = 0x8000000;
constexpr int FLASH_SIZE = 0x10000;
