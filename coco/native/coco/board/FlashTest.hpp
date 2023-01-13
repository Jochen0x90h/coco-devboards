#pragma once

#include <coco/platform/Flash_File.hpp>


namespace coco {
namespace board {


// test configuraton for Flash
struct FlashTest {
	Flash_File flash{"flashTest.bin", 2, 4096, 4};
};

}
}
