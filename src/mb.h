#pragma once

#include <filesystem>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "maildir/dir.h"

namespace po = boost::program_options;

struct Options
{
  fs::path maildir;
};
Options parse_options(int argc, const char *const *argv);
