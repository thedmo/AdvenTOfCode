#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Stack = std::vector<std::string>;

const int CRATE_STRING_SIZE = 3;

void GetStacks(std::vector<std::string> lines, std::vector<Stack> &stacks) {
  int stack_count = 0;
  int highest_stack_count = 0;
  // iterate through lines
  for (size_t i = lines.size() - 1; i >= 0; i++) {
    std::string line = lines[i];

    // separate crates and populate stacks with them
  }
}

int main() {
  std::fstream input("../../input.txt");
  std::string line;

  std::vector<std::string> stack_lines;
  std::vector<Stack> stacks;

  while (std::getline(input, line)) {
    // Create Stacks
    if (std::find(line.begin(), line.end(), '[') != line.end()) {
      stack_lines.push_back(line);
    } else if (line.empty()) {
      //   std::cout << "stacks done at line " << stack_lines.size() << std::endl;
      GetStacks(stack_lines, stacks);
    }

    // Move stuff
  }

  input.close();
}