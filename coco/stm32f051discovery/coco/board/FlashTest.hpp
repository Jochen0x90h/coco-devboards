#pragma once

#include <coco/platform/Flash_FLASH.hpp>
#include "config.hpp"


namespace coco {
namespace board {

// test configuraton for Flash
struct FlashTest {
	Flash_FLASH flash{FLASH_ADDRESS, 2, 4096};
};

}
}
