#include <iostream>
#include <ncurses.h>

#include "Controller.hpp"
// #include <fstream>
// #include <vector>

// int rows;
// int cols;

int main(int argc, char ** argv)
{
  // if (argc < 2)
  //   {
  //     std::cerr << "Usage: ./a.out [FILE_NAME]" << std::endl;
  //     return 1;
  //   }

  initscr();
  keypad(stdscr, TRUE);
  // getmaxyx(stdscr, rows, cols);
  noecho();

  Controller controller(stdscr);
  controller.run();


  // std::string fileName = std::string(argv[1]);
  // printw("opening the file: ");
  // printw(fileName.c_str());

  // std::ifstream fileStream(fileName.c_str());
  // if (!fileStream.is_open())
  //   {
  //     printw(" failed");
  //     getch();
  //     endwin();
  //     return 0;
  //   }
  // clear();

  // std::vector<std::string> lines;
  // std::string line;
  // int counter = 0;
  // while (getline(fileStream, line))
  //   {
  //     lines.push_back(line);
  //     mvprintw(counter++, 0, line.c_str());
  //   }

  // int textOffset = 0;
  // int cursor = 0;
  // move(cursor, 0);
  
  // while (true)
  //   {
  //     int charCode = getch();
  //     switch (charCode)
  // 	{
  // 	case 'q':
  // 	  endwin();
  // 	  return 0;

  // 	case KEY_UP:
  // 	  if (cursor == 0)
  // 	    {
  // 	      if (textOffset > 0)
  // 		{
  // 		  textOffset--;
  // 		  clear();
  // 		  for (int i = 0; i < rows; i++)
  // 		    {
  // 		      mvprintw(i, 0, lines[i+textOffset].c_str());
  // 		    }
  // 		  move(cursor, 0);
  // 		}
  // 	    }
  // 	  else
  // 	    move(--cursor, 0);
  // 	  break;

  // 	case KEY_DOWN:
  // 	  if (cursor == rows - 1)
  // 	    {
  // 	      if (lines.size() - textOffset > rows)
  // 		{
  // 		  textOffset++;
  // 		  clear();
  // 		  for (int i = 0; i < rows; i++)
  // 		    {
  // 		      mvprintw(i, 0, lines[i+textOffset].c_str());
  // 		    }
  // 		  move(cursor, 0);
  // 		}
  // 	    }
  // 	  else
  // 	    {
  // 	      move(++cursor, 0);
  // 	    }
  // 	  break;

  // 	case PAGE_UP:
  // 	  textOffset = textOffset > rows ? textOffset - rows : 0;
  // 	  clear();
  // 	  for (int i = 0; i < rows; i++)
  // 	    {
  // 	      mvprintw(i, 0, lines[i+textOffset].c_str());
  // 	    }
  // 	  move(cursor, 0);
  // 	  break;

  // 	case PAGE_DOWN:
  // 	  {
  // 	    int maxOffset = lines.size() - rows;
  // 	    if (maxOffset < 0)
  // 	      break;
  // 	    textOffset = textOffset + rows < maxOffset ? textOffset + rows : maxOffset;
  // 	    clear();
  // 	    for (int i = 0; i < rows; i++)
  // 	      {
  // 		mvprintw(i, 0, lines[i+textOffset].c_str());
  // 	      }
  // 	    move(cursor, 0);
  // 	    break;
  // 	  }

  // 	case 'g':
  // 	  {
  // 	    char buff[255];
  // 	    echo();
  // 	    getstr(buff);
  // 	    noecho();
  // 	    std::string filter = std::string(buff);

  // 	    for (auto it = lines.begin(); it != lines.end();)
  // 	      if (it->find(filter) == std::string::npos)
  // 		it = lines.erase(it);
  // 	      else
  // 		it++;

  // 	    textOffset = 0;
  // 	    clear();
  // 	    for (int i = 0; i < rows and i+textOffset < lines.size(); i++)
  // 	      {
  // 		mvprintw(i, 0, lines[i+textOffset].c_str());
  // 	      }
  // 	    move(cursor, 0);
  // 	    break;
  // 	  }

  // 	default:
  // 	  printw("%d", charCode);
  // 	}
  //   }

  endwin();
}
