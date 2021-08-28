#include "options.h"

template <typename T>
std::optional<T> get_optional(const po::variables_map &vm, const std::string &name)
{
  if (vm.count(name))
    return vm[name].as<T>();
  else
    return std::nullopt;
}

Options parse_options(int argc, const char *const *argv)
{
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help,h", "Print help message")
      ("list,l", "List directories containing mail\n"
                 "All other options are ignored")
      ("maildir,d", po::value<fs::path>()->default_value("INBOX"), "Directory containing mail")
      ("uid,u", po::value<int>(), "UID of email to edit/print path of")
      ("toggle,t", po::value<std::string>(), "Toggle the specified flags")
      ("set,f", po::value<std::string>(), "Set the specified flags")
      ("unset,F", po::value<std::string>(), "Unset the specified flags")
      ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cerr << desc << std::endl;
    std::exit(0);
  }

  return {
      .list = vm.count("list") > 0,
      .maildir = vm["maildir"].as<fs::path>(),
      .uid = get_optional<int>(vm, "uid"),
      .toggle = get_optional<std::string>(vm, "toggle"),
      .set = get_optional<std::string>(vm, "set"),
      .unset = get_optional<std::string>(vm, "unset"),
  };
}
