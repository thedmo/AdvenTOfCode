#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using Stack = std::vector<char>;

const int CRATE_STRING_SIZE = 3;

void GetStacks(std::vector<std::string> lines, std::vector<Stack> &stacks) {
  int stack_count = 0;
  int highest_stack_count = 0;

  unsigned int current_number_of_stacks = 0;
  unsigned int number_of_stacks = 0;

  //calculate number of stacks on first line and create vectors
  for (size_t i = 0; i < lines[0].size(); i++)
  {
    if ((i % 4) == 0)
    {
      number_of_stacks++;

      Stack new_stack;
      stacks.push_back(new_stack);
    }
  }
  // std::cout << "number of Stacks: " << number_of_stacks << std::endl;

// iterate through lines
  for (int i = lines.size() - 1; i >= 0; i--) {
    std::string line = lines[i];
    int stack_index = 0;

    // find crates on current line and store them into corresponding stacks
    for (int idx = line.find('[');idx != std::string::npos; idx = line.find('[', idx + 1)) {
    // for (int idx = line.find('[');idx < line.length(); idx = line.find('[', idx + 1)) {

      // get stack the current crate is on
      stack_index = idx / 4;

      // store
      if (stack_index < number_of_stacks) {
        char content(line.at(idx + 1));
        stacks[stack_index].push_back(content);
      }
    }
  }

  // for (unsigned int i = 0; i < stacks.size(); i++)
  // {
  //   for (unsigned int j = 0; j < stacks[i].size(); j++)
  //   {
  //     std::cout << stacks[i][j];
  //   }
  //   std::cout << std::endl;
  // }

}

// int GetNumber(std::string pattern, std::string line) {
//   int number = 0;

//   int index = line.find(pattern);
//   if (index != std::string::npos)
//   {
//     if (line.at(index + pattern.size() + 1) != ' '){
//     number = (line.at(index + pattern.size()) << line.at(index + pattern.size() + 1)) - '0';

//     }else{
//     number = line.at(index + pattern.size()) - '0';

//     }


//     // std::cout << "movecount is(int): " << move_count << ", (char): " << line.at(index + move_str.size()) << std::endl;
//   }
//   return number;
// }

void MoveCrate(std::string line, std::vector<Stack> &stacks) {
  std::string move_str = "move ";
  std::string from_str = "from ";
  std::string to_str = "to ";
  int move_count = 0, from_num = 0, to_num = 0;

  std::vector<std::string> line_content;
  int content_num = 0;

  std::string s;

  std::istringstream str_stream(line);

  while (getline(str_stream, s, ' ')) {
    line_content.push_back(s);
    // std::cout << line_content[content_num] << " ";
    content_num++;
  }

  // std::cout << std::endl;

  move_count = std::stoi(line_content[1]);
  from_num = std::stoi(line_content[3]) - 1;
  to_num = std::stoi(line_content[5]) - 1;

  std::cout << "move " << move_count << " from " << from_num << " to " << to_num << std::endl;
  Stack from_stack = stacks[from_num];
  Stack to_stack = stacks[to_num];

  int starting_index = 0;

  for (size_t i = move_count; i > 0; i--)
  {
    starting_index = (int)from_stack.size() - i;

    to_stack.push_back(from_stack.at(starting_index));


  }
  for (size_t i = 0; i < move_count; i++)
  {
    from_stack.pop_back();
  }
  stacks[from_num] = from_stack;
  stacks[to_num] = to_stack;


  for (size_t i = 0; i < stacks.size(); i++)
  {
    if (stacks.at(i).empty())
    {
      continue;
    }
    std::cout << stacks.at(i).back();
  }

  std::cout << std::endl;
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
      continue;
    }
    else if (line.empty()) {
      GetStacks(stack_lines, stacks);
      continue;
    }
    else if (std::find(line.begin(), line.end(), 'm') != line.end())
    {
    // Move stuff
      MoveCrate(line, stacks);
      continue;
    }
  }

  for (size_t i = 0; i < stacks.size(); i++)
  {
    std::cout << stacks.at(i).at(stacks.at(i).size() - 1);
  }

  std::cout << std::endl;

  input.close();
}