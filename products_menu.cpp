#include "products_menu.h"

#include <fstream>
#include <iostream>
#include <stdexcept>      // std::invalid_argument std::out_of_range

namespace cafe {

ProductsMenu::~ProductsMenu() {
std::cout << "ProductsMenu for " << getName() << " destruction." << std::endl;
}

bool ProductsMenu::getAt(char marker, ProductDescription& product) const {
for (auto p : product_descriptions_)
if (p.marker == marker) {
product = p;
return true;
}
return false;
}

bool ProductsMenu::parseFile(const std::string file_name) {
  std::vector<char> data;
  int data_size = 0;

  std::ifstream file;
  // file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try {
    // Open the stream
    file.open(file_name);
    // Determine the file length
    file.seekg(0, std::ios_base::end);
    std::size_t file_size = file.tellg();
    data_size = static_cast<int>(file_size);
    if (data_size < 0) {
      file.close();
      return false;
    }
    file.seekg(0, std::ios_base::beg);
    // Reserve the space in the vector
    data.reserve(file_size);
    // Load the data
    file.read((char*)&data[0], file_size);
    // Close the file
    file.close();
  } catch (std::ios_base::failure e) {
    std::cerr << "Exception: Not found file '" << file_name
              << "' with the products menu!" << std::endl;
    return false;
    //} catch (std::ifstream::failure e) {
    // std::cerr << "Exception: Opening/reading/closing file '" << file_name <<
    // "' with the products menu!" << std::endl;
    // return;
  }

int parsed_products_count = 0;
  int i = 0;
  while (i < data_size) {
    // Moving to the begin of a product description:
    while (i < data_size && data[i] <= ' ')
      i++;
    if (i >= data_size)
      break;

    // Calculating the length of a product description:
    int description_len = 1;
    while ((i + description_len) < data_size && data[i + description_len] != 10)
      description_len++;
    if ((i + description_len) >= data_size)
break;
    int j = i + description_len + 1;
    while (data[i + description_len - 1] <= ' ')
      description_len--;

// Checking if the first character is a correct product marker:
if (is_correct_product_marker_(data[i])) {
char product_marker = data[i];
// Moving to the period:
do {
i++;
description_len--;
} while (description_len > 0 && data[i] != '.');

if (description_len > 0) {
// Moving to the beggin of a product name:
do {
i++;
description_len--;
} while (description_len > 0 && !(data[i] >= 'a' && data[i] <= 'z') && !(data[i] >= 'A' && data[i] <= 'Z'));

if (description_len > 0) {
// If a name was found:
int name_len = 1;
while (name_len < description_len && data[i+name_len] != '(' && data[i+name_len] != '$')
name_len++;

if (name_len < description_len) {
// If  a marker of a price was found:
int k = i + name_len + 1;
int price_len = description_len - name_len - 1;
// Moving to the beggin of the price:
while (price_len > 0 && (data[k] <= ' ' || data[k] == '$')) {
k++;
price_len--;
}

if (price_len > 0) {
// Right-trimming the name:
    while (data[i + name_len - 1] <= ' ')
      name_len--;
// Right-trimming the price:
    while (data[k + price_len - 1] < '0' && data[k+price_len-1] > '9')
      price_len--;

try {
// Converting the price:
double price = std::stod(std::string(&data[k], price_len));

    product_descriptions_.push_back(
        ProductDescription(product_marker, std::string(&data[i], name_len), price));
parsed_products_count++;
} catch(std::invalid_argument e) {
      std::cerr << "Exception: No conversion to double could be performed for string '" << std::string(&data[k], price_len) << "'!" << std::endl;
} catch(std::out_of_range e) {
      std::cerr << "Exception: The string value '" << std::string(&data[k], price_len)
                << "' is out of the range of representable values by an double!" << std::endl;
}
}
}
}
}
}

    i = j;
  }

return (parsed_products_count > 0);
}

}  // namespace cafe
