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
   float mass;
   int color;
};

struct Orb
{
   Vector position;
   float mass;
   int color;
};

Vector StartEntitySize = {6, 3};

Vector GetEntitySizes(const struct Entity *e)
{
   return Mul(StartEntitySize, (float)e->mass / 10); //6 3 * 2 = 12 6
}

Vector GetOrbSizes(const struct Orb *o)
{
   return Mul(StartEntitySize, (float)o->mass / 10);
}

struct Entity *new_entity(const char *name, int x, int y, int mass, int color)
{
   struct Entity *e = malloc(sizeof(struct Entity));

   e->name = name;
   e->position.x = x;
   e->position.y = y;
   e->mass = mass;
   e->color = color;

   return e;
}

struct Orb *new_orb(int x, int y, int mass, int color)
{
   struct Orb *orb = malloc(sizeof(struct Orb));

   orb->position.x = x;
   orb->position.y = y;
   orb->mass = mass;
   orb->color = color;

   return orb;
}

void print_player(Vector center, const struct Entity *e)
{
   Vector size = GetEntitySizes(e); 
   mvprintw(0,1,"Print Player x %f y %f  size %f size %f mass %f", e->position.x, e->position.y, size.x, size.y, e->mass);
   Vector position = {center.x - size.x / 2, center.y - size.y / 2};
   print_empty_rectangle(position, size.y, size.x, e->color);
}

void print_entities(Vector center, const struct Entity *player, struct leaf *entities)
{
   struct leaf *tmp = entities;

   while (tmp != NULL)
   {
      const struct Entity *e = tmp->data;
      Vector size = GetEntitySizes(e);
      // Vector diff 
      Vector diff = Sub(e->position, player->position);
      Vector position = Add(center, diff);
      print_empty_rectangle(position, size.y, size.x, e->color);
      tmp = tmp->next;
   }
}

void print_orbs(Vector center, const struct Entity *player, struct leaf *orbs)
{
   struct leaf *tmp = orbs;

   while (tmp != NULL)
   {
      const struct Orb *orb = tmp->data;
      Vector size = GetOrbSizes(orb);
      Vector diff = Sub(orb->position, player->position); 
      Vector position = Add(center, diff);
      print_empty_rectangle(position, size.y, size.x, orb->color);
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

bool check_orb_collision(const struct Entity *e, const struct Orb *orb)
{
   if (e == NULL || orb == NULL)
      return false;

   Vector entity_size = GetEntitySizes(e);
   Vector orb_size = GetOrbSizes(orb);
   Vector graphick_pos={e->position.x-entity_size.x/2,e->position.y-(int)(entity_size.y/2)};// 2.5 -> (int) -> 2 

   return check_collision(graphick_pos, entity_size, orb->position, orb_size);
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

void orb_collision(struct leaf **orbs, struct Entity *player)
{
   struct leaf *tmp = *orbs;
   struct leaf *prev = NULL;

   while (tmp != NULL)
   {
      struct Orb *orb = tmp->data;
      if (check_orb_collision(player, orb))
      {
         player->mass += orb->mass * 0.2; 
         *orbs = remove_leaf_ptr(*orbs, tmp);
         free(orb);
         break; 
      }
      prev = tmp;
      tmp = tmp->next;
   }
}

int get_random(int from, int to)
{
   return rand() % (to - from + 1) + from;
}

void get_entity(struct leaf **entities, struct Entity player, char *name)
{
   int x, y, mass, color;
   int count_tries = 0;

   struct Entity *new_en;
   bool collision = false;

   do
   {
      x = get_random(1, 100);
      y = get_random(1, 50);
      mass = get_random(10, 50);
      color = get_random(2, 4);

      new_en = new_entity(name, x, y, mass, color);
      count_tries++;
      
      mvprintw(0,1, "%d, %d, %d, %d", x, y, mass, color);
      refresh();

      if ((check_entity_collision(&player, new_en) == true) || (get_collision(*entities, new_en) != NULL))
         collision = true;

      if (collision)
         free(new_en);

      if (count_tries > 10)
         return;
   }
   while (collision);

   *entities = preappend_leaf(*entities, new_en);
}

void generate_orb(struct leaf **orbs)
{
   int x = get_random(1, 100);
   int y = get_random(1, 50);
   int mass = get_random(4, 12);
   int color = get_random(2, 4);

   struct Orb *new_orbb= new_orb(x, y, mass, color);
   *orbs = preappend_leaf(*orbs, new_orbb);
}

void move_entities(struct leaf *entities)
{
   struct leaf *tmp = entities;

   while (tmp != NULL)
   {
      struct Entity *entity = tmp->data;

      Vector direction = {get_random(-1, 1), get_random(-1, 1)};

      if (direction.x != 0 || direction.y != 0)
         Move(&entity->position, Normalize(direction), 1);

      tmp = tmp->next;
   }  
}

bool bigger_entity(struct Entity *e1, struct Entity *e2)
{
   /*if (e1->mass > e2->mass)
      return true;
   return false;*/
   return (e1->mass > e2->mass);
}

void eat_entity(struct Entity *bigger, struct Entity *smaller)
{
   bigger->mass += (smaller->mass * 0.3);
}

void handle_entities(struct leaf **entities)
{
   struct leaf *tmp = *entities;
   struct leaf *bumped; 

   while (tmp != NULL)
   {
      bumped = get_collision(*entities, tmp->data);

      if (bumped != NULL && bigger_entity(tmp->data, bumped->data))
      {
         eat_entity(tmp->data, bumped->data);
         *entities = remove_leaf_ptr(*entities, bumped);
      }
      tmp = tmp->next;
   } 
}


int main()
{
   srand(time(NULL));
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


   int count_entities = 0;
   int move_count = 0;
   struct leaf *entities = NULL;
   struct leaf *orbs = NULL;

   struct Entity player = {"Player", {5, 5}, 20, 1};

   mvprintw(0, 0, "hello");

   while (1)
   {
      int ch = getch();
      if (ch == 10) //enter 
      {
         char *buf = malloc(15);
         sprintf(buf, "Entity %d", count_entities++);
         //struct Entity *e = new_entity(buf, get_random(1, 100), get_random(1, 50),get_random(10, 50), get_random(2, 4));
         get_entity(&entities, player, buf);

         //entities = preappend_leaf(entities, e);
         //mvprintw(1, 0, "Generated Entity %d", count_entities);
      }
      else if (ch == 113) //q
      {
         if(player.mass > 1)
            player.mass--;
      }
      else if (ch == 101) //e
         player.mass++;
      else if (ch == 111) //o - create orb
         generate_orb(&orbs);

      handler(ch, &player.position);

      if (move_count++ % 4 == 0)
         move_entities(entities);

      handle_entities(&entities);
      orb_collision(&orbs, &player);

      mvprintw(0,0, "Player x %f y %f mass %f", player.position.x, player.position.y, player.mass);

      /*print_empty_rectangle(player.position, 1, 1, 1);*/
      print_player(get_center(), &player);
      print_entities(get_center(), &player, entities);
      print_orbs(get_center(), &player, orbs);

      refresh();
      erase();
      napms(40);
   }
   
   refresh();
   getch();
   endwin();
}
