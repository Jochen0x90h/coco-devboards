#pragma once

#include <coco/platform/Flash_NVMC.hpp>


namespace coco {
namespace board {


// test configuraton for Flash
struct FlashTest {
	Flash_NVMC flash{0xe0000 - 2 * 4096, 2, 4096};
};

}
}
