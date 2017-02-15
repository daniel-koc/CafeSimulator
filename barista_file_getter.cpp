#include "barista_file_getter.h"

#include <fstream>
#include <iostream>

namespace cafe {

BaristaFileGetter::~BaristaFileGetter() {
}

int BaristaFileGetter::getBaristas(BaristaDescriptions& barista_descriptions,
                                   int required_baristas) {
  if (required_baristas < 1)
    return 0;

  if (!already_parsed_file_) {
    parseBaristaDescriptionsFile();
    already_parsed_file_ = true;
  }
  int baristas_count = static_cast<int>(barista_descriptions_.size());
  if (baristas_count > required_baristas)
    baristas_count = required_baristas;

  const auto first_it = barista_descriptions_.cbegin();
  const auto last_it = first_it + baristas_count;
  barista_descriptions.insert(barista_descriptions.cbegin(), first_it, last_it);

  return baristas_count;
}

void BaristaFileGetter::parseBaristaDescriptionsFile() {
  std::vector<char> data;
  int data_size = 0;

  std::ifstream file;  //("barista_names.txt");
  // file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try {
    // Open the stream
    file.open(file_name_);
    // Determine the file length
    file.seekg(0, std::ios_base::end);
    std::size_t file_size = file.tellg();
    data_size = static_cast<int>(file_size);
    if (data_size < 0) {
      file.close();
      return;
    }
    file.seekg(0, std::ios_base::beg);
    // Reserve the space in the vector
    data.reserve(file_size);
    // Load the data
    file.read((char*)&data[0], file_size);
    // Close the file
    file.close();
  } catch (std::ios_base::failure e) {
    std::cerr << "Exception: Not found file '" << file_name_
              << "' with barista descriptions!" << std::endl;
    file.close();
    return;
    //} catch (std::ifstream::failure e) {
    // std::cerr << "Exception: Opening/reading/closing file '" << file_name_ <<
    // "' with barista descriptions!" << std::endl;
    // return;
  }

  int i = 0;
  while (i < data_size) {
    // Moving to the begin of a barista's name:
    while (i < data_size && data[i] <= ' ')
      i++;
    if (i >= data_size)
      break;

    // Calculating the size of a barista's name:
    int name_len = 1;
    while ((i + name_len) < data_size && data[i + name_len] != 10)
      name_len++;
    if ((i + name_len) >= data_size)
      break;
    int j = i + name_len + 1;
    while (data[i + name_len - 1] <= ' ')
      name_len--;

    barista_descriptions_.push_back(
        BaristaDescription(std::string(&data[i], name_len)));

    i = j;
  }
}

}  // namespace cafe
