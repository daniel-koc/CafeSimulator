#ifndef CAFE_BARISTA_WORKER_H_
#define CAFE_BARISTA_WORKER_H_

#include <string>

#include "receipt_description.h"

namespace cafe {

class ProductsMenu;

class BaristaWorker {
 public:
  BaristaWorker(const std::string name,
                ProductsMenu* drinks_menu,
                ProductsMenu* add_ons_menu)
      : barista_name_(name),
        drinks_menu_(drinks_menu),
        add_ons_menu_(add_ons_menu) {}

  ReceiptDescription makeReceipt(const OrderDescription& order);

 private:
  std::string barista_name_;

  ProductsMenu* drinks_menu_;
  ProductsMenu* add_ons_menu_;
};

}  // namespace cafe

#endif  // CAFE_BARISTA_WORKER_H_
