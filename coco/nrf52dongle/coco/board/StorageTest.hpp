#pragma once

#include <coco/platform/Flash_NVMC.hpp>
#include <coco/Storage_Flash.hpp>


namespace coco {
namespace board {


// test configuraton for Storage
struct StorageTest {
        Flash_NVMC flash{0xe0000 - 4 * 32768, 4, 32768};
	Storage_Flash storage{flash};
};

}
}
