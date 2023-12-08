#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

std::map<std::string, int> need = {{"red", 12}, {"green", 13}, {"blue", 14}};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "We should have a single input as the file to decode\n";
    return 1;
  }

  std::ifstream input_file(argv[1], std::ios_base::out);

  int id = 1;
  int sum_works = 0;
  int sum_power = 0;
  std::string line;

  while (std::getline(input_file, line)) {
    std::map<std::string, int> max_colors;
    std::stringstream ss_game(line);
    ss_game.ignore(max_size, ':');
    std::string sample;
    while (std::getline(ss_game, sample, ';')) {
      std::stringstream ss_sample(sample);
      std::string num_color;
      int num;
      std::string color;
      while (std::getline(ss_sample, num_color, ',')) {
        std::stringstream ss_num_color(num_color);
        ss_num_color >> num;
        ss_num_color >> color;
        if (max_colors.contains(color)) {
          max_colors[color] = std::max(max_colors[color], num);
        } else {
          max_colors[color] = num;
        }
      }
    }

    // Part 1
    // bool works = true;
    // for (auto const& [key, item] : need) {
    //   if (max_colors.contains(key) && max_colors[key] > item) {
    //     works = false;
    //     break;
    //   }
    // }
    //
    // if (works) {
    //   sum_works += id;
    // }
    
    int power = 1;
    for (auto const& [key, item] : max_colors) {
      power *= item;
    }

    sum_power += power;

    id++;
  }

  // std::cout << sum_works << std::endl;
  std::cout << sum_power << std::endl;

  return 0;
}
