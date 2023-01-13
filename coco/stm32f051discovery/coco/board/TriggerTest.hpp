#pragma once

#include <coco/platform/Trigger_EXTI_TIM2.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace board {

Trigger_EXTI_TIM2::Config triggerConfig[] {
	{gpio::PA(0), gpio::Pull::DISABLED, false} // user button
};

// test configuraton for Trigger
struct TriggerTest {
	Trigger_EXTI_TIM2 trigger{triggerConfig};
};

}
}
