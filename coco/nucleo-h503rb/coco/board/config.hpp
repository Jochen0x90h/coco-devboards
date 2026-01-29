#pragma once

#include <coco/Frequency.hpp>


using namespace coco::literals;

// make sure the board specific SystemInit() configures the clocks to the given frequencies

//constexpr auto SYS_CLOCK = 248MHz;
constexpr auto SYS_CLOCK = 240MHz;
constexpr auto AHB_CLOCK = SYS_CLOCK;

constexpr auto APB1_CLOCK = AHB_CLOCK / 8; // 31MHz
constexpr auto APB1_TIMER_CLOCK = APB1_CLOCK * 2; // 62MHz

constexpr auto APB2_CLOCK = AHB_CLOCK / 8; // 31MHz
constexpr auto APB2_TIMER_CLOCK = APB2_CLOCK * 2; // 62MHz

constexpr auto APB3_CLOCK = AHB_CLOCK / 8; // 31MHz

constexpr auto USART1_CLOCK = APB2_CLOCK;
constexpr auto USART3_CLOCK = APB1_CLOCK;
constexpr auto UART4_CLOCK = APB1_CLOCK;
constexpr auto UART5_CLOCK = APB1_CLOCK;

constexpr auto LPUART1_CLOCK = APB3_CLOCK;

constexpr auto I2C1_CLOCK = APB1_CLOCK;
constexpr auto I2C2_CLOCK = APB1_CLOCK;
constexpr auto I2C3_CLOCK = APB3_CLOCK;


constexpr auto PLL1Q_CLOCK = 31MHz;

constexpr auto SPI1_CLOCK = PLL1Q_CLOCK;
constexpr auto SPI2_CLOCK = PLL1Q_CLOCK;
constexpr auto SPI3_CLOCK = PLL1Q_CLOCK;

constexpr auto FDCAN_CLOCK = PLL1Q_CLOCK;


// flash start address and size
constexpr int FLASH_ADDRESS = 0x8000000;
constexpr int FLASH_SIZE = 0x20000; // 128k
