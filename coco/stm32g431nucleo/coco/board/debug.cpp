#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

constexpr int greenPin = gpio::PA(5);

void __attribute__((weak)) init() {
	// Initialize debug LEDs
	gpio::configureOutput(greenPin, false, gpio::Speed::LOW);
}

void __attribute__((weak)) setRed(bool value) {
}

void __attribute__((weak)) toggleRed() {
}

void __attribute__((weak)) setGreen(bool value) {
	gpio::setOutput(greenPin, value);
}

void __attribute__((weak))  toggleGreen() {
	gpio::toggleOutput(greenPin);
}

void __attribute__((weak)) setBlue(bool value) {
}

void __attribute__((weak)) toggleBlue() {
}

} // namespace debug
} // namespace coco
