#include <ncurses.h>


//zmienne
int kolumny = 0;
int rzedy = 0;
char tekst[] = "Wyswietlany tekst!";


int main()
{
  //start    
  initscr();
    
  //Pobieranie wartości okna do zmiennych
  getmaxyx( stdscr, rzedy, kolumny ); //1
    
    
  //wyswietlanie tekstu
  mvprintw( rzedy / 2,( kolumny / 2 ) -( sizeof( tekst ) / 2 ), tekst ); //2
  getch();
  endwin();
}
