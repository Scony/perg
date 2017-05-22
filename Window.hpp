#pragma once

class Window
{
public:
  Window(int x, int y, int cols, int rows);
  virtual ~Window();

  virtual void render() = 0;

protected:
  int mX;
  int mY;
  int mCols;
  int mRows;
};
