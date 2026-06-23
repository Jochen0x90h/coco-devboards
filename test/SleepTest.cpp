#include <coco/debug.hpp>
#include <coco/platform/system.hpp>


/*
    Tests debug::sleep() which is blocking
*/

using namespace coco;


int main() {
    debug::out << "SleepTest (" << system::name() << ' ' << system::version() << ")\n";
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
