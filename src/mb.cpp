#include "mb.h"

using namespace maildir;

int main(int argc, const char *const *argv)
{
  auto opts = parse_options(argc, argv);

  maildir::resolve(opts.maildir);

  auto iter = maildir_iterator(opts.maildir);

  if (opts.uid.has_value())
  {
    auto entry = *std::find_if(iter.begin(), iter.end(), [&opts](const Entry &e)
                               { return e.uid() == *opts.uid; });

    if (opts.toggle.has_value() || opts.set.has_value() || opts.unset.has_value())
    {
      int flags = (int)entry.flags();

      if (opts.toggle.has_value())
        flags ^= parse_flags(*opts.toggle);
      if (opts.set.has_value())
        flags |= parse_flags(*opts.set);
      if (opts.unset.has_value())
        flags &= ~parse_flags(*opts.unset);

      entry.set_flags((Flags)flags);
    }

    std::cout << entry.path() << std::endl;
  }
  else
  {
    std::vector<Entry> entries(iter.begin(), iter.end());

    std::sort(
        entries.begin(),
        entries.end(),
        [](Entry &a, Entry &b)
        {
          return a.uid() > b.uid();
        });

    for (auto entry : entries)
    {
      std::cout << entry.uid() << "\t"
                << entry.flags_str() << "\t"
                << entry.subject() << std::endl;
    }
  }
}
