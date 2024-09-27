#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void __attribute__((weak)) SystemInit() {
    /*
        Use HSI, set system clock to 40MHz and peripheral clocks to 20MHz
        HSI is 8MHz

        Reference manual 3.5.1
        Wait states      HCLK
        0WS              24MHz
        1WS              48MHz
        2WS              72MHz
    */

    // set flash latency
    FLASH->ACR = (1 << FLASH_ACR_LATENCY_Pos) // 1 wait state
        | FLASH_ACR_PRFTBE; // prefetch buffer enable

    // set PLL multiplier, use PLL, set APB1 and APB2 prescaler
    RCC->CFGR = RCC_CFGR_PLLMUL10 // x10
        | RCC_CFGR_SW_PLL // use PLL
        | RCC_CFGR_PPRE1_DIV2 // APB1_CLOCK = AHB_CLOCK / 2
        | RCC_CFGR_PPRE2_DIV2; // APB2_CLOCK = AHB_CLOCK / 2

    // enable PLL
    RCC->CR = RCC->CR | RCC_CR_PLLON;

    // set clock source of ADC to PLL clock / 1
    RCC->CFGR2 = RCC_CFGR2_ADCPRE12_4;

    // enable FPU, depends on compiler flags (see nRF5_SDK_*/modules/nrfx/mdk/system_nrf52.c)
#if (__FPU_USED == 1)
    SCB->CPACR = SCB->CPACR | (3UL << 20) | (3UL << 22);
    __DSB();
    __ISB();
#else
    #warning "FPU is not used"
#endif

    // enable clocks of GPIO and SYSCFG
    RCC->AHBENR = RCC->AHBENR
        | RCC_AHBENR_GPIOAEN
        | RCC_AHBENR_GPIOBEN
        | RCC_AHBENR_GPIOCEN
        | RCC_AHBENR_GPIODEN
        | RCC_AHBENR_GPIOFEN;
    RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_SYSCFGEN;

    coco::debug::init();
}
}
