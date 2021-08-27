#pragma once

#include <cctype>
#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "encodings.h"

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

  typedef std::unordered_map<std::string, std::string> Headers;

  class Entry
  {
  public:
    Entry(const fs::path &path);

    fs::path &path() { return m_path; }
    int uid() { return m_uid; }
    Flags flags() { return m_flags; }

    std::string flags_str();

    Headers &headers();

    std::string subject()
    {
      std::string subject = encodings::decode_word(headers()["Subject"]);
      if (subject.empty())
      {
        return "(no subject)";
      }
      return subject;
    }

  private:
    fs::path m_path;
    int m_uid;
    Flags m_flags;
    Headers m_headers;
  };

}
