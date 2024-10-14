/*File "list.h" create by abstract, (2024-10-08)*/
#ifndef LIST_H_SENTURY
#define LIST_H_SENTURY

#include"vector.h"
 
#define LIST_H_VERSION "1.0.0"

struct leaf
{
   void *data;
   struct leaf *prev, *next;
};

struct leaf *append_leaf(struct leaf* last,void *data);
struct leaf *preappend_leaf(struct leaf* head, void *data);
void print_list(struct leaf *head);
int get_distance(struct leaf *head, struct leaf *last,const struct leaf *tmp);
struct leaf *remove_leaf_ptr(struct leaf *head, struct leaf *finded);
 
#endif
