#include <cstdint>

namespace hello_world {

// Adds two numbers.
int Add(const int a, const int b) { return a + b; }

}  // namespace hello_world

extern "C" {
// Adds two numbers.
int HelloWorld_Add(const int a, const int b) { return hello_world::Add(a, b); }
}
