#include <filesystem>
#include <iostream>
#include <optional>

#include <boost/program_options.hpp>

namespace fs = std::filesystem;
namespace po = boost::program_options;

struct Options
{
  bool list;
  fs::path maildir;
  std::optional<int> uid;
  std::optional<std::string> toggle;
  std::optional<std::string> set;
  std::optional<std::string> unset;
};
Options parse_options(int argc, const char *const *argv);
