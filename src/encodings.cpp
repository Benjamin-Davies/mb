#include "encodings.h"

#include <cassert>

#include <boost/algorithm/string.hpp>

namespace encodings
{

  // See also: https://datatracker.ietf.org/doc/html/rfc1342
  std::string decode_word(const std::string &str)
  {
    if (str.size() < 8 || str[0] != '=' || str[1] != '?')
    {
      return str;
    }

    size_t divider_1 = str.find('?', 2);
    size_t divider_2 = str.find('?', divider_1 + 1);
    size_t divider_3 = str.find('?', divider_2 + 1);

    std::string charset(str.begin() + 2, str.begin() + divider_1);
    std::string encoding(str.begin() + divider_1 + 1, str.begin() + divider_2);
    std::string contents(str.begin() + divider_2 + 1, str.begin() + divider_3);

    boost::to_upper(charset);
    boost::to_upper(encoding);

    // TODO: these may have other values
    assert(charset == "UTF-8" || charset == "US-ASCII");
    assert(encoding == "Q");
    assert(str[divider_3 + 1] == '=');

    std::string res;
    res.reserve(contents.size());
    for (auto pos = contents.begin(); pos != contents.end(); pos++)
    {
      switch (*pos)
      {
      case '=':
        res.push_back(std::stoi(std::string(pos + 1, pos + 3), 0, 16));
        pos += 2;
        break;
      case '_':
        res.push_back(' ');
        break;
      default:
        res.push_back(*pos);
      }
    }

    return res;
  }

}
