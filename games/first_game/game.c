#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "list.h"
#include "enemy.h"
#include "vector.h"


void print_hero(Vector p)
{
   attron(COLOR_PAIR(1));
   mvprintw(p.y - 1, p.x + 1, "X");
   mvprintw(p.y, p.x,"XXX");
   mvprintw(p.y + 1, p.x + 1, "X");
   attroff(COLOR_PAIR(1));
}

void handler(int ch, Vector *v)
{
   /*bool flag_action=false;*/
   if(ch == KEY_UP)
   {
      v->y--;
      /*flag_action=true;*/
   }
   else if(ch == KEY_DOWN)
   {
      v->y++;
      /*flag_action=true;*/
   }
   else if(ch == KEY_LEFT)
   {
      v->x--;
      /*flag_action=true;*/
   }
   else if(ch == KEY_RIGHT)
   {
      v->x++;
      /*flag_action=true;*/
   }
}

void print_bullet(Vector v)
{
   attron(COLOR_PAIR(2));
   mvprintw(v.y, v.x, "*");
   attroff(COLOR_PAIR(2));
}

void print_bullet_list(struct leaf *head)
{
   struct leaf *tmp = head;

   while(tmp != NULL)
   {
      print_bullet(tmp->actual);
      tmp = tmp->next;
   }
}

void move_bullets(struct leaf **head)
{
   struct leaf *tmp = *head;

   while(tmp != NULL)
   {
      Move(&tmp->actual,tmp->vec,1);//v 
      
      if (Module(Sub(tmp->actual,tmp->start))>50){
         *head=remove_leaf_ptr(*head,tmp);
         mvprintw(2,0,"head = %ld",*head);
      
      }
      else
         tmp = tmp->next;
   }
}


int main()
{
   // на след занятии сделать наводку 

   initscr();
   start_color();
   curs_set(0);
   noecho(); //не отображать вводимые символы
   nodelay(stdscr, true); //не блокировать ввод
   keypad(stdscr, 1); //использовать функциональные клавиши

   init_pair(1, COLOR_RED, COLOR_RED);
   init_pair(2, COLOR_GREEN, COLOR_GREEN);
   init_pair(3, COLOR_BLUE, COLOR_BLUE);
   //COLOR_BLUE

   Vector hero = {10, 10};
   struct leaf *bullets = NULL;
   /*struct enemy *enemies = NULL;*/

   // enemy inicialization
   /*enemies = add_enemy(enemies, 20, 30);*/
   /*enemies = add_enemy(enemies, 30, 15);*/

   while(1)
   {
      int ch = getch();
      handler(ch, &hero);

      if(ch == 10){
         Vector vec = {0.7,0.7};
         bullets = preappend_leaf(bullets,hero,vec);
      }

      clear();
      mvprintw(0,0,"x = %f y = %f ch = %d", hero.x, hero.y, ch);
      if (bullets!=NULL)
         mvprintw(1,0,"bullet %f %f  ", bullets->actual.x, bullets->actual.y);
      print_hero(hero);
      print_bullet_list(bullets);
      /*print_enemy_list(enemies);*/

      refresh();
      move_bullets(&bullets);

      napms(100);
   }

   refresh();

   getch();
   endwin();
}
