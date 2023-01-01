#include <coco/assert.hpp>
#include <iostream>


namespace coco {
namespace debug {

bool inited = false;

void init() {
	inited = true;
}

void setRed(bool value = true) {
	assert(inited);
	std::cout << "Red " << (value ? "on" : "off") << std::endl;
}

void toggleRed() {
	assert(inited);
	std::cout << "Red toggle" << std::endl;
}

void setGreen(bool value = true) {
	assert(inited);
	std::cout << "Green " << (value ? "on" : "off") << std::endl;
}

void toggleGreen() {
	assert(inited);
	std::cout << "Green toggle" << std::endl;
}

void setBlue(bool value = true) {
	assert(inited);
	std::cout << "Blue " << (value ? "on" : "off") << std::endl;
}

void toggleBlue() {
	assert(inited);
	std::cout << "Blue toggle" << std::endl;
}

} // namespace debug
} // namespace coco
