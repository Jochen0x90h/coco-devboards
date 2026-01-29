#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void __attribute__((weak)) SystemInit() {
    /*
        Use HSI, set system clock to 64MHz and peripheral clocks to 16MHz
        HSI is 16MHz
        HSE is 8MHz (MCO from ST-Link) when SB17 is on and SB25/SB27 are off

        Reference manual Table 9
        Wait states  Range 1  Range 2
        0WS           24MHz     8MHz
        1WS           48MHz    16MHz
        2WS           64MHz      -
    */

    // enable clock of PWR
    RCC->APBENR1 = RCC->APBENR1 | RCC_APBENR1_PWREN;

    // 2 wait states
    auto latency = FLASH_ACR_LATENCY_2WS;

    // configure flash
    FLASH->ACR = 0x00040600 // reserved, keep at reset value
        | latency // 2 wait states
        | FLASH_ACR_ICEN // instruction cache enable
        | FLASH_ACR_PRFTEN; // prefetch enable

    // wait until latency bitfield returns written value, see reference manual 3.3.4
    while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != latency);

    // configure PLL using HSI: 16MHz / 1 * 8 = 128MHz
    RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSI // source is internal oscillator HSI16
        | ((1 - 1) << RCC_PLLCFGR_PLLM_Pos) // /M divisor
        | (8 << RCC_PLLCFGR_PLLN_Pos) // *N multiplier
        | RCC_PLLCFGR_PLLREN // enable PLLR output
        | ((2 - 1) << RCC_PLLCFGR_PLLR_Pos); // PLLR: 128MHz / 2 = 64MHz (set SYS_CLOCK in config.hpp accordingly)
        //| RCC_PLLCFGR_PLLPEN // enable PLLP output (for ADC)
        //| ((3 - 1) << RCC_PLLCFGR_PLLP_Pos); // PLLP: 128MHz / 3 = 42.7MHz

    // enable internal oscillator and PLL
    RCC->CR = RCC_CR_HSION // enable internal oscillator
        | RCC_CR_PLLON; // enable PLL
/*
    // configure PLL using HSE: 8MHz / 1 * 12 = 96MHz
    RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSI // source is internal oscillator HSI16
        | ((1 - 1) << RCC_PLLCFGR_PLLM_Pos) // /M divisor
        | (12 << RCC_PLLCFGR_PLLN_Pos) // *N multiplier
        | RCC_PLLCFGR_PLLREN; // enable PLLR output
        | ((2 - 1) << RCC_PLLCFGR_PLLR_Pos) // PLLR: 96MHz / 2 = 48MHz (set SYS_CLOCK in config.hpp accordingly)
        //| RCC_PLLCFGR_PLLPEN // enable PLLP output (for ADC)
        //| ((3 - 1) << RCC_PLLCFGR_PLLP_Pos); // PLLP: 96MHz / 3 = 32MHz
        | RCC_PLLCFGR_PLLQEN // enable PLLQ output (for USB)
        | ((2 - 1) << RCC_PLLCFGR_PLLQ_Pos); // PLLQ: 96MHz / 2 = 48MHz

    // enable external clock and PLL
    RCC->CR = RCC_CR_HSEON | RCC_CR_HSEBYP // enable external clock
        | RCC_CR_PLLON; // enable PLL
*/
    // set voltage scaling range 1, power down flash during stop mode (is default)
    PWR->CR1 = PWR_CR1_VOS_0 | PWR_CR1_FPD_STOP;

    // wait until PLL is ready
    while (!(RCC->CR & RCC_CR_PLLRDY)) {}

    // configure clock
    RCC->CFGR = RCC_CFGR_SW_PLLRCLK // use PLL
        | RCC_CFGR_HPRE_DIV1 // AHB_CLOCK = SYSCLK
        | RCC_CFGR_PPRE_DIV4; // APB_CLOCK = AHB_CLOCK / 4

    // select PLLP as set clock source of ADC
    //RCC->CCIPR = RCC->CCIPR | RCC_CCIPR_ADC12SEL_0;

    // select PLLQ as clock source of USB
    //RCC->CCIPR2 = RCC->CCIPR2 | RCC_CCIPR2_USBSEL_1;

    // enable clocks of GPIO and SYSCFG
    RCC->IOPENR = RCC->IOPENR
        | RCC_IOPENR_GPIOAEN
        | RCC_IOPENR_GPIOBEN
        | RCC_IOPENR_GPIOCEN
        | RCC_IOPENR_GPIOFEN;
    RCC->APBENR2 = RCC->APBENR2 | RCC_APBENR2_SYSCFGEN;

    coco::debug::init();
}
}
