#include <fstream>
#include <iostream>
#include <string>

enum pick {
  rock,
  paper,
  scissors
};

enum outcome {
  win,
  draw,
  lose
};

const int win_score = 6;
const int draw_score = 3;

int CalculateScore(int elven_pick, int my_pick) {
  int my_score = my_pick + 1;

  if (
      (my_pick == pick::rock && elven_pick == pick::scissors) ||
      (my_pick == pick::paper && elven_pick == pick::rock) ||
      (my_pick == pick::scissors && elven_pick == pick::paper)) {
    my_score += win_score;
  } else if (my_pick == elven_pick) {
    my_score += draw_score;
  }

  return my_score;
}

int GetPick(char c) {
  if (c == 'A') {
    return pick::rock;
  } else if (c == 'B') {
    return pick::paper;
  } else if (c == 'C') {
    return pick::scissors;
  }
  return -1;
}

int GetWinningPick(int elven_pick) {
  return (elven_pick + 1) % 3;
}

int GetLosingPick(int elven_pick) {
  return (elven_pick + 2) % 3;
}

int GetMyPick(int elven_pick, char condition_char) {
  int condition;

  if (condition_char == 'X') {
    condition = outcome::lose;
  } else if (condition_char == 'Y') {
    condition = outcome::draw;
  } else {
    condition = outcome::win;
  }

  if (condition == outcome::win) {
    GetWinningPick(elven_pick);
  } else if (condition == outcome::draw) {
    return elven_pick;
  } else {
    return GetLosingPick(elven_pick);
  }
}

int main(int, char**) {
  std::ifstream input("../../input.txt");

  std::string line;

  int score = 0;

  char my_pick, elven_pick;

  while (std::getline(input, line)) {
    try {
      // change for wished outcome
      elven_pick = GetPick(line.at(0));
      my_pick = GetMyPick(elven_pick, line.at(2));

      score += CalculateScore(elven_pick, my_pick);
    } catch (std::exception e) {
      std::cerr << e.what() << std::endl;
    }
  }

  std::cout << score << std::endl;
}
