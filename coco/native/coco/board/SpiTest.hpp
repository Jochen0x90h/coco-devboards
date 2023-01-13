#pragma once

#include <coco/platform/SpiMaster_cout.hpp>


namespace coco {
namespace board {

// test configuraton for SPI with one channel for transfer and one for command/data
struct SpiTest {
	SpiMaster_cout transfer{"transfer"};
	SpiMaster_cout command{"command"};
	SpiMaster_cout data{"data"};
};

}
}
