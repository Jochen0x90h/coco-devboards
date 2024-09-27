#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void __attribute__((weak)) SystemInit() {
    /*
        Use HSI, set system clock to 80MHz and peripheral clocks to 20MHz
        HSI is 16MHz
        HSE is 24MHz

        Reference manual Table 9
        Wait states  2.7-3.6V  2.4-2.7V  2.1-2.4V  1.8-2.1V prefetch off
        0WS             30MHz     24MHz     22MHz     20MHz
        1WS             60MHz     48MHz     44MHz     40MHz
        2WS             90MHz     72MHz     66MHz     60MHz
        3WS            120MHz     96MHz     88MHz     80MHz
        4WS            150MHz    120MHz    110MHz    100MHz
        5WS            168MHz    144MHz    132MHz    120MHz
        6WS                      168MHz    154MHz    140MHz
        7WS                                168MHz    160MHz
    */

    // set flash latency
    FLASH->ACR = FLASH_ACR_LATENCY_2WS // 2 wait states
        | FLASH_ACR_PRFTEN // prefetch enable
        | FLASH_ACR_ICEN // instruction cache enable
        | FLASH_ACR_DCEN; // data cache enable

    // configure PLL: 16MHz / 8 * 160 = 320MHz / 4 = 80MHz
    RCC->PLLCFGR = 0x20000000 // reserved, must be kept at reset value
        | RCC_PLLCFGR_PLLSRC_HSI // source is internal oscillator HSI16
        | (8 << RCC_PLLCFGR_PLLM_Pos) // PLL M divisor
        | (160 << RCC_PLLCFGR_PLLN_Pos) // PLL N multiplier
        | RCC_PLLCFGR_PLLP_0 // PLL P divisor = 4
        | (4 << RCC_PLLCFGR_PLLQ_Pos); // PLL Q divisor

    // enable internal oscillator and PLL
    RCC->CR = RCC_CR_HSITRIM_4 // keep HSITRIM at reset value
        | RCC_CR_HSION // enable internal oscillator
        | RCC_CR_PLLON; // enable PLL

    // wait until PLL is ready
    while (!(RCC->CR & RCC_CR_PLLRDY)) {}

    // use PLL, set AHB, APB1 and APB2 prescaler
    RCC->CFGR = RCC_CFGR_SW_PLL // use PLL
        | RCC_CFGR_HPRE_DIV1 // AHB_CLOCK = SYS_CLOCK
        | RCC_CFGR_PPRE1_DIV4 // APB1_CLOCK = AHB_CLOCK / 4
        | RCC_CFGR_PPRE2_DIV4; // APB2_CLOCK = AHB_CLOCK / 4

    // enable FPU, depends on compiler flags (see nRF5_SDK_*/modules/nrfx/mdk/system_nrf52.c)
#if (__FPU_USED == 1)
    SCB->CPACR = SCB->CPACR | (3UL << 20) | (3UL << 22);
    __DSB();
    __ISB();
#else
    #warning "FPU is not used"
#endif

    // enable clocks of GPIO and SYSCFG
    RCC->AHB1ENR = RCC->AHB1ENR
        | RCC_AHB1ENR_GPIOAEN
        | RCC_AHB1ENR_GPIOBEN
        | RCC_AHB1ENR_GPIOCEN
        | RCC_AHB1ENR_GPIODEN
        | RCC_AHB1ENR_GPIOEEN
        | RCC_AHB1ENR_GPIOHEN;
    RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_SYSCFGEN;

    coco::debug::init();
}
}
