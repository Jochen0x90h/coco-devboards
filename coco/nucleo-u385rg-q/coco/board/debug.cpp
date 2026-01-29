#include <coco/convert.hpp>
#include <coco/debug.hpp>
#include <coco/board/config.hpp>
#include <coco/platform/gpio.hpp>
#include <coco/platform/uart.hpp>


namespace coco {
namespace debug {

constexpr auto greenPin = gpio::PA5;

const auto txPin = gpio::PA9 | gpio::AF7;
#define UART_INFO uart::USART1_INFO
constexpr auto uartClock = USART1_CLOCK;
constexpr auto uartConfig = uart::Config::ENABLE_FIFO;
constexpr auto uartFormat = uart::Format::DEFAULT;
constexpr auto baudRate = 115200Hz;

void __attribute__((weak)) init() {
    // initialize debug LEDs
    gpio::enableOutput(greenPin, false);

    // initialize UART for debug output to virtual COM port
    UART_INFO.enableClock()
        .enable(UART_INFO.enableRxTxPins(gpio::NONE, txPin, uartConfig), uartFormat, uartClock, baudRate)
        .startTx();
}

void __attribute__((weak)) set(uint32_t bits, uint32_t function) {
    gpio::setOutput(greenPin, (bits & 2) != 0, (function & 2) != 0);
}

void __attribute__((weak)) sleep(Microseconds<> time) {
    int64_t count = int64_t(int(SYS_CLOCK) / 850000) * time.value >> 3;
    for (int64_t i = 0; i < count; ++i) {
        __NOP();
    }
}

void __attribute__((weak)) write(const char *message, int length) {
    auto uart = UART_INFO.instance();

    for (int i = 0; i < length; ++i) {
        // wait until fifo has space
        uart.waitTx();

        // send a character
        uart.tx(message[i]);
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
