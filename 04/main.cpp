#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using Area = std::vector<int>;
using Team = std::vector<Area>;
using Teams = std::vector<Team>;

const int AREAS_PER_TEAM = 2;

int main() {
  std::fstream input("../../input.txt");
  std::string line;

  std::vector<std::string> team_strings;
  std::vector<std::string> area_string;

  Area new_area;
  Team new_team;
  Teams teams;

  while (std::getline(input, line)) {
    // acquire areas and fill them into teams

    std::stringstream team_stream(line);
    team_strings.clear();

    new_team.clear();

    for (size_t i = 0; i < AREAS_PER_TEAM; i++) {
      std::string new_area_string;
      std::getline(team_stream, new_area_string, ',');
      team_strings.push_back(new_area_string);

      std::stringstream area_stream(team_strings[i]);
      area_string.clear();

      new_area.clear();

      for (size_t j = 0; j < 2; j++) {
        std::string new_boundary;
        std::getline(area_stream, new_boundary, '-');
        area_string.push_back(new_boundary);

        new_area.push_back(std::stoi(new_boundary));
      }

      new_team.push_back(new_area);

      //   std::cout << area_string[0] << "-" << area_string[1] << " ";
    }

    teams.push_back(new_team);

    // std::cout << std::endl;

    // std::cout << team_strings[0]
    //     << ", "
    //     << team_strings[1]
    //     << std::endl;
  }

  int complete_overlapping_areas_count = 0;
  int partially_overlapping_areas_count = 0;

  for (size_t i = 0; i < teams.size(); i++) {
    //   std::cout << teams[i][0][0]
    //             << "-"
    //             << teams[i][0][1]
    //             << ","
    //             << teams[i][1][0]
    //             << "-"
    //             << teams[i][1][1]
    //             << std::endl;

    if ((teams[i][0][0] <= teams[i][1][0] && teams[i][0][1] >= teams[i][1][1]) || (teams[i][0][0] >= teams[i][1][0] && teams[i][0][1] <= teams[i][1][1])) {
      // if (((teams[i][0][0] <= teams[i][1][0]) && (teams[i][0][1] >= teams[i][1][1]))) {
      //   std::cout << "found overlapping areas in team: " << i << std::endl;
      complete_overlapping_areas_count++;
    }

    if (teams[i][0][0] >= teams[i][1][0] && teams[i][0][0] <= teams[i][1][1]) {
      partially_overlapping_areas_count++;
      continue;
    }
    if (teams[i][0][1] >= teams[i][1][0] && teams[i][0][1] <= teams[i][1][1]) {
      partially_overlapping_areas_count++;
      continue;
    }
    if (teams[i][1][0] >= teams[i][0][0] && teams[i][1][0] <= teams[i][0][1]) {
      partially_overlapping_areas_count++;
      continue;
    }
    if (teams[i][1][1] >= teams[i][0][0] && teams[i][1][1] <= teams[i][0][1]) {
      partially_overlapping_areas_count++;
      continue;
    }
  }
  std::cout << "Number of completely overlapping areas: " << complete_overlapping_areas_count << std::endl;
  std::cout << "Number of partially overlapping areas: " << partially_overlapping_areas_count << std::endl;

  input.close();
}