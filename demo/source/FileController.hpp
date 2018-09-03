#pragma once

#include <memory>
#include <map>

#include "Region.hpp"
#include "File.hpp"
#include "StatusBar.hpp"
#include "Minibuffer.hpp"
#include "Event.hpp"
#include "TextWindow.hpp"

class FileController
{
public:
  FileController(Region region,
		 std::shared_ptr<File> file,
		 std::shared_ptr<StatusBar> statusBar,
		 std::shared_ptr<Minibuffer> minibuffer);

  Event proceed();

private:
  void addGrep(std::shared_ptr<Grep> grep);

  void nopHandler();
  void grepHandler();
  void circleGrepsLeftHandler();
  void circleGrepsRightHandler();
  void focusHandler();
  void focusReleaseHandler();
  void markHandler();

  std::map<std::string, std::function<void()> > mActiveHandlers = {
    {"<>", std::bind(&FileController::nopHandler, this)},
    {"g", std::bind(&FileController::grepHandler, this)},
    {"<M-Up>", std::bind(&FileController::circleGrepsLeftHandler, this)},
    {"<M-Down>", std::bind(&FileController::circleGrepsRightHandler, this)},
    {"f", std::bind(&FileController::focusHandler, this)},
    {"m", std::bind(&FileController::markHandler, this)},
  };

  Region mRegion;

  std::shared_ptr<File> mFile;
  std::map<unsigned, std::shared_ptr<Grep> > mGreps;
  std::map<unsigned, std::shared_ptr<TextWindow> > mTextWindows;
  unsigned mCurrentGrep;

  std::shared_ptr<TextWindow> mFocusWindow;

  std::shared_ptr<StatusBar> mStatusBar;
  std::shared_ptr<Minibuffer> mMinibuffer;
};
