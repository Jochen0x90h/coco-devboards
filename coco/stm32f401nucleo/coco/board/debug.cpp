#include <coco/debug.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

constexpr auto greenPin = gpio::Config::PA5;

void __attribute__((weak)) init() {
    // initialize debug LEDs
    gpio::configureOutput(greenPin, false);
}

void __attribute__((weak)) set(uint32_t bits, uint32_t function) {
    gpio::setOutput(greenPin, (bits & 2) != 0, (function & 2) != 0);
}

void __attribute__((weak)) sleep(Microseconds<> time) {
    int64_t count = int64_t(12) * time.value;
    for (int64_t i = 0; i < count; ++i) {
        __NOP();
    }
}

void __attribute__((weak)) write(const char *message, int length) {
}

} // namespace debug
} // namespace coco
