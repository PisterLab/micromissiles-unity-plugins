#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <numeric>
#include <vector>

namespace example {

// Add two numbers.
int Add(const int a, const int b) { return a + b; }

// Calculate the sum of the floats.
float Sum(const std::vector<float>& values) {
  return std::reduce(values.cbegin(), values.cend());
}

// Generate a range of integers from 0 to size - 1.
std::vector<int> Range(const int size) {
  if (size <= 0) {
    return std::vector<int>();
  }
  std::vector<int> integers(size);
  std::iota(integers.begin(), integers.end(), 0);
  return integers;
}

// Execute the function on the given input and return the result.
float Execute(const std::function<float(float)>& function, const float input) {
  return function(input);
}

}  // namespace example

extern "C" {
// Add two numbers.
int Example_Add(const int a, const int b) { return example::Add(a, b); }

// Calculate the sum of the floats.
float Example_Sum(const float* values, const int length) {
  std::vector<float> values_vec(values, values + length);
  return example::Sum(values_vec);
}

// Generate a range of integers from 0 to size - 1.
void Example_Range(const int size, int* array, int* length) {
  const std::vector<int> integers = example::Range(size);
  std::copy(integers.cbegin(), integers.cend(), array);
  *length = integers.size();
}

// Execute the function on the given input and return the result.
float Example_Execute(float (*function)(float), const float input) {
  std::function<float(float)> function_wrapper(function);
  return example::Execute(function_wrapper, input);
}
}
