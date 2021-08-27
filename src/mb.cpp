#include "mb.h"

int main(int argc, const char *const *argv)
{
  auto opts = parse_options(argc, argv);

  maildir::resolve(opts.maildir);

  auto entries = maildir::entries(opts.maildir);
  for (auto pos = entries.begin(); pos != entries.begin() + 10; pos++)
  {
    auto &entry = *pos;
    std::cout << entry.uid() << "\t"
              << entry.flags_str() << "\t"
              << entry.subject() << std::endl;
  }
}

Options parse_options(int argc, const char *const *argv)
{
  po::options_description desc("Allowed options");
  desc.add_options()("maildir,d", po::value<fs::path>()->default_value("INBOX"), "Directory containing mail");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cerr << desc << std::endl;
    std::exit(0);
  }

  return {
      .maildir = vm["maildir"].as<fs::path>(),
  };
}
