#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

constexpr int redPin = gpio::P0(23);
constexpr int greenPin = gpio::P0(22);
constexpr int bluePin = gpio::P0(24);

void __attribute__((weak)) init() {
	// Initialize debug LEDs
	gpio::configureOutput(redPin, true, gpio::Drive::S0S1);
	gpio::configureOutput(greenPin, true, gpio::Drive::S0S1);
	gpio::configureOutput(bluePin, true, gpio::Drive::S0S1);
}

void __attribute__((weak)) setRed(bool value) {
	gpio::setOutput(redPin, !value);
}

void __attribute__((weak)) toggleRed() {
	gpio::toggleOutput(redPin);
}

void __attribute__((weak)) setGreen(bool value) {
	gpio::setOutput(greenPin, !value);
}

void __attribute__((weak)) toggleGreen() {
	gpio::toggleOutput(greenPin);
}

void __attribute__((weak)) setBlue(bool value) {
	gpio::setOutput(bluePin, !value);
}

void __attribute__((weak)) toggleBlue() {
	gpio::toggleOutput(bluePin);
}

} // namespace debug
} // namespace coco
