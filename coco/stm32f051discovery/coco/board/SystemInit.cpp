#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void SystemInit() {
	// default clock is 8MHz

	// set system clock to 40MHz and peripheral clock to 20MHz

	// set APB1 prescaler, set PLL multiplier, use PLL
	RCC->CFGR = RCC_CFGR_PPRE_DIV2 | RCC_CFGR_PLLMUL10 | RCC_CFGR_SW_PLL;

	// enable PLL
	RCC->CR = RCC->CR | RCC_CR_PLLON;

	coco::debug::init();
}
}
