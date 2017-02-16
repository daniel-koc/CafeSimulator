#ifndef CAFE_ORDERS_MANAGER_H_
#define CAFE_ORDERS_MANAGER_H_

#include <list>
#include <memory>
#include <mutex>

#include "order_description.h"
#include "receipt_description.h"

namespace cafe {

class ProductsMenu;

class OrdersManager {
 public:
  OrdersManager(ProductsMenu* drinks_menu,
                ProductsMenu* add_ons_menu,
                const std::string orders_file_name,
                const std::string receipt_file_name)
      : drinks_menu_(drinks_menu),
        add_ons_menu_(add_ons_menu),
        orders_file_name_(orders_file_name),
        receipt_file_name_(receipt_file_name) {}

  bool isNextOrder() const { orders_.empty(); }

  OrderDescription getNextOrder();
  void addReceipt(ReceiptDescription receipt);

  void manageAllOrders(int baristas_count);

 private:
  /**
    * Parse the given text file to build the order's list.
    *
    * @return True when orders could be read from the given file;
    *false otherwise.
    */
  bool parseOrdersFile();

  void serializeReceipt(const ReceiptDescription& receipt);

  ProductsMenu* drinks_menu_;
  ProductsMenu* add_ons_menu_;

  std::string orders_file_name_;
  std::string receipt_file_name_;

  std::list<OrderDescription> orders_;
  std::list<ReceiptDescription> receipts_;

  std::mutex order_mutex_;
  std::mutex receipt_mutex_;
};

}  // namespace cafe

#endif  // CAFE_ORDERS_MANAGER_H_
