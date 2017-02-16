#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>  // std::invalid_argument std::out_of_range
#include <vector>

#include "cafe_params.h"
#include "orders_manager.h"
#include "products_menu_factory.h"

int main(int argc, char* argv[]) {
  int baristas_count = 3;
  if (argc > 1) {
    try {
      baristas_count = std::stoi(argv[1]);
    } catch (std::invalid_argument e) {
      std::cerr
          << "Exception: No conversion to int could be performed for string '"
          << argv[1] << "'!" << std::endl;
    } catch (std::out_of_range e) {
      std::cerr << "Exception: The string value '" << argv[1]
                << "' is out of the range of representable values by an int!"
                << std::endl;
    }
  }
  std::cout << "Barista's count: " << baristas_count << std::endl;
  if (baristas_count < 1)
    return 0;

  auto products_menu_factory = cafe::ProductsMenuFactory::getInstance();

  std::shared_ptr<cafe::ProductsMenu> drinks_menu =
      products_menu_factory->getDrinksMenu();
  if (drinks_menu->parseFile(cafe::DRINKS_PATH)) {
    std::cout << drinks_menu->getName() << " menu:" << std::endl;
    for (int i = 0; i < drinks_menu->count(); i++) {
      const cafe::ProductDescription drink = drinks_menu->at(i);
      std::cout << drink.marker << ". " << drink.name << " ($" << drink.price
                << ")" << std::endl;
    }
    std::cout << std::endl;
  }

  std::shared_ptr<cafe::ProductsMenu> add_ons_menu =
      products_menu_factory->getAdOnsMenu();
  if (add_ons_menu->parseFile(cafe::ADD_ONS_PATH)) {
    std::cout << add_ons_menu->getName() << " menu:" << std::endl;
    for (int i = 0; i < add_ons_menu->count(); i++) {
      const cafe::ProductDescription add_ons = add_ons_menu->at(i);
      std::cout << add_ons.marker << ". " << add_ons.name << " ($"
                << add_ons.price << ")" << std::endl;
    }
    std::cout << std::endl;
  }

  std::unique_ptr<cafe::OrdersManager> orders_manager(
      new cafe::OrdersManager(drinks_menu.get(), add_ons_menu.get(),
                              cafe::ORDERS_PATH, cafe::RECEIPTS_PATH));
  orders_manager->manageAllOrders(baristas_count);

  return 0;
}
