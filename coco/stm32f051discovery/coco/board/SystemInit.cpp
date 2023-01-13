#include "config.hpp"
#include <coco/platform/platform.hpp>


// called from system/startup_stm32f042x6.s to setup clock and flash before static constructors
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void SystemInit() {
	// leave clock in default configuration (8MHz)

	// disabled interrupts trigger an event and wake up the processor from WFE
	// see chapter 5.3.3 in reference manual
	SCB->SCR = SCB->SCR | SCB_SCR_SEVONPEND_Msk;

	// initialize TIM2
	RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_TIM2EN;
	TIM2->PSC = (CLOCK + 1000 / 2) / 1000 - 1; // prescaler for 1ms timer resolution
	TIM2->EGR = TIM_EGR_UG; // update generation so that prescaler takes effect
	TIM2->DIER = TIM_DIER_CC1IE; // interrupt enable for CC1
	TIM2->CR1 = TIM_CR1_CEN; // enable, count up
}
}
