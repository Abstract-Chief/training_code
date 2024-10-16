#include <stdio.h>
#include <ncurses.h>

#include "vector.h"
#include "rectangles.h"

void print_rectangle_ws(Vector pos, int height, int width, char symbol, int color)
{  
   attron(COLOR_PAIR(color));

   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
		mvprintw(pos.y + i, pos.x + j, "%c", symbol);
      }
   }
   attroff(COLOR_PAIR(color));
}

void print_empty_rectangle(Vector pos, int height, int width, int color)
{
	attron(COLOR_PAIR(color));

	for (int i = 0; i < height; i++)
   {
      mvprintw(pos.y + i, pos.x, "%c", '+');
      mvprintw(pos.y + i, pos.x + width, "%c", '+');
   }
   
   for (int i = 0; i < width + 1; i++)
   {
      mvprintw(pos.y, pos.x + i, "%c", '+');
      mvprintw(pos.y + height, pos.x + i, "%c", '+');
   }
      
   
   attroff(COLOR_PAIR(color));
}
