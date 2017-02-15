#include "products_menu_factory.h"

#include <iostream>

namespace cafe {
namespace {
const char* DRINKS_MENU_NAME = "Drinks";
const char* ADD_ONS_MENU_NAME = "Add-ons";
}  // namespace

ProductsMenuFactory::ProductsMenuFactory() {
drinks_menu_.reset(new ProductsMenu(DRINKS_MENU_NAME, [](char marker) {
return ((marker >= 'a' && marker <= 'z') || (marker >= 'A' && marker <= 'Z'));
}));
add_ons_menu_.reset(new ProductsMenu(ADD_ONS_MENU_NAME, [](char marker) {
return (marker >= '0' && marker <= '9');
}));
}

ProductsMenuFactory::~ProductsMenuFactory() {
std::cout << "ProductsMenuFactory destruction." << std::endl;
}

//static
std::unique_ptr<ProductsMenuFactory> ProductsMenuFactory::getInstance() {
return std::unique_ptr<ProductsMenuFactory>(new ProductsMenuFactory());
}

}  // namespace cafe
