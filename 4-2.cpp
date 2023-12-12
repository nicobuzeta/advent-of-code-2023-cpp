#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "We should have a single input as the file to decode\n";
    return 1;
  }

  std::ifstream input_file(argv[1], std::ios_base::in);

  int count{0};
  std::string line;
  while (std::getline(input_file, line))
    count++;
  std::vector<int> repeat_games(count, 1);

  input_file.clear();
  input_file.seekg(std::ios_base::beg);

  int game_id = 0;
  while (std::getline(input_file, line)) {
    std::stringstream ss_line{line};
    ss_line.ignore(max_size, ':');

    std::string numbers;
    std::getline(ss_line, numbers, '|');

    std::set<int> winning_numbers;
    int num;
    std::stringstream ss_winning_numbers{numbers};
    while (!ss_winning_numbers.eof()) {
      ss_winning_numbers >> num;
      winning_numbers.insert(num);
    }

    std::getline(ss_line, numbers, '|');

    std::set<int> my_numbers;
    std::stringstream ss_my_numbers{numbers};
    while (!ss_my_numbers.eof()) {
      ss_my_numbers >> num;
      my_numbers.insert(num);
    }

    std::set<int> intersection;
    std::set_intersection(winning_numbers.begin(), winning_numbers.end(),
                          my_numbers.begin(), my_numbers.end(),
                          std::inserter(intersection, intersection.begin()));

    for (int o = 0; o < repeat_games[game_id]; o++) {
      for (int i = 1; i <= intersection.size(); i++) {
        repeat_games[game_id + i] += 1;
      }
    }
    game_id++;
  }

  std::cout << std::accumulate(repeat_games.begin(), repeat_games.end(), 0) << std::endl;

  return 0;
}
