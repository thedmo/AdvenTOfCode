#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Priorities = std::vector<char>;
using Group = std::vector<std::string>;
using Groups = std::vector<Group>;

Priorities SetPriorities() {
  Priorities temp;
  char current_char = 'a';

  for (size_t i = 0; i <= 25; i++, current_char++) {
    temp.push_back(current_char);
  }

  current_char = 'A';
  for (size_t i = 26; i <= 51; i++, current_char++) {
    temp.push_back(current_char);
  }
  return temp;
}

int GetPriority(char c, Priorities priorities_table) {
  auto it = std::find(priorities_table.begin(), priorities_table.end(), c);

  int index = (it - priorities_table.begin());

  int priority = index + 1;

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

  bool is_new_group = false;
  int member_counter = 0;
  int group_counter = 0;
  Groups groups;
  Group current_group;

  while (std::getline(input, line)) {
    // create groups
    member_counter = member_counter % 3;

    if (member_counter == 0) {
      Group new_group;
      groups.push_back(new_group);
    }
    groups[groups.size() - 1].push_back(line);

    member_counter++;

    // Find item
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

    char result;

    for (auto it = first_compartment.begin(); it < first_compartment.end(); it++) {
      auto finding = std::find(second_compartment.begin(), second_compartment.end(), *it);

      if (finding != std::end(second_compartment)) {
        if (*finding == *it) {
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

  // find Badges
  char compare_char;
  std::cout << groups.size() << std::endl;
  int priority_sum_of_badges = 0;
  int badge_count = 0;

  for (size_t i = 0; i < groups.size(); i++) {
    Group cur_group = groups[i];

    std::string member_one = cur_group[0];
    std::string member_two = cur_group[1];
    std::string member_three = cur_group[2];

    for (auto it1 = member_one.begin(); it1 < member_one.end(); it1++) {
      compare_char = *it1;
      auto result1 = std::find(member_two.begin(),
                               member_two.end(),
                               compare_char);

      if (result1 == member_two.end()) {
        continue;
      }

      auto result2 = std::find(member_three.begin(),
                               member_three.end(),
                               compare_char);

      if (result2 == member_three.end()) {
        continue;
      }
      badge_count++;
      priority_sum_of_badges += GetPriority(compare_char, priorities);
      break;
    }
  }

  std::cout << "Sum of badge priorities: "
            << priority_sum_of_badges
            << ", badges found: "
            << badge_count
            << std::endl;
  input.close();
}