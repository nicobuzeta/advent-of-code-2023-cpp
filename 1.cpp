#include <cstdint>
#include <fstream>
#include <iostream>
#include <ranges>

int get_numbers(std::string_view str) {
    std::string num_string {""};

    for (auto const& letter : str) {
        if (std::isdigit(letter)) {
            num_string += letter;
            break;
        }
    }

    for (auto const& letter : str | std::views::reverse) {
        if (std::isdigit(letter)) {
            num_string += letter;
            break;
        }
    }

    return std::stoi(num_string);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "We should have a single input as the file to decode\n";
    return 1;
  }

  std::ifstream input_file(argv[1], std::ios_base::out);

  std::string word;

  int sum = 0;

  while (input_file >> word) {
      int num = get_numbers(word);
      sum += num;
  }

  std::cout << sum << std::endl;

  return 0;
}
