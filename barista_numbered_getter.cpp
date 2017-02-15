#include "barista_numbered_getter.h"

#include <iostream>

namespace cafe {

const char* BARISTA_PSEUDO_NAME = "Barista#";

BaristaNumberedGetter::~BaristaNumberedGetter() {
  std::cout << "BaristaNumberedGetter destroyed." << std::endl;
}

int BaristaNumberedGetter::getBaristas(
    BaristaDescriptions& barista_descriptions,
    int required_baristas) {
  if (required_baristas < 1)
    return 0;

  for (int i = 1; i <= required_baristas; i++) {
    std::string name(BARISTA_PSEUDO_NAME);
    name += std::to_string(i);
    // std::stringstream ss;
    // ss << i;
    // name = ss.str();
    barista_descriptions.push_back(BaristaDescription(name));
  }

  return required_baristas;
}

}  // namespace cafe
