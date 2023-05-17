#include <coco/assert.hpp>


namespace coco {
namespace debug {

bool inited = false;
bool red = false;
bool green = false;
bool blue = false;

void init() {
     debug::inited = true;
}

void setRed(bool value) {
	assert(debug::inited);
	debug::red = value;
}

void toggleRed() {
	assert(debug::inited);
	debug::red = !debug::red;
}

void setGreen(bool value) {
	assert(debug::inited);
	debug::green = value;
}

void toggleGreen() {
	assert(debug::inited);
	debug::green = !debug::green;
}

void setBlue(bool value) {
	assert(debug::inited);
	debug::blue = value;
}

void toggleBlue() {
	assert(debug::inited);
	debug::blue = !debug::blue;
}

} // namespace debug
} // namespace coco
