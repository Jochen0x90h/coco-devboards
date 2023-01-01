#pragma once

#include <coco/platform/QuadratureDecoder_QDEC.hpp>


namespace coco {
namespace board {

class QuadratureDecoder : public QuadratureDecoder_QDEC {
public:
       QuadratureDecoder() : QuadratureDecoder_QDEC(gpio::P0(4), gpio::P0(5)) {}
};

}
}
