#pragma once

#include <coco/platform/QuadratureDecoder_QDEC.hpp>


namespace coco {
namespace board {

// test configuraton for QuadratureDecoder
struct QuadratureDecoderTest {
       QuadratureDecoder_QDEC quadratureDecoder{gpio::P0(4), gpio::P0(5)};
};

}
}
