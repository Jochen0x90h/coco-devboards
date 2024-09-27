#include <coco/debug.hpp>
#include <coco/board/config.hpp>
#include <coco/platform/gpio.hpp>
#include <coco/platform/usart.hpp>


namespace coco {
namespace debug {

constexpr auto greenPin = gpio::Config::PA5;

const auto txPin = gpio::Config::PA2 | gpio::Config::AF1;
#define USART_INFO usart::USART2_INFO
constexpr auto uartClock = APB_CLOCK;
constexpr auto uartConfig = usart::Config::DEFAULT;
constexpr int baudRate = 115200;

void __attribute__((weak)) init() {
    // initialize debug LEDs
    gpio::configureOutput(greenPin, false);

    // initialize UART for debug output to virtual COM port
    {
        auto uart = USART_INFO.usart;

        // enable clock
        USART_INFO.rcc.enableClock();

        // configure tx pin
        gpio::configureAlternate(txPin);

        // set baud rate
        uart->BRR = (int(uartClock) + (baudRate >> 1)) / baudRate;

        // enable UART and transmitter
        uart->CR1 = usart::CR1(uartConfig) // config
            | USART_CR1_FIFOEN // enable FIFO
            | USART_CR1_UE // enable UART
            | USART_CR1_TE; // enable TX

        // wait until transmitter enable gets acknowledged
        while ((uart->ISR & USART_ISR_TEACK) == 0);
    }
}

void __attribute__((weak)) set(uint32_t bits, uint32_t function) {
    gpio::setOutput(greenPin, (bits & 2) != 0, (function & 2) != 0);
}

void __attribute__((weak)) sleep(Microseconds<> time) {
    int64_t count = int64_t(33) * time.value >> 2;
    for (int64_t i = 0; i < count; ++i) {
        __NOP();
    }
}

void __attribute__((weak)) write(const char *message, int length) {
    auto uart = USART_INFO.usart;

    for (int i = 0; i < length; ++i) {
        // wait until fifo has space
        while ((uart->ISR & USART_ISR_TXE_TXFNF) == 0);

        // send a character
        uart->TDR = message[i];
    }
}

} // namespace debug
} // namespace coco
