#pragma once

#include <coco/platform/SpiMaster_SPIM3.hpp>
#include <coco/platform/gpio.hpp>


namespace coco {
namespace board {

// test configuraton of SPI with one channel for transfer and one for command/data
struct SpiTest {
	SpiMaster_SPIM3 spi{
		gpio::P0(19), // SCK
		gpio::P0(20), // MOSI
		gpio::P0(21), // MISO
		gpio::P0(21)}; // DC (data/command for write-only display, can be same as MISO)
	SpiMaster_SPIM3::Channel transfer{spi, gpio::P0(2)};
	SpiMaster_SPIM3::Channel command{spi, gpio::P0(3), SpiMaster_SPIM3::Channel::Mode::COMMAND};
	SpiMaster_SPIM3::Channel data{spi, gpio::P0(3), SpiMaster_SPIM3::Channel::Mode::DATA};
};

}
}
