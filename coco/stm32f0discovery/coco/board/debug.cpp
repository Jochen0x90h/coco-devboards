#include <coco/convert.hpp>
#include <coco/debug.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace debug {

constexpr auto greenPin = gpio::PC9;
constexpr auto bluePin = gpio::PC8;

void __attribute__((weak)) init() {
    // Initialize debug LEDs
    gpio::enableOutput(greenPin, false);
    gpio::enableOutput(bluePin, false);
}

void __attribute__((weak)) set(uint32_t bits, uint32_t function) {
    gpio::setOutput(greenPin, (bits & 2) != 0, (function & 2) != 0);
    gpio::setOutput(bluePin, (bits & 4) != 0, (function & 4) != 0);
}

void __attribute__((weak)) sleep(Microseconds<> time) {
    int64_t count = int64_t(20) * time.value >> 2;
    for (int64_t i = 0; i < count; ++i) {
        __NOP();
    }
}

void __attribute__((weak)) write(const char *message, int length) {
    // todo
}

} // namespace debug
} // namespace coco

// Override the __assert_func which gets called when NDEBUG is not defined
extern "C" void __assert_func(const char *file, int line, const char *func, const char *expr) {
    using namespace coco;
    debug::set(debug::RED);
    debug::out << "Assertion failed: " << expr << ", function " << func << ", file " << file << ", line " << dec(line) << '\n';
    while (true);
}
