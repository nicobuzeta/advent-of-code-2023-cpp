#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

int num_val(std::vector<std::vector<char>> &matrix,
            std::pair<int, int> start_coord) {
  std::string num {""};
  for (int column = start_coord.second; column != matrix[start_coord.first].size() && std::isdigit(matrix[start_coord.first][column]); column++) {
    num += matrix[start_coord.first][column];
  }
  return std::stoi(num);
}

std::pair<int, int> num_start_coord(std::vector<std::vector<char>> &matrix,
                                    std::pair<int, int> start_coord) {
  int row = start_coord.first;
  for (int column = start_coord.second; column != 0; column--) {
    if (!std::isdigit(matrix[row][column])) {
      return {row, column += 1};
    }
  }
  return {row, 0};
}

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
    for (int inner_idx = 0; inner_idx < line_vector.size(); inner_idx++) {
      if (matrix[outer_idx][inner_idx] != '*') {
        continue;
      }
      std::vector<std::pair<int, int>> symbs;
      // Check left and top left and down left
      if (inner_idx != 0) {
        symbs.emplace_back(outer_idx, inner_idx - 1);

        if (outer_idx != 0) {
          symbs.emplace_back(outer_idx - 1, inner_idx - 1);
        }
        if (outer_idx != (matrix.size() - 1)) {
          symbs.emplace_back(outer_idx + 1, inner_idx - 1);
        }
      }
      // Check right and top right and down right
      if (inner_idx != (line_vector.size() - 1)) {
        symbs.emplace_back(outer_idx, inner_idx + 1);
        if (outer_idx != 0) {
          symbs.emplace_back(outer_idx - 1, inner_idx + 1);
        }
        if (outer_idx != (matrix.size() - 1)) {
          symbs.emplace_back(outer_idx + 1, inner_idx + 1);
        }
      }
      // Check up
      if (outer_idx != 0) {
        symbs.emplace_back(outer_idx - 1, inner_idx);
      }
      // Check down
      if (outer_idx != (matrix.size() - 1)) {
        symbs.emplace_back(outer_idx + 1, inner_idx);
      }
      std::set<std::pair<int, int>> num_locations;
      std::ranges::for_each(
          symbs | std::views::filter([matrix](std::pair<int, int> coord) {
            return std::isdigit(matrix[coord.first][coord.second]);
          }),
          [&num_locations, &matrix](std::pair<int, int> coord) {
            num_locations.insert(num_start_coord(matrix, coord));
          });

      if (num_locations.size() == 2) {
        auto values = num_locations | std::views::transform([&matrix](std::pair<int, int> coord) {
            return num_val(matrix, coord);
            });
        std::cout << std::endl;
        sum += std::accumulate(values.begin(), values.end(), 1, std::multiplies<>());
      }
    }
  }
  std::cout << sum << std::endl;

  return 0;
}
