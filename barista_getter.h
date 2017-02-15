#ifndef CAFE_BARISTA_GETTER_H_
#define CAFE_BARISTA_GETTER_H_

#include <string>
#include <vector>

namespace cafe {

struct BaristaDescription {
  BaristaDescription() {}
  BaristaDescription(const std::string& n) { name = n; }
  BaristaDescription(const BaristaDescription& d) { name = d.name; }

  std::string name;
};

typedef std::vector<BaristaDescription> BaristaDescriptions;

/**
 * Abstract class which allows for getting the required amound of barista's
 * descriptions.
 */
class BaristaGetter {
 protected:
  BaristaGetter() {}

 public:
  virtual ~BaristaGetter() {}

  /**
   * Tries to return the required amound of barista's descriptions.
   *
   * @param barista_descriptions The vector into which is stored the barista's
   *descriptions.
   * @param required_baristas Required amound of baristas.
   *
   * @return The amound of barista's descriptions stored in barista_descriptions
   *vector.
   */
  virtual int getBaristas(BaristaDescriptions& barista_descriptions,
                          int required_baristas) = 0;
};

}  // namespace cafe

#endif  // CAFE_BARISTA_GETTER_H_
