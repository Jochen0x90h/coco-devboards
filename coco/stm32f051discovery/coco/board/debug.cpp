#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

void init() {
	// Initialize debug LEDs
	gpio::configureOutput(gpio::PC(9), gpio::Pull::DISABLED, gpio::Speed::LOW, gpio::Drive::PUSH_PULL); // green LED
	gpio::configureOutput(gpio::PC(8), gpio::Pull::DISABLED, gpio::Speed::LOW, gpio::Drive::PUSH_PULL); // blue LED
}

void setRed(bool value) {
}

void toggleRed() {
}

void setGreen(bool value) {
	gpio::setOutput(gpio::PC(9), value);
}

void toggleGreen() {
	gpio::toggleOutput(gpio::PC(9));
}

void setBlue(bool value) {
	gpio::setOutput(gpio::PC(8), value);
}

void toggleBlue() {
	gpio::toggleOutput(gpio::PC(8));
}

} // namespace debug
} // namespace coco
