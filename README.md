## Task description

This is an Object-Oriented multi-threaded C++ program to simulate a cafe. The simulation is made up of an input file, an output file, the main-thread , and additional worker-threads each representing a barista. The amount of baristas (worker-threads) is configurable. 

The main-thread reads the input file to create orders. Each order is handled by an available barista to generate a receipt. Each receipt is serialized in the main-thread into the output file. Each barista sleeps for a random amount of seconds (3 to 6) between handling orders.

### Main-thread

* Parses the input file and creates orders.
* Each order has has an order-number dictated by the line number of the input file it was generated from.
* orders are given to/taken by available baristas.
* serializes receipts into the output file.
* A serialized receipt contains the drink order in long-form with add-ons specifying if duplicated.

### Barista (worker-thread)

* Each barista must have a unique name.
* Generates a receipt containing the total price.
* receipts are given to/taken by the main-thread.
* After processing an order, the barista sleeps for a random time between 3 to 6 seconds before handling another order.

### Input file

* A comma delimited file containing a drink order per line
* Each line starts with a letter indicating which drink it is
* A drink may contain 0 to N number of add-ons. 
* A drink may contain duplicates of the same add-on

### Receipt

* Order number
* Time-stamp of when receipt was created
* Total price
* The name of the barista which handled the order
* The drink & add-ons

## Design and implementation

 During development I assumed that both the list of baristas, drinks and add-ons are read from the configuration (text) files. For this purpose, I defined the following classes:

1. BaristaGetter - allows to get the required amound of barista's descriptions (names).
* BaristaFileGetter (Derived class from BaristaGetter) - allows to get the required amound of barista's descriptions which are read from the given configuration file.
* BaristaNumberedGetter (derived class from BaristaGetter) - Allows to get the required amound of barista's descriptions with numbered pseudo-names. It is used in case when the list of names defined in the configuration file is too short.
* BaristaGenericGetter (derived class from BaristaGetter) - Allows to get the required amound of barista's descriptions (using another BaristaGetter's derived classes: BaristaFileGetter and BaristaNumberedGetter). (example of the generic class pattern design.)
2. ProductMenu - parses the given configuration file for the product type (drinks or add-ons); it is used also as container for the product list. The instance of this class is created by ProductMenuFactory (example of factory Method Design Pattern).

The orders are parsed and managed by OrdersManager class. Whole work is done in OrdersManager::manageAllOrders method:
* gets the list of baristas,
* creates the vector of BaristaWorker's classes and vector of the threads,
* parses the given file with the orders,
* waits until all barista's threads done their work,
* serializes all receipts (generated by baristas).

Method BaristaWorker::doWork is called by the launched threads in order to process the orders. BaristaWorker class contains pointer to the OrdersManager object in order to get the next orders (available in the queue) and to send the prepared receipts back to the OrderManager.
The process of generating of the receipts takes place simultaneously with parsing the file with the orders.

 The challenge was to meet the requirements that each barista should sleep for a random amount of seconds (3 to 6) between handling orders. 
 The common way is e.g. setting a seed for randomizer based on the current time.
 However, if we use the function with precision in milliseconds, then all threads generate exactly the same "random" numbers - and consequently fall asleep at the same time.
 A solution could be to set the seed based of time with precision in nanoseconds.
There are also algorithms which allow for setting a "real" random value - based on Generating a normal distribution around a mean.
So it is possible to solve this issue on different ways.

We would also improove the implementation of BaristaWorker::doWork method. We could use condition variables to wait until OrderManager notify that a order is available in the queue.
