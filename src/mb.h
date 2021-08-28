#pragma once

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>

#include "options.h"
#include "maildir/dir.h"

void list_maildirs(const fs::path &base, const fs::path &path = "");
