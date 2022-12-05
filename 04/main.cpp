#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using Area = std::vector<int>;
using Team = std::map<Area, Area>;

const int AREAS_PER_TEAM = 2;

int main() {
    std::fstream input("../../input.txt");
    std::string line;

    std::vector<std::string> team_strings;
    std::vector<std::string> area_string;


    while (std::getline(input, line)) {

        //acquire areas and fill them into teams 
        std::stringstream team_stream(line);
        team_strings.clear();

        for (size_t i = 0; i < AREAS_PER_TEAM; i++)
        {
            std::string new_area;
            std::getline(team_stream, new_area, ',');
            team_strings.push_back(new_area);
            area_string.clear();

            for (size_t j = 0; j < 2; j++)
            {
                std::stringstream area_stream(team_strings[i]);
                std::string new_boundary;
                std::getline(area_stream, new_boundary, '-');
                area_string.push_back(new_boundary);
            }
        }
        // std::cout << team_strings[0]
        //     << ", "
        //     << team_strings[1]
        //     << std::endl;

    }

    input.close();
}