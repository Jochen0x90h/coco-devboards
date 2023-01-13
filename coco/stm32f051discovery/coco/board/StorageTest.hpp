#pragma once

#include <coco/platform/Flash_FLASH.hpp>
#include <coco/Storage_Flash.hpp>
#include "config.hpp"


namespace coco {
namespace board {

// test configuraton for Storage
struct StorageTest {
        Flash_FLASH flash{FLASH_ADDRESS, 4, 8192};
	Storage_Flash storage{flash};
};

}
}
