#include "orders_manager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>  // std::stringstream
#include <time.h>

#include "barista_generic_getter.h"
#include "barista_worker.h"
#include "products_menu.h"

namespace cafe {
namespace {

// trim from end
static inline std::string& rtrim(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
          s.end());
  return s;
}

}  // namespace

void OrdersManager::manageAllOrders(int baristas_count) {
  cafe::BaristaDescriptions barista_descriptions;
  std::unique_ptr<cafe::BaristaGenericGetter> barista_getter(
      new cafe::BaristaGenericGetter());
  barista_getter->getBaristas(barista_descriptions, baristas_count);
  std::for_each(barista_descriptions.begin(), barista_descriptions.end(),
                [](cafe::BaristaDescription& description) {
                  std::cout << description.name << std::endl;
                });
  std::cout << std::endl;

  if (!parseOrdersFile()) {
    std::cout << "There is no orders!" << std::endl;
    return;
  }

  std::unique_ptr<BaristaWorker> barista(new BaristaWorker(
      barista_descriptions[0].name, drinks_menu_, add_ons_menu_));

  std::cout << "Orders:" << std::endl;
  while (!isNextOrder()) {
    cafe::OrderDescription order = getNextOrder();
    std::cout << "Ordering: " << order.number << ". " << order.drink_marker
              << ", ";
    for (auto add_ons_marker : order.add_ons_markers)
      std::cout << add_ons_marker << ", ";
    std::cout << std::endl;

    ReceiptDescription receipt = barista->makeReceipt(order);
    serializeReceipt(receipt);
  }
  std::cout << std::endl;
}

bool OrdersManager::parseOrdersFile() {
  std::vector<char> data;
  int data_size = 0;

  std::ifstream file;  //("barista_names.txt");
  // file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try {
    // Open the stream
    file.open(orders_file_name_);
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
    std::cerr << "Exception: Not found file '" << orders_file_name_
              << "' with orders!" << std::endl;
    file.close();
    return false;
    //} catch (std::ifstream::failure e) {
    // std::cerr << "Exception: Opening/reading/closing file '" <<
    // orders_file_name_ <<
    // "' with orders!" << std::endl;
    // return false;
  }

  int next_order_number = 1;
  int i = 0;
  while (i < data_size) {
    // Moving to the begin of a order:
    while (i < data_size && data[i] <= ' ')
      i++;
    if (i >= data_size)
      break;

    // Calculating the size of a order:
    int order_len = 1;
    if ((i + order_len) >= data_size)
      break;
    while ((i + order_len) < data_size && data[i + order_len] != 10)
      order_len++;
    int j = i + order_len;

    if ((data[i] >= 'a' && data[i] <= 'z') ||
        (data[i] >= 'A' && data[i] <= 'Z')) {
      OrderDescription order(next_order_number, data[i]);
      i++;

      while (i < j) {
        while (i < j && (data[i] == ',' || data[i] <= ' '))
          i++;
        if (i >= j)
          break;
        if (!(data[i] >= '0' && data[i] <= '9'))
          break;
        order.add_ons_markers.push_back(data[i]);
        i++;
      }

      orders_.push_back(order);
      next_order_number++;
    }

    i = j + 1;
  }

  return true;
}

void OrdersManager::serializeReceipt(const ReceiptDescription& receipt) {
  std::stringstream ss;
  ss << "Order #" << receipt.order.number << ", ";
  // char ts_buf[20];
  // struct tm *tm;
  // tm = gmtime(&receipt.time_stamp);
  // strftime(ts_buf, sizeof(ts_buf), "%Y%m%d", tm);
  std::string tstamp(asctime(localtime(&receipt.time_stamp)));
  ss << rtrim(tstamp) << ", ";
  ss << "$" << receipt.total_price << ", ";
  ss << receipt.barista_name << ", ";
  ProductDescription product;
  if (drinks_menu_->getAt(receipt.order.drink_marker, product))
    ss << product.name;
  if (!receipt.order.add_ons_markers.empty()) {
    ss << ", ";
    std::map<char, int> add_ons_map;
    for (auto add_ons_marker : receipt.order.add_ons_markers) {
      const auto it = add_ons_map.find(add_ons_marker);
      if (it == add_ons_map.cend())
        add_ons_map[add_ons_marker] = 1;
      else
        it->second++;
    }
    for (auto add_ons_marker : receipt.order.add_ons_markers) {
      const auto it = add_ons_map.find(add_ons_marker);
      if (it != add_ons_map.cend()) {
        if (add_ons_menu_->getAt(it->first, product)) {
          ss << product.name;
          if (it->second > 1)
            ss << " x" << it->second;
        }
        add_ons_map.erase(it);
      }
      if (!add_ons_map.empty())
        ss << ", ";
    }
  }

  std::cout << ss.str() << std::endl;

  std::ofstream file;  //("barista_names.txt");
  // file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try {
    // Open the stream
    file.open(receipt_file_name_, std::ios::out | std::ios::app);
    // Determine the file length
    file << ss.str() << std::endl;
    // Close the file
    file.close();
  } catch (std::ios_base::failure e) {
    std::cerr << "Exception: Not found file '" << orders_file_name_
              << "' with orders!" << std::endl;
    file.close();
    //} catch (std::ifstream::failure e) {
    // std::cerr << "Exception: Opening/reading/closing file '" <<
    // orders_file_name_ <<
    // "' with orders!" << std::endl;
  }
}

}  // namespace cafe
