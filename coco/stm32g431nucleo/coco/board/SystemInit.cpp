#include "config.hpp"
#include <coco/debug.hpp>
#include <coco/platform/platform.hpp>


// called from startup code to setup clock and flash before static constructors and main()
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void SystemInit() {
	// default clock is 16MHz

	/*
		Reference manual Table 9
		Wait states  Range 1 boost  Range 1 normal  Range 2
		0WS           34MHz          30MHz           12MHz
		1WS           68MHz          60MHz           24MHz
		2WS          102MHz          90MHz           26MHz
		3WS          136MHz         120MHz
		4WS          170MHz         150MHz
	*/

/*
	// set system clock to 80MHz and peripheral clocks to 20MHz

	// set flash latency
	FLASH->ACR = FLASH_ACR_DBG_SWEN | FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_2WS;

	// select HSI16, set PLL multiplier, enable PLL "R" output
	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSI | (10 << RCC_PLLCFGR_PLLN_Pos) | RCC_PLLCFGR_PLLREN;

	// enable HSI16 and PLL
	RCC->CR = RCC_CR_HSION | RCC_CR_PLLON | 0x63;

	// wait until PLL is ready (not neded as hardware switches clock when PLL is ready)
	//while (!(RCC->CR & RCC_CR_PLLRDY)) {}

	// set APB1 and APB2 prescaler, use PLL
	RCC->CFGR = RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV4 | RCC_CFGR_SW_PLL;
*/

	// set system clock to 160MHz and peripheral clocks to 20MHz

	// set flash latency
	FLASH->ACR = FLASH_ACR_DBG_SWEN | FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_4WS;

	// set boost mode
	PWR->CR5 = 0;

	// select HSI16, set PLL multiplier, enable PLL "R" output
	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSI | (20 << RCC_PLLCFGR_PLLN_Pos) | RCC_PLLCFGR_PLLREN;

	// enable HSI16 and PLL
	RCC->CR = RCC_CR_HSION | RCC_CR_PLLON | 0x63;

	// wait until PLL is ready (not neded as hardware switches clock when PLL is ready)
	//while (!(RCC->CR & RCC_CR_PLLRDY)) {}

	// set APB1 and APB2 prescaler, use PLL
	RCC->CFGR = RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV8 | RCC_CFGR_PPRE2_DIV8 | RCC_CFGR_SW_PLL;

	coco::debug::init();
}
}
