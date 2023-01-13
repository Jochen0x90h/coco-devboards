#pragma once

#include <coco/platform/InOut_GPIO.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace board {

InOut_GPIO::Config ioConfig[] {
	{gpio::P0(23), gpio::Mode::OUTPUT, gpio::Pull::DISABLED, gpio::Drive::S0D1, true, false}, // red LED
	{gpio::P0(22), gpio::Mode::OUTPUT, gpio::Pull::DISABLED, gpio::Drive::S0D1, true, false}, // green LED
	{gpio::P0(24), gpio::Mode::OUTPUT, gpio::Pull::DISABLED, gpio::Drive::S0D1, true, false}, // blue LED
	{gpio::P0(18), gpio::Mode::INPUT, gpio::Pull::UP, gpio::Drive::S0D1, true, false} // user button
};

// test configuraton for InOut
struct InOutTest {
	InOut_GPIO io{ioConfig};
};

}
}
