#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>  // std::invalid_argument std::out_of_range
#include <vector>

#include "barista_generic_getter.h"

int main(int argc, char* argv[]) {
  int baristas_count = 20;
  if (argc > 1) {
    try {
      baristas_count = std::stoi(argv[1]);
    } catch (std::invalid_argument e) {
      std::cerr
          << "Exception: No conversion to int could be performed for string '"
          << argv[1] << "'!" << std::endl;
    } catch (std::out_of_range e) {
      std::cerr << "Exception: The string value '" << argv[1]
                << "' is out of the range of representable values by an int!"
                << std::endl;
    }
  }
  std::cout << "Barista's count: " << baristas_count << std::endl;
  if (baristas_count < 1)
    return 0;

  cafe::BaristaDescriptions barista_descriptions;
  std::unique_ptr<cafe::BaristaGenericGetter> barista_getter(
      new cafe::BaristaGenericGetter());
  barista_getter->getBaristas(barista_descriptions, baristas_count);
  std::for_each(barista_descriptions.begin(), barista_descriptions.end(),
                [](cafe::BaristaDescription& description) {
                  std::cout << description.name << std::endl;
                });
  std::cout << std::endl;

  return 0;
}
