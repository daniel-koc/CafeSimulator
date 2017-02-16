#ifndef CAFE_PRODUCTS_MENU_FACTORY_H_
#define CAFE_PRODUCTS_MENU_FACTORY_H_

#include "products_menu.h"

#include <memory>

namespace cafe {

class ProductsMenuFactory {
 protected:
  ProductsMenuFactory();

 public:
  ~ProductsMenuFactory();

  static std::unique_ptr<ProductsMenuFactory> getInstance();

  std::shared_ptr<ProductsMenu> getDrinksMenu() const { return drinks_menu_; }
  std::shared_ptr<ProductsMenu> getAdOnsMenu() const { return add_ons_menu_; }

 private:
  std::shared_ptr<ProductsMenu> drinks_menu_;
  std::shared_ptr<ProductsMenu> add_ons_menu_;
};

}  // namespace cafe

#endif  // CAFE_PRODUCTS_MENU_FACTORY_H_
