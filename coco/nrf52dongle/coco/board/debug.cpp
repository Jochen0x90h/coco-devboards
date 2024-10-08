#include <coco/debug.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

constexpr auto redPin = gpio::Config::P0_23 | gpio::Config::INVERT;
constexpr auto greenPin = gpio::Config::P0_22 | gpio::Config::INVERT;
constexpr auto bluePin = gpio::Config::P0_24 | gpio::Config::INVERT;

void __attribute__((weak)) init() {
    // Initialize debug LEDs
    gpio::configureOutput(redPin, false);
    gpio::configureOutput(greenPin, false);
    gpio::configureOutput(bluePin, false);
}

void __attribute__((weak)) set(uint32_t bits, uint32_t function) {
    gpio::setOutput(redPin, (bits & 1) != 0, (function & 1) != 0);
    gpio::setOutput(greenPin, (bits & 2) != 0, (function & 2) != 0);
    gpio::setOutput(bluePin, (bits & 4) != 0, (function & 4) != 0);
}

void __attribute__((weak)) sleep(Microseconds<> time) {
    int64_t count = int64_t(113) * time.value / 16;
    for (int64_t i = 0; i < count; ++i) {
        __NOP();
    }
}

void __attribute__((weak)) write(const char *message, int length) {
}

} // namespace debug
} // namespace coco
