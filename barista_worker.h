#ifndef CAFE_BARISTA_WORKER_H_
#define CAFE_BARISTA_WORKER_H_

#include <memory>
#include <string>

#include "receipt_description.h"

namespace cafe {

class OrdersManager;
class ProductsMenu;

class BaristaWorker {
 public:
  BaristaWorker(const std::string name,
                std::shared_ptr<ProductsMenu> drinks_menu,
                std::shared_ptr<ProductsMenu> add_ons_menu,
                OrdersManager* orders_manager)
      : barista_name_(name),
        drinks_menu_(drinks_menu),
        add_ons_menu_(add_ons_menu),
        orders_manager_(orders_manager) {}

  void doWork();

  ReceiptDescription makeReceipt(const OrderDescription& order);

 private:
  std::string barista_name_;

  std::shared_ptr<ProductsMenu> drinks_menu_;
  std::shared_ptr<ProductsMenu> add_ons_menu_;
  OrdersManager* orders_manager_;
};

}  // namespace cafe

#endif  // CAFE_BARISTA_WORKER_H_
