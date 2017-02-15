#ifndef CAFE_BARISTA_GENERIC_GETTER_H_
#define CAFE_BARISTA_GENERIC_GETTER_H_

#include <memory>

#include "barista_getter.h"

namespace cafe {

class BaristaFileGetter;
class BaristaNumberedGetter;

/**
 * Allows for getting the required amound of barista's
 * descriptions based on another BaristaGetter's derived classes.
*/
class BaristaGenericGetter : public BaristaGetter {
 public:
  BaristaGenericGetter();
  ~BaristaGenericGetter();

  int getBaristas(BaristaDescriptions& barista_descriptions,
                  int required_baristas) override;

  std::unique_ptr<BaristaFileGetter> barista_file_getter_;
  std::unique_ptr<BaristaNumberedGetter> barista_numbered_getter_;
};

}  // namespace cafe

#endif  // CAFE_BARISTA_GENERIC_GETTER_H_
