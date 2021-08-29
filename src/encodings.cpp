#include "encodings.h"

namespace encodings
{

  // See also: https://datatracker.ietf.org/doc/html/rfc1342
  std::string decode_word(const std::string &str)
  {
    if (str.size() < 8 || str[0] != '=' || str[1] != '?')
    {
      return str;
    }

    std::string res;
    size_t pos = 0;

    while (pos < str.size())
    {
      size_t divider_1 = str.find('?', pos + 2);
      size_t divider_2 = str.find('?', divider_1 + 1);
      size_t divider_3 = str.find('?', divider_2 + 1);

      std::string charset(str.begin() + pos + 2, str.begin() + divider_1);
      std::string encoding(str.begin() + divider_1 + 1, str.begin() + divider_2);
      std::string contents(str.begin() + divider_2 + 1, str.begin() + divider_3);

      boost::to_upper(charset);
      boost::to_upper(encoding);

      // TODO: these may have other values
      assert(charset == "UTF-8" || charset == "US-ASCII");
      assert(encoding.size() == 1);
      assert(str[divider_3 + 1] == '=');

      switch (encoding[0])
      {
      case 'Q':
        res += decode_quoted_printable_alt(contents);
        break;

      case 'B':
        res += decode_base64(contents);
        break;

      default:
        std::cerr << "Encountered unknown subject encoding: " << encoding << std::endl;
      }

      pos = divider_3 + 2;
    }

    return res;
  }

  std::string decode_quoted_printable_alt(const std::string &contents)
  {
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

  // Adapted from: https://stackoverflow.com/a/28471421
  std::string decode_base64(const std::string &contents)
  {
    using namespace boost::archive::iterators;
    using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
    return boost::algorithm::trim_right_copy_if(
        std::string(It(contents.begin()), It(contents.end())),
        [](char c)
        { return c == '\0'; });
  }

}
