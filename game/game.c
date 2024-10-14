#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "triangles.h"
#include "vector.h"
#include"list.h"


void handler(int ch, Vector *v)
{
   if(v==NULL)
      return;
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


struct Entity{
   Vector position;
   int color;
};
struct Entity *new_entity(int x,int y,int color){
   struct Entity *e = malloc(sizeof(struct Entity));
   e->position.x=x;
   e->position.y=y;
   e->color = color;
   return e;
}
void print_entities(struct leaf *entities,struct leaf *actual){
   struct leaf *tmp = entities;
   while(tmp!=NULL){
      const struct Entity *e = tmp->data;
      if(tmp==actual)
         print_empty_triangle(e->position, 5, 12, 1);
      else
         print_empty_triangle(e->position, 5, 12, e->color);
      tmp = tmp->next;
   }
}
bool check_collision(Vector v1,Vector size1,Vector v2,Vector size2){
   
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


   int start_color = 2;
   struct leaf *entities = NULL;

   struct leaf *actual = NULL;

   // если нажата клавища g - удалить актуальный элемент 103 remove_leaf_ptr
   // 
   while (1)
   {
      int ch = getch();
      if (ch == 10)//enter
      {
         struct Entity *e = new_entity(10,10,start_color);
         start_color++;
         actual=entities = preappend_leaf(entities,e);
      }else if(ch==32){//space 
         if(actual->next==NULL)
            actual=entities;
         else
            actual=actual->next;
      }
      if(actual!=NULL){
         struct Entity *e = actual->data;
         handler(ch, &e->position);
         mvprintw(0,0,"%f %f  %d",e->position.x,e->position.y,ch);
      }

      print_entities(entities,actual);
      refresh();
      clear();
      napms(100);
   }
   
   refresh();

   getch();

   endwin();
}
