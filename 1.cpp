#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>

std::map<std::string, int> conv{
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

std::optional<int> custom_isdigit(int pos, std::string_view str) {
  char letter = str[pos];
  if (std::isdigit(letter)) {
    return letter - '0';
  }

  for (auto const &[key, value] : conv) {
    std::string_view possible_match = str.substr(pos, key.size());
    if (possible_match == key) {
      return value;
    }
  }
  return {};
}

int get_numbers(std::string str) {
  std::string num_string{""};

  for (auto it = str.begin(); it != str.end(); it++) {
    int pos = it - str.begin();
    std::optional<int> num = custom_isdigit(pos, str);

    if (num.has_value()) {
      num_string += std::to_string(num.value());
      break;
    }
  }

  for (auto it = str.rbegin(); it != str.rend(); it++) {
    int pos = str.rend() - it - 1;
    std::optional<int> num = custom_isdigit(pos, str);

    if (num.has_value()) {
      num_string += std::to_string(num.value());
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
