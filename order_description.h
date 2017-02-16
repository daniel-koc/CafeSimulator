#ifndef CAFE_ORDER_DESCRIPTION_H_
#define CAFE_ORDER_DESCRIPTION_H_

#include <string>
#include <vector>

namespace cafe {

struct OrderDescription {
  OrderDescription() {}
  OrderDescription(int n, char m) : number(n), drink_marker(m) {}

  int number;
  char drink_marker;
  std::vector<char> add_ons_markers;
};

}  // namespace cafe

#endif  // CAFE_ORDER_DESCRIPTION_H_
