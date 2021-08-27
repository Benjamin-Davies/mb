#include "mb.h"

using namespace maildir;

int main(int argc, const char *const *argv)
{
  auto opts = parse_options(argc, argv);

  maildir::resolve(opts.maildir);

  auto iter = maildir_iterator(opts.maildir);
  std::vector<Entry> entries(iter.begin(), iter.end());

  std::sort(
      entries.begin(),
      entries.end(),
      [](Entry &a, Entry &b)
      {
        return a.uid() > b.uid();
      });

  for (auto pos = entries.begin(); pos != entries.begin() + 10; pos++)
  {
    auto &entry = *pos;
    std::cout << entry.uid() << "\t"
              << entry.flags_str() << "\t"
              << entry.subject() << std::endl;
  }
}
