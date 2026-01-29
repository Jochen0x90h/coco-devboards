#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void SystemInit() {
    /*
        Use HSI, set system clock to 48MHz and peripheral clocks to 24MHz
        HSI is 48MHz
        HSE is 48MHz

        Reference manual Table 6
        Wait states      HCLK
        0WS              24MHz
        1WS              48MHz
    */

    // enable clock of PWR
    RCC->APBENR1 = RCC->APBENR1 | RCC_APBENR1_PWREN;

    // 1 wait state
    auto latency = FLASH_ACR_LATENCY_1WS;

    // configure flash
    FLASH->ACR = 0x00000600 // reserved, keep at reset value
        | latency
        | FLASH_ACR_ICEN // instruction cache enable
        | FLASH_ACR_PRFTEN // prefetch enable
        | FLASH_ACR_DBG_SWEN; // debug enable

    // wait until latency bitfield returns written value, see reference manual 3.3.3
    while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != latency);

    // configure clock
    RCC->CFGR = RCC_CFGR_SW_HSISYS // use HSI
        | RCC_CFGR_HPRE_DIV1 // AHB_CLOCK = SYSCLK
        | RCC_CFGR_PPRE_DIV2; // APB_CLOCK = AHB_CLOCK / 2
    RCC->CR = RCC_CR_HSION // enable HSI48
        | RCC_CR_HSIDIV_DIV1; // HSI48 prescaler

    // enable clocks of GPIO and SYSCFG
    RCC->IOPENR = RCC->IOPENR
        | RCC_IOPENR_GPIOAEN
        | RCC_IOPENR_GPIOBEN
        | RCC_IOPENR_GPIOCEN
        | RCC_IOPENR_GPIODEN
        | RCC_IOPENR_GPIOFEN;
    RCC->APBENR2 = RCC->APBENR2 | RCC_APBENR2_SYSCFGEN;

    coco::debug::init();
}
}
