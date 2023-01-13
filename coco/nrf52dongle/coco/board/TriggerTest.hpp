#pragma once

#include <coco/platform/Trigger_GPIOTE_RTC0.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace board {

Trigger_GPIOTE_RTC0::Config triggerConfig[] {
	{gpio::P0(18), gpio::Pull::UP, true} // user button
};

// test configuraton for Trigger
struct TriggerTest {
	Trigger_GPIOTE_RTC0 trigger{triggerConfig};
};

}
}
