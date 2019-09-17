//Minefield 2017/2018, Franciszek Mirecki
//komenda do kompilacji g++ -o ./minefield point.cpp main.cpp -lncurses -Wno-write-strings
#include "point.h"

using namespace std;

int main () {

  initscr(); //funkcja pozwalajaca na uzywanie biblioteki ncurses
  cbreak();
  int choice;
  while (choice)
  {
    menu();
    choice = read(0, 2);
    switch (choice) {
      case 1:
        newGame();
      break;

      case 2:
        credits();
      break;
    }
  }
  endwin();
  return 0;
}
