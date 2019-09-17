//Minefield 2017/2018, Franciszek Mirecki
#include "point.h"

using namespace std;

int size = 40; //plansza wraz z ramka jest 40x40
int mnum; //liczba min, stwierdzilem ze bedzie zmienna globalna poniewaz chcialbym aby rowniez byla zapisywana do pliku
bool **board, **mines, game;

//point
Point::Point() {
  x = 1;
  y = 1;
  moves = 0;
}

Point::~Point() {}

int Point::getX() {return x;}

int Point::getY() {return y;}

void Point::showPos() {
  printw("Saper -\tx:%d\ty:%d\n", x, y);
}

void Point::keyPressed(char ch) {
  if (ch == '0' || ch == 'x') {
    game = false;
  }
  if(ch == 'w' && y < size-2) {
    y++;
  } else if (ch == 's' && y > 1) {
    y--;
  } else if (ch == 'a' && x > 1) {
    x--;
  } else if (ch == 'd' && x < size-2) {
    x++;
  }
  moves++;
}

bool Point::probe() {
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if(mines[x+i][y+j]) return true;
    }
  }
  return false;
}

void Point::isGameOver() {
  if(x == size-2 && y == size-2) {
    clear();
    fstream file;
    int save;
    char name[16];
    while(save) {
      printw("BRAWO! Wygrales zycie. Udalo Ci sie to w %d ruchow!\n", moves);
      printw("Czy chcesz zapisac swoj wynik do pliku?\n1. Tak\n0. Nie\n");
      save = read(0, 1);
      switch(save) {
        case 1:
          printw("\nProsze podac swoj nick: ");
          scanw("%s", &name);
          file.open("wyniki.txt");
          file.seekg(0, ios::end); // ustawia kursor na koncu pliku
          if (file.good()) {
            file << "\nGratulacje! Gracz " << name << " przeszedl Minefield w " << moves << " ruchach!\nMin na polu bylo " << mnum << "." << endl << endl;
            printw("\nSaved");
            getch();
        	} else {
            printw("\nPermission denied! Saving failed.");
            getch();
        	}
        break;

        default:
          printw("\nNie ma takiej opcji");
      }
      game = false;
      break;
    }
  } else if(mines[x][y]) {
    clear();
    printw("Przegrana! Jestes slaby, zagraj jeszcze raz!\n\nAby powrocic do menu wcisnij ENTER...\n");
    scanw("%d", &game);
    game = false;
  }

}

/*bool Saper::isOnBoard() {
  if (x < size-1 && x > 0 && y < size-1 && y > 0c) return true;
  return false;
}
*///miala byc fajna funkcja ale niestety nie dziala, zostawiam sobie na pozniej

//misc
void menu() {
  clear();
  printw("\nWitaj w grze...\n   ~~~MINEFIELD!~~~\n");
  printw("\tMenu:\n");
  printw("\t 1. Nowa gra\n");
  printw("\t 2. Info\n");
  printw("\t 0. exit\n");
  refresh();
}

int read(int dLim, int uLim) {
  int num;
  printw("Podaj wartosc z przedzialu [%d - %d]: ", dLim, uLim);
  scanw("%d", &num);
  while (num < dLim || num > uLim) {
    printw("\nZLE! Wartosc spoza przedzialu.\n");
    printw("Podaj jeszcze raz wartosc z przedzialu [%d - %d]: ", dLim, uLim);
	scanw("%d", &num);
  }
  return num;
}

//kejs 1
//template <typename T>
bool** make2DArray(int s) {
  bool **tab = new bool*[s];
  for (int i = 0; i < s; i++) {
    tab[i] = new bool[s];
  }
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      tab[i][j] = 0;
    }
  }
  return tab;
}

void info() {
  printw("Sterowanie:\tW - gora,\tS - dol,\tA - lewo,\tD - prawo;\n");
  printw("Aby zakonczyc gre nacisnij 0 lub x...\n");
  refresh();
}

void showMinesInfo(int i, int mx, int my) {
  printw("Mina nr %d, x: %d y: %d\n", i+1, mx, my);
}

void randMines() {
  srand(time(NULL));
  int tmpx, tmpy, u = size-2, d = 1;
  clear();
  printw("Rozpoczynamy nowa gre...\nIle ma byc min?\n");
  mnum = read(1, 314); //przewaznie da sie jeszcze przejsc gre przy tylu minach
  int i = 0;
  do {
    tmpx = (rand() % (u - d)) + d;
    tmpy = (rand() % (u - d)) + d;
    if (!mines[tmpx][tmpy] && (tmpx + tmpy) != 2*(size - 2) && (tmpx + tmpy) != 2) { //wiem, dziwne warunki ale moge sie z nich wytlumaczyc!
      mines[tmpx][tmpy] = true;
      showMinesInfo(i, tmpx, tmpy); // tutaj zakomentowac zeby nie wyswietlaly sie informacje o polozeniu min
      i++;
    } else i--;
  } while (i < mnum);
  printw("\nAby rozpoczac gre wcisnij jakikolwiek klawisz...");
  getch();
  refresh();
}

void newGame() {
  game = true;
  Point saper;
  board = make2DArray(size);
  mines = make2DArray(size);
  randMines();
  char ch;
  while(game) {
    drawBoard(saper);
    info();
    saper.showPos();
    if(saper.probe()) printw("Uwaga miny!\n");
    else printw("Brak min.\n");
    ch = getch();
    saper.keyPressed(ch);
    saper.isGameOver();
  }
  delete(board);
  delete(mines);
}

void drawBoard(Point s) {
  board[s.getX()][s.getY()] = true;
  clear();
  for (int j = size-1; j > -1; j--) {
    for (int i = 0; i < size; i++) {
      if(j == 0 || j == size-1) {
        printw("-");
      } else if(i == 0 || i == size-1) {
          printw("|");
      } else if(i == s.getX() && j == s.getY()) {
          printw("o");
      } else if(i == size-2 && j == size-2) {
          printw("M"); // meta
      } else if(i == 1 && j == 1) {
          printw("S"); // start
      } else if(board[i][j]) {
          printw("#");
      // /* tutaj odkomentowac zeby nie bylo widac min
      } else if(mines[i][j]) {
          printw("*");
      // */ //i tutaj odkomentowac zeby nie bylo widac min
      } else {
          printw(" ");
      }
    }
    printw("\n");
  }
  refresh();
}

//kejs 2
void credits() {
  clear();
  printw("\n|~MINEFIELD~|\n");
  printw("Gra napisana przez: Franciszka Mireckiego\n");
  printw("Projekt z Jezykow Programowania 2017/2018\n");
  printw("\nAby powrocic do menu wcisnij jakikolwiek klawisz...");
  getch();
  refresh();
}
