#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void __attribute__((weak)) SystemInit() {
    /*
        Use CSI RC as clock source, set system clock to 248MHz and peripheral clocks to 31MHz
        CSI is 4MHz
        HSI is 64MHz
        HSE is 24MHz crystal

        Reference manual Table 20
        Wait states   delay   scale 3        scale 2        scale 1        scale 0
        0WS             0      20MHz          30MHz          34MHz          42MHz
        1WS             0      40MHz          60MHz          68MHz          84MHz
        2WS             1      60MHz          90MHz         102MHz         126MHz
        3WS             1      80MHz         120MHz         136MHz         168MHz
        4WS             2     100MHz         150MHz         170MHz         210MHz
        5WS             2                                   200MHz         250MHz
    */


    // set flash latency
    FLASH->ACR = FLASH_ACR_LATENCY_5WS // 5 wait states
        | FLASH_ACR_WRHIGHFREQ_1 // programming delay 2
        | FLASH_ACR_PRFTEN; // prefetch enable

    // set voltage scale 0
    PWR->VOSCR = PWR_VOSCR_VOS_1 | PWR_VOSCR_VOS_0;

    // configure PLL1 inputs, PLL1M and outputs
    RCC->PLL1CFGR = (2 << RCC_PLL1CFGR_PLL1RGE_Pos) // input clock 4-8MHz
        | RCC_PLL1CFGR_PLL1SRC_1 // input is CSI
        | (1 << RCC_PLL1CFGR_PLL1M_Pos) // /M
        | RCC_PLL1CFGR_PLL1PEN // enable PLL1P output
        | RCC_PLL1CFGR_PLL1QEN; // enable PLL1Q output

    // configure PLL1: 4MHz / 1 * 124 = 496MHz
    RCC->PLL1DIVR = ((124 - 1) << RCC_PLL1DIVR_PLL1N_Pos) // *N
        | ((2 - 1) << RCC_PLL1DIVR_PLL1P_Pos) // PLLP: 496MHz / 2 = 248MHz
        | ((2 - 1) << RCC_PLL1DIVR_PLL1Q_Pos); // PLLQ: 496MHz / 16 = 31MHz (default source for SPI1, SPI2, SPI3, FDCAN1, FDCAN2)
        //| ((2 - 1) << RCC_PLL1DIVR_PLL1R_Pos); // PLLR

    // wait until voltage scaling is ready
    while ((PWR->VOSSR & PWR_VOSSR_VOSRDY) == 0);

    // enable clock (keep HSI enabled)
    RCC->CR = RCC_CR_HSION // keep HSI enabled
        | RCC_CR_CSION; // use CSI

    // set AHB, APB1, APB2 and APB3 prescaler
    RCC->CFGR2 = RCC_CFGR2_HPRE1_DIV1
        | RCC_CFGR2_PPRE1_DIV8
        | RCC_CFGR2_PPRE2_DIV8
        | RCC_CFGR2_PPRE3_DIV8;

    // wait until clock is ready
    while ((RCC->CR & RCC_CR_CSIRDY) == 0);

    // enable PLL1 and wait until ready
    RCC->CR = RCC_CR_HSION // keep HSI enabled
        | RCC_CR_CSION // keep CSI enabled
        | RCC_CR_PLL1ON;
    while ((RCC->CR & RCC_CR_PLL1RDY) == 0);

    // use PLL1
    RCC->CFGR1 = RCC_CFGR1_SW_1 | RCC_CFGR1_SW_0;

    // configure instruction cache
    ICACHE->CR = ICACHE_CR_EN | ICACHE_CR_WAYSEL;

    // switch off HSI
    RCC->CR =  RCC_CR_PLL1ON // keep PLL enabled
        | RCC_CR_CSION; // keep CSI enabled

    // enable FPU, depends on compiler flags
#if (__FPU_USED == 1)
    SCB->CPACR = SCB->CPACR | (3UL << 20) | (3UL << 22);
    __DSB();
    __ISB();
#else
    #warning "FPU is not used"
#endif


    // enable clocks of GPIO and SYSCFG
    RCC->AHB2ENR = RCC->AHB2ENR
        | RCC_AHB2ENR_GPIOAEN
        | RCC_AHB2ENR_GPIOBEN
        | RCC_AHB2ENR_GPIOCEN
        | RCC_AHB2ENR_GPIODEN
        | RCC_AHB2ENR_GPIOHEN;
    //RCC->APB3ENR = RCC->APB3ENR | RCC_APB3ENR_SYSCFGEN;

    coco::debug::init();
}
}
