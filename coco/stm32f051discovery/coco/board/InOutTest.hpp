#pragma once

#include <coco/platform/InOut_GPIO.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace board {


InOut_GPIO::Config ioConfig[] {
	{gpio::PB(12), gpio::Mode::OUTPUT, gpio::Pull::DISABLED, gpio::Speed::LOW, gpio::Drive::PUSH_PULL, false, false},
	{gpio::PC(9), gpio::Mode::OUTPUT, gpio::Pull::DISABLED, gpio::Speed::LOW, gpio::Drive::PUSH_PULL, false, false}, // green LED
	{gpio::PC(8), gpio::Mode::OUTPUT, gpio::Pull::DISABLED, gpio::Speed::LOW, gpio::Drive::PUSH_PULL, false, false}, // blue LED
	{gpio::PA(0), gpio::Mode::INPUT, gpio::Pull::DISABLED, gpio::Speed::LOW, gpio::Drive::PUSH_PULL, false, false} // user button
};


// test configuraton of InOut
struct InOutTest {
	InOut_GPIO io{ioConfig};
};

}
}
