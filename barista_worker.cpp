#include "barista_worker.h"

#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <cstdlib>
#include <sstream>  // std::stringstream
#include <time.h>
#include <thread>

#include "orders_manager.h"
#include "products_menu.h"

namespace cafe {

typedef std::chrono::high_resolution_clock Clock;

void BaristaWorker::doWork() {
  // Seed with a real random value
  /*
  auto starting_time = Clock::now();

  std::chrono::duration_cast<std::chrono::nanoseconds>(starting_time).count()

  std::chrono::time_point<std::chrono::system_clock> now =
  std::chrono::system_clock::now();
  auto epoch = now.time_since_epoch();
  auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
  long duration = value.count();
  */
  /*
  using namespace std::chrono;
      auto now = system_clock::now();
      auto now_ms = time_point_cast<milliseconds>(now);
      auto value = now_ms.time_since_epoch();
      long duration_mil = value.count();
  srand(duration_mil);
      milliseconds dur(duration_mil);
      time_point<system_clock> dt(dur);
      if (dt != now_ms)
          std::cout << "Failure." << std::endl;
      else
          std::cout << "Success." << std::endl;
  */
  // auto starting_time = Clock::now();
  srand(time(NULL));

  std::cout << "Worker Thread " << std::this_thread::get_id() << " is Executing"
            << std::endl;

  while (orders_manager_->isLoadingOrders() || orders_manager_->isNextOrder()) {
    if (orders_manager_->isNextOrder()) {
      OrderDescription order = orders_manager_->getNextOrder();
      ReceiptDescription receipt = makeReceipt(order);
      orders_manager_->addReceipt(receipt);
    }

    /*
        // Seed with a real random value, if available
        std::random_device r;
        // Choose a random mean between 1 and 6
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 6);
        int mean = uniform_dist(e1);
        std::cout << "Randomly-chosen mean: " << mean << '\n';
    // Generate a normal distribution around that mean
    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(mean, 2);
    std::map<int, int> hist;
    for (int n = 0; n < 10000; ++n) {
    ++hist[std::round(normal_dist(e2))];
    }
    //std::cout << "Normal distribution around " << mean << ":\n";
    //for (auto p : hist) {
    //std::cout << std::fixed << std::setprecision(1) << std::setw(2)
    //<< p.first << ' ' << std::string(p.second/200, '*') << '\n';
    //}
    */
    int rand = std::rand();
    // std::cout << "random: " << rand << std::endl;
    int d = 3000 + (rand % 3000);
    std::chrono::milliseconds duration(d);
    std::this_thread::sleep_for(duration);
  }
}

ReceiptDescription BaristaWorker::makeReceipt(const OrderDescription& order) {
  double total_price = 0.0;
  ProductDescription product;
  if (drinks_menu_->getAt(order.drink_marker, product))
    total_price += product.price;
  for (auto add_ons_marker : order.add_ons_markers)
    if (add_ons_menu_->getAt(add_ons_marker, product))
      total_price += product.price;
  return ReceiptDescription(order, time(0), total_price, barista_name_);
}

}  // namespace cafe
