#pragma once

#include <coco/platform/SpiMaster_SPI1.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace board {

// test configuraton for SPI with one channel for transfer and one for command/data
struct SpiTest {
	SpiMaster_SPI1 spi{1,
		gpio::PA(5), // SCK
		gpio::PA(7), // MOSI
		gpio::PA(6)}; // MISO
	SpiMaster_SPI1::Channel transfer{spi, gpio::PA(3)};
	SpiMaster_SPI1::Channel command{spi, gpio::PA(4)};
	SpiMaster_SPI1::Channel data{spi, gpio::PA(4)};
};

}
}
