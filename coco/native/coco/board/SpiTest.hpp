#pragma once

#include <coco/platform/SpiMasterOut.hpp>


namespace coco {
namespace board {

// test configuraton of SPI with one channel for transfer and one for command/data
struct SpiTest {
	SpiMasterOut transfer{"transfer"};
	SpiMasterOut command{"command"};
	SpiMasterOut data{"data"};
};

}
}
