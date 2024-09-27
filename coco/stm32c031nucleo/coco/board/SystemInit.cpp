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

    // set flash latency
    uint32_t latency = 1 << FLASH_ACR_LATENCY_Pos; // 1 wait state
    FLASH->ACR = FLASH_ACR_DBG_SWEN // debug enable
        | 0x0400 // reserved, keep at reset value
        | FLASH_ACR_ICEN // instruction cache enable
        | latency; // latency 2 cycles

    // wait until latency bitfield returns written value, see reference manual 3.3.3
    while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != latency);

    // configure clock
    RCC->CFGR = RCC_CFGR_HPRE_DIV1 // AHB prescaler
        | RCC_CFGR_PPRE_DIV2; // APB prescaler
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
