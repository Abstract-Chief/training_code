/*File "enemy.c" create by abstract, (2024-10-11)*/
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "enemy.h"
#include "list.h"

void print_enemy(int x, int y)
{
   attron(COLOR_PAIR(3));
   mvprintw(y - 1, x + 1, "%%");
   mvprintw(y, x, "%%%%%%");
   mvprintw(y + 1, x + 1, "%%");
   attroff(COLOR_PAIR(3));
}

struct enemy* add_enemy(struct enemy *head, int x, int y)
{
  struct enemy *new_enemy = malloc(sizeof(struct enemy));
  new_enemy->x = x;
  new_enemy->y = y;

  new_enemy->next = head;
  return new_enemy;
}

struct enemy *move_enemies(struct enemy *head, int hero_x, int hero_y, int tick)
{
  struct enemy *tmp = head;

  if (tick % 5 == 0)
  {
    while (tmp != NULL)
    {
      if (tmp->x < hero_x)
        tmp->x++;
      if (tmp->x > hero_x)
        tmp->x--;
      if (tmp->y < hero_y)
        tmp->y++;
      if (tmp->y > hero_y)
        tmp->y--;
      tmp = tmp->next;
    }
  }
  return NULL;
}

void print_enemy_list(struct enemy *head)
{
  struct enemy *tmp = head;

  while(tmp != NULL)
  {
    print_enemy(tmp->x,tmp->y);
    tmp = tmp->next;
  }
}
