#include "dir.h"

#include <algorithm>

namespace maildir
{

  fs::path locate()
  {
    fs::path home = std::getenv("HOME");
    for (auto &dir : {".local/share/mail", "mail", "Mail"})
    {
      auto abs_dir = home / dir;
      if (fs::is_directory(abs_dir))
        return abs_dir;
    }
    std::cerr << "Could not locate maildir" << std::endl;
    std::exit(1);
  }

  bool is_maildir(const fs::path &dir)
  {
    return fs::is_directory(dir / "cur") &&
           fs::is_directory(dir / "new") &&
           fs::is_directory(dir / "tmp");
  }

  fs::path &resolve(fs::path &dir)
  {
    if (!is_maildir(dir))
    {
      dir = locate() / dir;

      if (!is_maildir(dir))
      {
        std::cerr << "Directory " << dir << " does not have maildir sub-dirs" << std::endl;
        std::exit(1);
      }
    }

    return dir;
  }

  bool is_hidden(const fs::path &file)
  {
    std::string filename = file.filename();
    return filename.size() > 0 && filename[0] == '.';
  }

  void maildir_iterator::next()
  {
    if (m_state == Empty)
      return;

    if (m_state == Initial)
    {
      m_dir = fs::directory_iterator(*m_path / "new");
      m_state = ReadingNew;
    }

    if (dir_end())
    {
      if (m_state == ReadingNew)
      {
        m_dir = fs::directory_iterator(*m_path / "cur");
        m_state = ReadingCur;

        if (dir_end())
        {
          set_empty();
          return;
        }
      }
      else
      {
        set_empty();
        return;
      }
    }

    m_current = Entry((*m_dir)->path());
    (*m_dir)++;
  }

  bool maildir_iterator::dir_end() const
  {
    return *m_dir == fs::directory_iterator();
  }

  void maildir_iterator::set_empty()
  {
    m_state = Empty;
    m_path = std::nullopt;
    m_dir = std::nullopt;
    m_current = std::nullopt;
  }

}
