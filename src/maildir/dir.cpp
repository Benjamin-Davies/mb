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

  std::vector<Entry> entries(const fs::path &dir)
  {
    std::vector<Entry> entries;

    auto iter_dir = [&entries, &dir](const char *sub_dir)
    {
      for (auto &file : fs::directory_iterator(dir / sub_dir))
      {
        if (file.is_regular_file() && !is_hidden(file.path()))
        {
          Entry entry(file.path());
          entries.push_back(entry);
        }
      }
    };

    iter_dir("new");
    iter_dir("cur");

    std::sort(
        entries.begin(),
        entries.end(),
        [](Entry &a, Entry &b)
        {
          return a.uid() > b.uid();
        });

    return entries;
  }

}
