#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

void init() {
	// Initialize debug LEDs
	gpio::setOutput(gpio::P0(23), true);
	gpio::setOutput(gpio::P0(22), true);
	gpio::setOutput(gpio::P0(24), true);
	gpio::configureOutput(gpio::P0(23), gpio::Pull::DISABLED, gpio::Drive::S0D1); // red LED
	gpio::configureOutput(gpio::P0(22), gpio::Pull::DISABLED, gpio::Drive::S0D1); // green LED
	gpio::configureOutput(gpio::P0(24), gpio::Pull::DISABLED, gpio::Drive::S0D1); // blue LED
}

void setRed(bool value) {
	gpio::setOutput(gpio::P0(23), !value);
}

void toggleRed() {
	gpio::toggleOutput(gpio::P0(23));
}

void setGreen(bool value) {
	gpio::setOutput(gpio::P0(22), !value);
}

void toggleGreen() {
	gpio::toggleOutput(gpio::P0(22));
}

void setBlue(bool value) {
	gpio::setOutput(gpio::P0(24), !value);
}

void toggleBlue() {
	gpio::toggleOutput(gpio::P0(24));
}

} // namespace debug
} // namespace coco
