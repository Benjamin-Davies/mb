#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>


namespace encodings
{

  std::string decode_word(const std::string &);
  std::string decode_quoted_printable_alt(const std::string &);
  std::string decode_base64(const std::string &);

}
