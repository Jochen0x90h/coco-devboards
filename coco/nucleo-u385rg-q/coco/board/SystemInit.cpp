#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void __attribute__((weak)) SystemInit() {
    /*
        Use MSIS as clock source, set system clock to 96MHz and peripheral clocks to 24MHz
        HSI is 16MHz
        HSE is not connected

        Reference manual Table 37
        Wait states  range 1        range 2
        0WS           32MHz          16MHz
        1WS           64MHz          32MHz
        2WS           96MHz          48MHz
    */

    // enable clock of PWR
    RCC->AHB1ENR2 = RCC->AHB1ENR2 | RCC_AHB1ENR2_PWREN;

    // use MSIS as EPOD (embedded power distribution) booster clock source
    RCC->CFGR4 = RCC_CFGR4_BOOSTSEL_0;

    // configure flash
    FLASH->ACR = FLASH_ACR_LATENCY_2WS // 2 wait states
        | FLASH_ACR_PRFTEN; // prefetch enable

    // set boost mode and range 1 (high performance)
    PWR->VOSR = PWR_VOSR_BOOSTEN | PWR_VOSR_R1EN;

    // set AHB, APB1, APB2 and APB3 prescaler
    RCC->CFGR2 = RCC_CFGR2_HPRE1_DIV1
        | RCC_CFGR2_PPRE1_DIV4
        | RCC_CFGR2_PPRE2_DIV4;
    RCC->CFGR3 = RCC_CFGR3_PPRE3_DIV4;

    // wait until booster and range 1 are ready
    while ((PWR->VOSR & (PWR_VOSR_R1RDY | PWR_VOSR_BOOSTRDY)) != (PWR_VOSR_R1RDY | PWR_VOSR_BOOSTRDY)) {}

    // configure MSIS and MSIK, select ICSCR1 register
    RCC->ICSCR1 = RCC_ICSCR1_MSIS_96MHZ | RCC_ICSCR1_MSIK_96MHZ | RCC_ICSCR1_MSIRGSEL;

    // configure instruction cache
    ICACHE->CR = ICACHE_CR_EN | ICACHE_CR_WAYSEL;

    // enable FPU, depends on compiler flags
#if (__FPU_USED == 1)
    SCB->CPACR = SCB->CPACR | (3UL << 20) | (3UL << 22);
    __DSB();
    __ISB();
#else
    #warning "FPU is not used"
#endif


    // enable clocks of GPIO and SYSCFG
    RCC->AHB2ENR1 = RCC->AHB2ENR1
        | RCC_AHB2ENR1_GPIOAEN
        | RCC_AHB2ENR1_GPIOBEN
        | RCC_AHB2ENR1_GPIOCEN
        | RCC_AHB2ENR1_GPIODEN
        | RCC_AHB2ENR1_GPIOHEN;
    RCC->APB3ENR = RCC->APB3ENR | RCC_APB3ENR_SYSCFGEN;

    coco::debug::init();
}
}
