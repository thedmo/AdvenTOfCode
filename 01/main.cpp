#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream input;
  input.open("C:/Users/MinJa/dev/AdventOfCode/01/input.txt");

  std::cout << "Beginning to count..." << std::endl;

  std::string line;

  // input.getline(newLine)

  std::vector<int> elves;

  unsigned int index = 0;
  int current_calories;

  int biggest_amount = 0;

  if (!input.good()) {
    std::cout << "input not good..." << std::endl;
  }

  while (std::getline(input, line)) {
    if (line.empty()) {
      std::cout << "next please!" << std::endl;
      index++;
      continue;
    }

    try {
      current_calories = std::stoi(line);
      if (index >= (elves.size())) {
        elves.push_back(current_calories);
      } else {
        elves.at(index) += current_calories;
      }

    } catch (std::exception e) {
      std::cerr << e.what() << std::endl;
    }

    if (elves.at(index) > biggest_amount) {
      biggest_amount = elves.at(index);
      std::cout << "new max found: " << std::to_string(biggest_amount) << std::endl;
    }
  }
  std::cout << "biggest amount: " << std::to_string(biggest_amount) << std::endl;
}
