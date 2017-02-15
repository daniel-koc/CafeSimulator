#include "barista_generic_getter.h"

#include <iostream>

#include "barista_file_getter.h"
#include "barista_numbered_getter.h"
#include "cafe_params.h"

namespace cafe {

BaristaGenericGetter::BaristaGenericGetter()
    : barista_file_getter_(new BaristaFileGetter(BARISTA_NAMES_PATH)),
      barista_numbered_getter_(new BaristaNumberedGetter()) {
}

BaristaGenericGetter::~BaristaGenericGetter() {
  std::cout << "BaristaGenericGetter destroyed." << std::endl;
}

int BaristaGenericGetter::getBaristas(BaristaDescriptions& barista_descriptions,
                                      int required_baristas) {
  if (required_baristas < 1)
    return 0;

  int described_baristas_count = barista_file_getter_->getBaristas(
      barista_descriptions, required_baristas);
  if (described_baristas_count < required_baristas) {
    barista_numbered_getter_->getBaristas(
        barista_descriptions, required_baristas - described_baristas_count);
  }

  return required_baristas;
}

}  // namespace cafe
