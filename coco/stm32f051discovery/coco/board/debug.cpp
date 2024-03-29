#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

constexpr int greenPin = gpio::PC(9);
constexpr int bluePin = gpio::PC(8);

void __attribute__((weak)) init() {
	// Initialize debug LEDs
	gpio::configureOutput(greenPin, false, gpio::Speed::LOW);
	gpio::configureOutput(bluePin, false, gpio::Speed::LOW);
}

void __attribute__((weak)) setRed(bool value) {
}

void __attribute__((weak)) toggleRed() {
}

void __attribute__((weak)) setGreen(bool value) {
	gpio::setOutput(greenPin, value);
}

void __attribute__((weak)) toggleGreen() {
	gpio::toggleOutput(greenPin);
}

void __attribute__((weak)) setBlue(bool value) {
	gpio::setOutput(bluePin, value);
}

void __attribute__((weak)) toggleBlue() {
	gpio::toggleOutput(bluePin);
}

} // namespace debug
} // namespace coco
