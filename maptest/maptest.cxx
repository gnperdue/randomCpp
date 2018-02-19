#include <iostream>
#include <map>

const std::map<int32_t, int32_t> planecode_to_target{
  {9, 1}, {18, 2}, {27, 3}, {44, 4}, {49, 5}
};
const std::map<int32_t, double> target_to_survival{
    {1, 0.0806985883387},
    {2, 0.0811123986095},
    {3, 0.111138474019},
    {4, 0.20879321687},
    {5, 0.160324197739}
};

int main() {

  for (int32_t i = 0; i < 173; ++i) {
    std::map<int32_t, int32_t>::const_iterator it = planecode_to_target.find(i);
    if (it != planecode_to_target.end()) {
      std::cout << planecode_to_target.at(i) << " ";
      std::map<int32_t, double>::const_iterator jt = target_to_survival.find(
          planecode_to_target.at(i)
          );
      if (jt != target_to_survival.end()) {
        std::cout << target_to_survival.at(planecode_to_target.at(i)) << std::endl;
      }
      else {
        std::cout << "error!" << std::endl;
        return 1;
      }
    }
  }

  return 0;
}
