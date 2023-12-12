#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "We should have a single input as the file to decode\n";
    return 1;
  }

  std::ifstream input_file(argv[1], std::ios_base::in);
  int sum{0};

  std::string line;
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
    if (intersection.size() >= 1) {
      sum += 1 << (intersection.size() - 1);
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
