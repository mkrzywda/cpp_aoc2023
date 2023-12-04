#include "tasks.h"
#include <iostream>

int main(int argc, char * argv[]) {
  std::string input;
  if (argc > 1) {
    input = argv[1];
  }

  std::size_t result_a = part_a(input);
  std::size_t result_b = part_b(input);

  std::cout << "Part A Result: " << result_a << '\n';
  std::cout << "Part B Result: " << result_b << '\n';

  return 0;
}
