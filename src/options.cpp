#include "options.h"

Options parse_options(int argc, const char *const *argv)
{
  po::options_description desc("Allowed options");
  desc.add_options()
      ("maildir,d", po::value<fs::path>()->default_value("INBOX"), "Directory containing mail")
      ("uid,u", po::value<int>(), "UID of email to edit/print path of");

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
