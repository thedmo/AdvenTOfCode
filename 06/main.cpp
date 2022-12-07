#include <fstream>
#include <iostream>
#include <map>
#include <string>

const int SEQUENCE_LENGTH = 14;

int main() {
  std::ifstream input("../../input.txt");
  std::string line;

  std::getline(input, line);

  std::string sequence;
  int index = 0;
  std::string current_sequence;
  std::map<char, int> sequence_map;
  bool all_chars_unique = true;

  for (size_t i = 0; i < line.size(); i++) {
    // initialize
    current_sequence = line.substr(i, SEQUENCE_LENGTH);
    sequence_map.clear();
    all_chars_unique = true;

    for (size_t j = 0; j < current_sequence.size(); j++) {
      if (sequence_map.find(current_sequence.at(j)) != sequence_map.end()) {
        all_chars_unique = false;
        break;
      } else {
        sequence_map.insert(std::pair<char, int>(current_sequence.at(j), 1));
      }
    }

    std::cout << current_sequence << std::endl;
    if (!all_chars_unique) {
      continue;
    } else {
      index = i + SEQUENCE_LENGTH;
      sequence = current_sequence;
      break;
    }
  }
  std::cout << "Sequence is: " << sequence << " at index: " << index << std::endl;
}
