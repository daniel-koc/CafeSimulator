#include "barista_worker.h"

#include <time.h>

#include "products_menu.h"

namespace cafe {

ReceiptDescription BaristaWorker::makeReceipt(const OrderDescription& order) {
  double total_price = 0.0;
  ProductDescription product;
  if (drinks_menu_->getAt(order.drink_marker, product))
    total_price += product.price;
  for (auto add_ons_marker : order.add_ons_markers)
    if (add_ons_menu_->getAt(add_ons_marker, product))
      total_price += product.price;
  return ReceiptDescription(order, time(0), total_price, barista_name_);
}

}  // namespace cafe
