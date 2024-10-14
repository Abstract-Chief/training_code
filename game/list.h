/*File "list.h" create by abstract, (2024-10-08)*/
#ifndef LIST_H_SENTURY
#define LIST_H_SENTURY

#include"vector.h"
 
struct leaf
{
   Vector start,actual,vec;
   struct leaf *prev, *next;
};

struct leaf *append_leaf(struct leaf* last,Vector pos,Vector dir);
struct leaf *preappend_leaf(struct leaf* head, Vector pos,Vector dir);
void print_list(struct leaf *head);
int get_distance(struct leaf *head, struct leaf *last,const struct leaf *tmp);
struct leaf *remove_leaf_ptr(struct leaf *head, struct leaf *finded);
 
#endif
