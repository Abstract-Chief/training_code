/*File "enemy.h" create by abstract, (2024-10-11)*/
 
#ifndef ENEMY_H_SENTURY
#define ENEMY_H_SENTURY
 
struct enemy
{
  int x;
  int y;
  struct enemy *next;
};

void print_enemy(int x, int y);
struct enemy* add_enemy(struct enemy *head, int x, int y);
struct enemy *move_enemies(struct enemy *head, int hero_x, int hero_y, int tick);
void print_enemy_list(struct enemy *head);
#endif
