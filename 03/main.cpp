#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Priorities = std::vector<char>;

Priorities SetPriorities() {
  Priorities temp;
  char current_char = 'a';
  for (size_t i = 0; i <= 25; i++, current_char++) {
    temp.push_back(current_char);
    std::cout << current_char << std::endl;
  }

  current_char = 'A';
  for (size_t i = 26; i <= 51; i++, current_char++) {
    temp.push_back(current_char);
    std::cout << current_char << std::endl;
  }

  return temp;
}

int GetPriority(char c, Priorities priorities_table) {
  auto it = std::find(priorities_table.begin(), priorities_table.end(), c);

  int index = (it - priorities_table.begin());

  int priority = index + 1;

  std::cout << "Priority: " << std::to_string(priority) << std::endl;

  return priority;
}

int main(int, char**) {
  std::fstream input("../../input.txt");
  std::string line;

  Priorities priorities = SetPriorities();

  int sum_of_priorities = 0;
  int compartment_size;

  std::string first_compartment;
  std::string second_compartment;

  while (std::getline(input, line)) {
    first_compartment = "";
    second_compartment = "";
    compartment_size = line.length() / 2;

    try {
      for (auto it = line.begin(); it < (line.begin() + (compartment_size)); it++) {
        first_compartment += *it;
      }

      for (auto it = (line.begin() + (compartment_size)); it < line.end(); it++) {
        second_compartment += *it;
      }
    } catch (std::exception e) {
      std::cerr << e.what();
    }

    try {
      std::cout << '\n'
                << first_compartment << '\n'
                << second_compartment << std::endl;
    } catch (std::exception e) {
      std::cerr << e.what();
    }

    char result;

    for (auto it = first_compartment.begin(); it < first_compartment.end(); it++) {
      auto finding = std::find(second_compartment.begin(), second_compartment.end(), *it);

      if (finding != std::end(second_compartment)) {
        if (*finding == *it) {
          std::cout << "Found: " << *finding << std::endl;
          result = *finding;
          break;
        }
      };
    }

    try {
      sum_of_priorities += GetPriority(result, priorities);
    } catch (std::exception e) {
      std::cerr << e.what() << std::endl;
    }
  }

  std::cout << std::to_string(sum_of_priorities) << std::endl;
}