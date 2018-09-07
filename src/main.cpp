#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>

#include "KeyboardInput.hpp"
#include "Ncurses.hpp"
#include "Region.hpp"

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

  perg::tui::KeyboardInput::init();
  perg::tui::Ncurses ncurses;
  ncurses.printw("It works!\n");
  for (const auto& filepath : filepaths)
  {
    ncurses.printw(filepath + "\n");
  }
  ncurses.printw("\n");
  auto region = ncurses.getRegion();
  ncurses.printw("Rows: " + std::to_string(region.rows) + "\n");
  ncurses.printw("Cols: " + std::to_string(region.cols) + "\n");
  ncurses.refresh();
  perg::tui::KeyboardInput::awaitKeyPressed();
  return SUCCESS;
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return UNHANDLED_EXCEPTION;
}
