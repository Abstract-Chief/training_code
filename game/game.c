#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "rectangles.h"
#include "vector.h"
#include "list.h"


void handler(int ch, Vector *v)
{
   if (v == NULL)
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

   Move(v, Normalize(direction), 1);
}

struct Entity
{
   const char *name;
   Vector position;
   int mass;
   int color;
};

Vector StartEntitySize = {6, 3};

Vector GetEntitySizes(const struct Entity *e)
{
   return Mul(StartEntitySize, (float)e->mass/10);//6 3 * 2 = 12 6
}

struct Entity *new_entity(const char *name,int x, int y,int mass, int color)
{
   struct Entity *e = malloc(sizeof(struct Entity));
   e->name=name;
   e->position.x = x;
   e->position.y = y;
   e->mass = mass;
   e->color = color;
   return e;
}

void print_entities(struct leaf *entities,const struct leaf *actual)
{
   struct leaf *tmp = entities;
   while (tmp != NULL)
   {
      const struct Entity *e = tmp->data;
      Vector size=GetEntitySizes(e);
      if (tmp == actual)
         print_empty_rectangle(e->position, size.y,size.x, 1);//Vector 
      else
         print_empty_rectangle(e->position, size.y,size.x, e->color);
      tmp = tmp->next;
   }
}

bool check_collision(Vector v1, Vector size1, Vector v2, Vector size2)
{
   /*mvprintw(1,0,"v1 %f %f size1 %f %f v2 %f %f size2 %f %f",v1.x,v1.y,size1.x,size1.y,v2.x,v2.y,size2.x,size2.y);*/
   /*mvprintw(2,0,"v1.x < v2.x + size2.x %d v2.x < v1.x + size1.x %d",v1.x < v2.x + size2.x,v2.x < v1.x + size1.x);*/
   /*mvprintw(3,0,"v1.y < v2.y + size2.y %d v2.y < v1.y + size1.y %d",v1.y < v2.y + size2.y,v2.y < v1.y + size1.y);*/
   if ((v1.x < v2.x + size2.x && v2.x < v1.x + size1.x) && (v1.y < v2.y + size2.y && v2.y < v1.y + size1.y))
      return true;
   return false;
}
bool check_entity_collision(const struct Entity *e1, const struct Entity *e2)
{
   if(e1 == e2)
      return false;
   if(e1 == NULL || e2 == NULL)
      return false;
   Vector size1 = GetEntitySizes(e1);
   Vector size2 = GetEntitySizes(e2);
   return check_collision(e1->position, size1, e2->position, size2);
}

struct leaf* get_collision(struct leaf *entities, const struct Entity *e)
{
   struct leaf *tmp = entities;
   while (tmp != NULL)
   {
      if (tmp->data != e)
      {
         if (check_entity_collision(e, tmp->data))
            return tmp;
      }
      tmp = tmp->next;
   }
   return NULL;
}


int main()
{
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

   while (1)
   {
      int ch = getch();
      if (ch == 10) //enter 
      {
         char *buf=malloc(15);
         sprintf(buf, "Entity %d", start_color);
         struct Entity *e = new_entity(buf,10, 10,10, start_color);
         start_color++;
         actual = entities = preappend_leaf(entities, e);
      }else if(ch == 113){
         struct Entity *e = actual->data;
         if(e->mass > 1)
            e->mass--;
      }else if(ch == 101){
         struct Entity *e = actual->data;
         e->mass++;
      }else if(ch == 32) // space - mark next entity as actual
      {
         if(actual->next == NULL)
            actual = entities;
         else
            actual = actual->next;
      }
      else if (ch == 103) // g - delete actual entity and go to next as actual
      {
         if (actual != NULL && (actual->next!=NULL || actual->prev!=NULL))
         {
            if (actual->next == NULL)
               actual = entities;
            else
               actual = actual->next;
            entities = remove_leaf_ptr(entities, actual->prev);
         }
      }

      if(actual != NULL)
      {
         struct Entity *e = actual->data;

         handler(ch, &e->position);
         struct leaf *collision = get_collision(entities, e);
         if(collision != NULL)
         {
            struct Entity *enemy = collision->data;
            mvprintw(1,0,"Collision %s %s",e->name,((struct Entity*)collision->data)->name);
            if(enemy->mass>e->mass){
               entities = remove_leaf_ptr(entities, actual);
               actual = entities;
            }else{
               entities = remove_leaf_ptr(entities, collision);
            }
         }
         mvprintw(0,0,"%s %f %f  %d",e->name,e->position.x, e->position.y, ch);
      }

      print_entities(entities, actual);
      refresh();
      clear();
      napms(50);
   }
   
   refresh();
   getch();
   endwin();
}
