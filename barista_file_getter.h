#ifndef CAFE_BARISTA_FILE_GETTER_H_
#define CAFE_BARISTA_FILE_GETTER_H_

#include "barista_getter.h"

namespace cafe {

/**
 * Allows for getting the required amound of barista's
 * descriptions which reads from the given file.
 */
class BaristaFileGetter : public BaristaGetter {
 public:
  BaristaFileGetter(const std::string file_name)
      : file_name_(file_name), already_parsed_file_(false) {}
  ~BaristaFileGetter();

  /**
   * Tries to return the required amound of barista's descriptions defined in
   *the given file.
   *
   * @param barista_descriptions The vector into which is stored the barista's
   *descriptions.
   * @param required_baristas Required amound of baristas.
   *
   * @return The amound of barista's descriptions stored in barista_descriptions
   *vector.
   */
  int getBaristas(BaristaDescriptions& barista_descriptions,
                  int required_baristas) override;

 private:
  void parseBaristaDescriptionsFile();

  std::string file_name_;
  BaristaDescriptions barista_descriptions_;
  bool already_parsed_file_;
};

}  // namespace cafe

#endif  // CAFE_BARISTA_FILE_GETTER_H_
