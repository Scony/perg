#pragma once

#include <memory>

#include "Controller.hpp"
#include "File.hpp"
#include "StatusBar.hpp"
#include "Minibuffer.hpp"

class FileController : public Controller
{
public:
  FileController(WINDOW * window,
		 std::shared_ptr<File> file,
		 std::shared_ptr<StatusBar> statusBar,
		 std::shared_ptr<Minibuffer> minibuffer);

  void run();
  // ??? getEvent();

private:
  std::shared_ptr<File> mFile;

  std::shared_ptr<StatusBar> mStatusBar;
  std::shared_ptr<Minibuffer> mMinibuffer;
};
