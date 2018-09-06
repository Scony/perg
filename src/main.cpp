#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <cassert>
#include <iostream>
#include <ncurses.h>
#include <vector>

#include "KeyboardInput.hpp"

namespace
{
constexpr size_t SUCCESS = 0;
constexpr size_t UNHANDLED_EXCEPTION = 1;
constexpr size_t BOOST_PO_ERROR = 2;
} // namespace

int main(int argc, char** argv) try
{
  namespace po = boost::program_options;
  po::options_description visibleOptions("Options");
  visibleOptions.add_options()("help,h", "Print help messages");
  po::options_description allOptions("");
  allOptions.add_options()("filepath", po::value<std::vector<std::string>>(), "filepath");
  allOptions.add(visibleOptions);
  po::positional_options_description positionalOptions;
  positionalOptions.add("filepath", -1);
  po::variables_map vm;
  try
  {
    po::store(
        po::command_line_parser(argc, argv).options(allOptions).positional(positionalOptions).run(),
        vm);
    po::notify(vm);
  }
  catch (po::error& e)
  {
    std::cerr << e.what() << std::endl;
    return BOOST_PO_ERROR;
  }

  if (vm.count("help"))
  {
    const auto execName = boost::filesystem::basename(argv[0]);
    std::cerr << "Usage: " << execName << " [OPTION]... [FILE]..." << std::endl << std::endl;
    std::cerr << visibleOptions << std::endl;
    return SUCCESS;
  }

  std::vector<std::string> filepaths{};
  if (vm.count("filepath"))
  {
    filepaths = vm["filepath"].as<std::vector<std::string>>();
  }

  assert(setenv("TERM", "xterm-256color", 1) == 0);
  perg::tui::KeyboardInput::init();
  initscr();
  printw("It works!\n");
  for (const auto& filepath : filepaths)
  {
    printw((filepath + "\n").c_str());
  }
  refresh();
  perg::tui::KeyboardInput::awaitKeyPressed();
  endwin();
  return SUCCESS;
  ;
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return UNHANDLED_EXCEPTION;
}
