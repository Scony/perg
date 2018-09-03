#pragma once

#include <string>
#include <memory>
#include <map>

#include "StatusBar.hpp"
#include "Minibuffer.hpp"
#include "Region.hpp"
#include "File.hpp"
#include "FileController.hpp"
#include "TextWindow.hpp"

class ApplicationController
{
public:
  ApplicationController(Region region);

  void run();

  void openFile(const std::string& filePath);

private:
  Region mRegion;

  std::map<unsigned, std::shared_ptr<File> > mFiles;
  std::map<unsigned, std::shared_ptr<FileController> > mFileControllers;
  int mCurrentFile;

  std::shared_ptr<StatusBar> mStatusBar;
  std::shared_ptr<Minibuffer> mMinibuffer;
  std::shared_ptr<TextWindow> mWelcomeWindow;
};
