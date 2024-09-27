#include <coco/debug.hpp>


using namespace coco;


int main() {
	while (true) {
		debug::set(debug::WHITE);

		// blocking sleep for 1s
		debug::sleep(1s);

		debug::set(debug::BLACK);

		// blocking sleep for 1s
		debug::sleep(1s);

		debug::write("foo\n");
	}
}
