#include <coco/platform/platform.hpp>


// called from system/startup_stm32f042x6.s to setup clock and flash before static constructors
// pass -Wl,--undefined=SystemInit to gcc in addition to -Wl,--gc-sections to prevent the function from being garbage collected
extern "C" {
void SystemInit() {
	// leave clock in default configuration (8MHz)
}
}
