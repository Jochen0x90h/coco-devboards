#include <cassert>



int main() {
    // Test assertion failure. Only works when NDEBUG is not defined.
    // Implementation is in debug.cpp, outputs to debug::out.
    // Note that when NDEBUG is not defined, the source file name ends up in the output binary.
    assert(false);
}
