#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>

#include "ApplicationController.hpp"
#include "ApplicationModel.hpp"
#include "Configuration.hpp"
#include "KeyboardInput.hpp"
#include "Ncurses.hpp"

namespace
{
constexpr size_t SUCCESS = 0;
constexpr size_t UNHANDLED_EXCEPTION = 1;
constexpr size_t BOOST_PO_ERROR = 2;

perg::types::Configuration configuration{
  grep_keystroke : "g",
  grep_circle_left_keystroke : "<S-Left>",
  grep_circle_right_keystroke : "<S-Right>",
  quit_keystroke : "q",
};
} // namespace

int main(int argc, char** argv) try
{
  namespace po = boost::program_options;
  po::options_description visibleOptions("Options");
  visibleOptions.add_options()("help,h", "Print help messages");
  po::options_description allOptions("");
  allOptions.add_options()("filepath", po::value<std::string>(), "filepath");
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
    std::cerr << "Usage: " << execName << " [OPTION]... [FILE]" << std::endl << std::endl;
    std::cerr << visibleOptions << std::endl;
    return SUCCESS;
  }

  std::vector<boost::filesystem::path> filepaths{};
  if (vm.count("filepath"))
  {
    auto raw_filepath = vm["filepath"].as<std::string>();
    filepaths.emplace_back(raw_filepath);
  }

  perg::tui::KeyboardInput::init();
  perg::tui::Ncurses ncurses;
  perg::model::ApplicationModel appModel{filepaths};
  perg::presenter::ApplicationController appController{
      configuration, appModel, perg::tui::KeyboardInput::getInstance(), ncurses};
  appController.awaitEvent();
  return SUCCESS;
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return UNHANDLED_EXCEPTION;
}
