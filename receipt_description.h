#ifndef CAFE_RECEIPT_DESCRIPTION_H_
#define CAFE_RECEIPT_DESCRIPTION_H_

#include "order_description.h"

#include <time.h>

namespace cafe {

struct ReceiptDescription {
  ReceiptDescription() {}
  ReceiptDescription(const OrderDescription& o,
                     time_t ts,
                     double tp,
                     const std::string& bn)
      : order(o), time_stamp(ts), total_price(tp), barista_name(bn) {}

  OrderDescription order;
  time_t time_stamp;
  double total_price;
  std::string barista_name;
};

}  // namespace cafe

#endif  // CAFE_RECEIPT_DESCRIPTION_H_
