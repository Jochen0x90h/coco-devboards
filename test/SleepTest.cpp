#include <coco/debug.hpp>


using namespace coco;


int main() {
    debug::write("SleepTest\n");
    while (true) {
        debug::set(debug::WHITE);
        debug::write("sleep 1\n");

        // blocking sleep for 1s
        debug::sleep(1s);

        debug::set(debug::BLACK);
        debug::write("sleep 2\n");

        // blocking sleep for 1s
        debug::sleep(1s);
    }
}
