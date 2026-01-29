#include <coco/convert.hpp>
#include <coco/debug.hpp>
#include <coco/platform/gpio.hpp>
#include <coco/platform/uart.hpp>


namespace coco {
namespace debug {

constexpr auto redPin = gpio::P0_23 | gpio::Config::INVERT;
constexpr auto greenPin = gpio::P0_22 | gpio::Config::INVERT;
constexpr auto bluePin = gpio::P0_24 | gpio::Config::INVERT;

const auto txPin = gpio::P0_8;//10;
#define UART_INFO uart::UART0_INFO
constexpr auto uartConfig = uart::Config::DEFAULT;
constexpr auto uartFormat = uart::Format::DEFAULT;
constexpr auto baudRate = 115200Hz;

void __attribute__((weak)) init() {
    // Initialize debug LEDs
    gpio::enableOutput(redPin, false);
    gpio::enableOutput(greenPin, false);
    gpio::enableOutput(bluePin, false);

    // initialize UART for debug output to virtual COM port
    UART_INFO.instance()
        .enable(UART_INFO.enableRxTxPins(gpio::NONE, txPin, uartConfig), uartFormat, baudRate)
        .startTx();
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
    auto uart = UART_INFO.instance();

    for (int i = 0; i < length; ++i) {
        // send a character
        uart.tx(message[i]);

        // wait until character is sent
        uart.waitTx();
    }
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
