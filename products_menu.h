#ifndef CAFE_PRODUCTS_MENU_H_
#define CAFE_PRODUCTS_MENU_H_

#include <string>
#include <unordered_map>

namespace cafe {

struct ProductDescription {
  ProductDescription() {}
  ProductDescription(char m, const std::string& n, double p)
      : marker(m), name(n), price(p) {}
  ProductDescription(const ProductDescription& d)
      : marker(d.marker), name(d.name), price(d.price) {}

  char marker;
  std::string name;
  double price;
};

typedef std::unordered_map<char, ProductDescription> ProductDescriptions;

class ProductsMenuFactory;

/**
  * Parse the given file into a products menu and holds it.
* This is class for drinks and add-ons and they differ by the type of the
* marker.
  */
class ProductsMenu {
 protected:
  friend class ProductsMenuFactory;

  /**
  * Function prototype for checking the corectness of the given product marker.
  */
  typedef bool (*IsCorrectProductMarker)(char marker);

  ProductsMenu(std::string menu_name,
               IsCorrectProductMarker is_correct_product_marker)
      : menu_name_(menu_name),
        is_correct_product_marker_(is_correct_product_marker) {}

 public:
  ~ProductsMenu();

  std::string getName() const { return menu_name_; }

  int count() const { static_cast<int>(product_descriptions_.size()); }

  const ProductDescription& at(int index) const;

  /**
    * Gets the product description for the given marker.
   *
   * @param marker Used to lookup in the menu.
    * @param product Output param.
    *
    * @return True when a product was found for the given marker; false
   *otherwise.
  */
  bool getAt(char marker, ProductDescription& product) const;

  /**
    * Parse the given text file to build the products menu.
    *
    * @return True when product descriptions could be read from the given file;
    *false otherwise.
    */
  bool parseFile(const std::string file_name);

 private:
  std::string menu_name_;

  IsCorrectProductMarker is_correct_product_marker_;

  ProductDescriptions product_descriptions_;
};

}  // namespace cafe

#endif  // CAFE_PRODUCTS_MENU_H_
