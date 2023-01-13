#pragma once

#include <coco/platform/Flash_File.hpp>
#include <coco/Storage_Flash.hpp>


namespace coco {
namespace board {


// test configuraton for Storage
struct StorageTest {
	Flash_File flash{"storageTest.bin", 4, 32768, 4};
	Storage_Flash storage{flash};
};

}
}
