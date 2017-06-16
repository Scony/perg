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

private:
  Region mRegion;

  std::shared_ptr<File> mFile;
  std::map<unsigned, std::shared_ptr<Grep> > mGreps;
  std::map<unsigned, std::shared_ptr<TextWindow> > mTextWindows;
  unsigned mCurrentGrep;

  std::shared_ptr<StatusBar> mStatusBar;
  std::shared_ptr<Minibuffer> mMinibuffer;
};
