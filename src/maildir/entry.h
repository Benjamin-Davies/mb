#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace maildir
{

  enum Flags
  {
    NONE = 0,
    DRAFT = 1 << 0,
    FLAGGED = 1 << 1,
    REPLIED = 1 << 2,
    SEEN = 1 << 3,
    TRASHED = 1 << 4,
  };

  Flags parse_flags(const std::string &);
  std::string to_string(Flags);

  class Entry
  {
  public:
    Entry(const fs::path &path);

    fs::path &path() { return m_path; }
    int uid() { return m_uid; }
    Flags flags() { return m_flags; }

    std::string flags_str();

  private:
    fs::path m_path;
    int m_uid;
    Flags m_flags;
  };

}
