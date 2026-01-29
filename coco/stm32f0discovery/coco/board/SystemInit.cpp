#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void SystemInit() {
    /*
        Use HSI, set system clock to 40MHz and peripheral clocks to 20MHz
        HSI is 8MHz

        Reference manual 3.5.1
        Wait states      HCLK
        0WS              24MHz
        1WS              48MHz
    */

    // set flash latency
    FLASH->ACR =
        FLASH_ACR_PRFTBE // prefetch buffer enable
        | (1 << FLASH_ACR_LATENCY_Pos); // 1 wait state

    // set PLL multiplier, use PLL, set AHB and APB prescaler
    RCC->CFGR = RCC_CFGR_PLLMUL10 // PLL factor 10, 8MHz / 2 * 10 = 40MHz
        | RCC_CFGR_SW_PLL // use PLL
        | RCC_CFGR_HPRE_DIV1 // AHB prescaler
        | RCC_CFGR_PPRE_DIV2; // APB prescaler

    // enable internal oscillator and PLL
    RCC->CR = RCC_CR_HSITRIM_4 // keep HSITRIM at reset value
        | RCC_CR_HSION // enable HSI
        | RCC_CR_PLLON; // enable PLL

    // enable clocks of GPIO and SYSCFG
    RCC->AHBENR = RCC->AHBENR
        | RCC_AHBENR_GPIOAEN
        | RCC_AHBENR_GPIOBEN;
    RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_SYSCFGCOMPEN;

    coco::debug::init();
}
}
