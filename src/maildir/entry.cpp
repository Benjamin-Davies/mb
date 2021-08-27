#include "entry.h"

namespace maildir
{

  // See also: https://cr.yp.to/proto/maildir.html
  // and: https://github.com/djnym/isync/blob/master/src/sync.c
  const char *FLAGS = "DFRST";
  const int FLAG_COUNT = 6;

  Flags parse_flags(const std::string &str)
  {
    int flags = NONE;
    for (auto &c : str)
    {
      for (int i = 0; i < FLAG_COUNT; i++)
      {
        if (c == FLAGS[i])
        {
          flags |= 1 << i;
        }
      }
    }
    return (Flags)flags;
  }

  std::string to_string(Flags flags)
  {
    std::string str;
    for (int i = 0; i < FLAG_COUNT; i++)
    {
      if (flags & 1 << i)
      {
        str += FLAGS[i];
      }
    }
    return str;
  }

  Entry::Entry(const fs::path &path) : m_path(path)
  {
    // of the form "...,U=uid:2,flags"
    std::string filename = m_path.filename();
    size_t col_pos = filename.rfind(':');
    size_t eq_pos = filename.rfind('=', col_pos);

    std::string uid(filename.begin() + eq_pos + 1, filename.begin() + col_pos);
    m_uid = std::stoi(uid);

    std::string flags(filename.begin() + col_pos + 3, filename.end());
    m_flags = parse_flags(flags);
  }

  std::string Entry::flags_str()
  {
    return to_string(m_flags);
  }

}