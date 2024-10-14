#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "triangles.h"
#include "vector.h"


void handler(int ch, Vector *v)
{
   Vector direction = {0,0};

   if(ch == KEY_UP)
      direction.y = -1;
   else if(ch == KEY_DOWN)
      direction.y = 1;
   else if(ch == KEY_LEFT)
      direction.x = -1;
   else if(ch == KEY_RIGHT)
      direction.x = 1;

   Move(v, Normalize(direction), 2);
}


int main()
{
   // на след занятии сделать наводку 

   initscr(); // включить нкурсес
   start_color(); // инициализировать цвета
   curs_set(0); // добавить / убрать курсор (1/0)
   noecho(); //не отображать вводимые символы
   nodelay(stdscr, true); //не блокировать ввод
   keypad(stdscr, 1); //использовать функциональные клавиши

   init_pair(1, COLOR_RED, COLOR_RED);
   init_pair(2, COLOR_GREEN, COLOR_GREEN);
   init_pair(3, COLOR_BLUE, COLOR_BLUE);
   init_pair(4, COLOR_YELLOW, COLOR_BLUE);

   Vector p1 = {10,10};
   Vector p2 = {30,30};
   Vector *actual = &p1;

   while (1)
   {
      int ch = getch();
      if (ch == 10)
      {
         if (actual == &p1)
            actual = &p2;
         else
            actual = &p1;
      }

      handler(ch, actual);
      clear();
      mvprintw(0,0, "%f %f", p1.x, p1.y);

      print_empty_triangle(p1, 5, 12, 4);
      print_empty_triangle(p2, 5, 12, 2);
      refresh();
      napms(100);
   }
   
   refresh();

   getch();

   endwin();
}
