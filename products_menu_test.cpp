#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>  // std::invalid_argument std::out_of_range
#include <vector>

#include "cafe_params.h"
#include "products_menu_factory.h"

int main(int argc, char* argv[]) {
auto products_menu_factory = cafe::ProductsMenuFactory::getInstance();

auto drinks_menu = products_menu_factory->getDrinksMenu();
if (drinks_menu->parseFile(cafe::DRINKS_PATH)) {
std::cout << drinks_menu->getName() << " menu:" << std::endl;
for (int i = 0; i < drinks_menu->count(); i++) {
const cafe::ProductDescription drink = drinks_menu->at(i);
std::cout << drink.marker << ". " << drink.name << " ($" << drink.price << ")" << std::endl;
}
  std::cout << std::endl;
}

auto add_ons_menu = products_menu_factory->getAdOnsMenu();
if (add_ons_menu->parseFile(cafe::ADD_ONS_PATH)) {
std::cout << add_ons_menu->getName() << " menu:" << std::endl;
for (int i = 0; i < add_ons_menu->count(); i++) {
const cafe::ProductDescription add_ons = add_ons_menu->at(i);
std::cout << add_ons.marker << ". " << add_ons.name << " ($" << add_ons.price << ")" << std::endl;
}
std::cout << std::endl;
}

return 0;
}
