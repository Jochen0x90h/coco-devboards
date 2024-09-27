#include <coco/debug.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

constexpr auto redPin = gpio::Config::PB6;
constexpr auto greenPin = gpio::Config::PB9;
constexpr auto bluePin = gpio::Config::PB7;
constexpr auto orangePin = gpio::Config::PB8;

void __attribute__((weak)) init() {
    // Initialize debug LEDs
    gpio::configureOutput(redPin, false);
    gpio::configureOutput(greenPin, false);
    gpio::configureOutput(bluePin, false);
    gpio::configureOutput(orangePin, false);
}

void __attribute__((weak)) set(uint32_t bits, uint32_t function) {
    gpio::setOutput(redPin, (bits & 1) != 0, (function & 1) != 0);
    gpio::setOutput(greenPin, (bits & 2) != 0, (function & 2) != 0);
    gpio::setOutput(bluePin, (bits & 4) != 0, (function & 4) != 0);
    gpio::setOutput(orangePin, (bits & 8) != 0, (function & 8) != 0);
}

void __attribute__((weak)) sleep(Microseconds<> time) {
    int64_t count = int64_t(5) * time.value;
    for (int64_t i = 0; i < count; ++i) {
        __NOP();
    }
}

void __attribute__((weak)) write(const char *message, int length) {
}

} // namespace debug
} // namespace coco
