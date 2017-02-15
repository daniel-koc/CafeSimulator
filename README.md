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
