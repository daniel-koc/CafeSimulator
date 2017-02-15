#ifndef CAFE_BARISTA_NUMBERED_GETTER_H_
#define CAFE_BARISTA_NUMBERED_GETTER_H_

#include "barista_getter.h"

namespace cafe {

/**
 * Allows for getting the required amound of barista's
 * descriptions with numbered pseudo-names.
 */
class BaristaNumberedGetter : public BaristaGetter {
 public:
  BaristaNumberedGetter() {}
  ~BaristaNumberedGetter();

  /**
   * Return the required amound of barista's descriptions with numbered
   *pseudo-names.
   *
   * @param barista_descriptions The vector into which is stored the barista's
   *descriptions.
   * @param required_baristas Required amound of baristas.
   *
   * @return The amound of barista's descriptions stored in barista_descriptions
   *vector.
   */
  int getBaristas(BaristaDescriptions& barista_descriptions,
                  int required_baristas) override;
};

}  // namespace cafe

#endif  // CAFE_BARISTA_NUMBERED_GETTER_H_
