#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream input("../../input.txt");
  std::string line;

  std::getline(input, line);

  std::string sequence;
  int index;

  for (size_t i = 0; i < line.size(); i++) {
    if (line.at(i) == line.at(i + 1)) {
      continue;
    } else {
      if (line.at(i + 1) == line.at(i + 2) || line.at(i) == line.at(i + 2)) {
        continue;
      } else {
        if (line.at(i + 2) == line.at(i + 3) || line.at(i + 1) == line.at(i + 3) || line.at(i) == line.at(i + 3)) {
          continue;
        } else {
          sequence += line.at(i);
          sequence += line.at(i + 1);
          sequence += line.at(i + 2);
          sequence += line.at(i + 3);
          index = i + 4;
          break;
        }
      }
    }
  }

  std::cout << "Sequence is: " << sequence << " at index: " << index << std::endl;
}