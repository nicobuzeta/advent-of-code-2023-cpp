#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "We should have a single input as the file to decode\n";
    return 1;
  }
  std::vector<std::vector<char>> matrix;

  std::ifstream input_file(argv[1], std::ios_base::in);

  std::string line;

  while (std::getline(input_file, line)) {
    std::vector<char> line_vector(line.begin(), line.end());
    matrix.push_back(line_vector);
  }

  uint sum = 0;

  for (int outer_idx = 0; outer_idx < matrix.size(); outer_idx++) {
    std::vector<char> line_vector = matrix[outer_idx];
    std::string accumulated{""};
    bool valid_accumulate{false};
    for (int inner_idx = 0; inner_idx < line_vector.size(); inner_idx++) {
      std::array<char, 8> symbol;
      symbol.fill('o');
      int last_filled = 0;
      bool isnum = std::isdigit(line_vector[inner_idx]);
      if (!isnum) {
        if (valid_accumulate) {
          sum += std::stoi(accumulated);
          accumulated = "";
          valid_accumulate = false;
        } else {
          accumulated = "";
        }
        continue;
      }
      // Check left and top left and down left
      if (inner_idx != 0) {
        symbol[last_filled++] = line_vector[inner_idx - 1];
        if (outer_idx != 0) {
          symbol[last_filled++] = matrix[outer_idx - 1][inner_idx - 1];
        }
        if (outer_idx != (matrix.size() - 1)) {
          symbol[last_filled++] = matrix[outer_idx + 1][inner_idx - 1];
        }
      }
      // Check right and top right and down right
      if (inner_idx != (line_vector.size() - 1)) {
        symbol[last_filled++] = line_vector[inner_idx + 1];
        if (outer_idx != 0) {
          symbol[last_filled++] = matrix[outer_idx - 1][inner_idx + 1];
        }
        if (outer_idx != (matrix.size() - 1)) {
          symbol[last_filled++] = matrix[outer_idx + 1][inner_idx + 1];
        }
      }
      // Check up
      if (outer_idx != 0) {
        symbol[last_filled++] = matrix[outer_idx - 1][inner_idx];
      }
      // Check down
      if (outer_idx != (matrix.size() - 1)) {
        symbol[last_filled++] = matrix[outer_idx + 1][inner_idx];
      }
      bool test = std::ranges::any_of(
          symbol, [](char c) { return !(std::isalnum(c) || c == '.'); });
      accumulated += line_vector[inner_idx];
      std::cout << accumulated << std::endl;
      std::cout << test << valid_accumulate << std::endl;
      if (test) {
        valid_accumulate = true;
      }
      std::cout << sum << std::endl;
      for (auto item : symbol) {
        std::cout << item << " ";
      }
      std::cout << test << std::endl;
    }
    if (valid_accumulate) {
      sum += std::stoi(accumulated);
      accumulated = "";
      valid_accumulate = false;
    } else {
      accumulated = "";
    }
  }
  std::cout << sum << std::endl;

  return 0;
}
