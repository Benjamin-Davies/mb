#include <filesystem>
#include <iostream>
#include <optional>

#include <boost/program_options.hpp>

namespace fs = std::filesystem;
namespace po = boost::program_options;

struct Options
{
  fs::path maildir;
  std::optional<int> uid;
};
Options parse_options(int argc, const char *const *argv);
