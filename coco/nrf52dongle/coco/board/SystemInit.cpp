#include <coco/platform/platform.hpp>


// called by system/gcc_startup_nrf52840.S
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void SystemInit() {
	// configure system clock
	NRF_CLOCK->HFXODEBOUNCE = N(CLOCK_HFXODEBOUNCE_HFXODEBOUNCE, Db1024us);
	NRF_CLOCK->LFCLKSRC = N(CLOCK_LFCLKSRC_SRC, Synth); // no external 32768Hz oscillator

	// start HF clock and wait
	NRF_CLOCK->TASKS_HFCLKSTART = TRIGGER;
	while (!NRF_CLOCK->EVENTS_HFCLKSTARTED);
	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;

	// start LF clock and wait
	NRF_CLOCK->TASKS_LFCLKSTART = TRIGGER;
	while (!NRF_CLOCK->EVENTS_LFCLKSTARTED);
	NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;

	// enable FPU, depends on compiler flags (see nRF5_SDK_*/modules/nrfx/mdk/system_nrf52.c)
#if (__FPU_USED == 1)
	SCB->CPACR = SCB->CPACR | (3UL << 20) | (3UL << 22);
	__DSB();
	__ISB();
#else
	#warning "FPU is not used"
#endif
}
}
