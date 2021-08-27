#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "entry.h"

namespace fs = std::filesystem;

namespace maildir
{

  fs::path &resolve(fs::path &);

  fs::path locate();

  bool is_maildir(const fs::path &);

  std::vector<Entry> entries(const fs::path &);

}
