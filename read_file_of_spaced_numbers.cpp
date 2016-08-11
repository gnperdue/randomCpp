#include <iostream>     // NOLINT(readability/streams)
#include <fstream>      // NOLINT(readability/streams)
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char * argv[]) {

  std::string file_name = "numbers.txt";
  // numbers like:
  // 10 11
  // 12 13
  // 14 14
  // etc.
  std::ifstream file(file_name);

  std::vector<int> numbers;

  std::string line;
  while (std::getline(file, line)) {
    std::string raw_nums;
    std::istringstream iss(line);
    // use getline to split the line - first make into an istringstream
    while (std::getline(iss, raw_nums, ' ')) {
      numbers.push_back(stoi(raw_nums));
    }
  }

  for (int i : numbers) {
    std::cout << i << std::endl;
  }

  return 0;
}
