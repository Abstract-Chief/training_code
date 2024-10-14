/*File "list.c" create by abstract, (2024-10-08)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include"list.h"
#include "vector.h"



struct leaf *append_leaf(struct leaf* last,void *data)
{
   if(last == NULL)
   {
      last = malloc(sizeof(struct leaf));
      last->data=data;
      last->next = NULL;
      return last;
   }

   struct leaf *new_leaf = malloc(sizeof(struct leaf));
   new_leaf->data = data;

   new_leaf->next = NULL;
   last->next = new_leaf;
   new_leaf->prev = last;
   return new_leaf;
}

struct leaf *preappend_leaf(struct leaf* head, void *data)
{
   if(head == NULL)
   {
      head = malloc(sizeof(struct leaf));
      head->data=data;
      head->next = NULL; head->prev = NULL;
      return head;
   }

   struct leaf* new_head = malloc(sizeof(struct leaf));
   new_head->data = data;
   new_head->next = head;new_head->prev = NULL;
   head->prev = new_head;
   return new_head;
}
int get_distance(struct leaf *head, struct leaf *last,const struct leaf *tmp)
{
	
	int count_ahead = 0, back_count = 0;
	for (struct leaf *ahead = head; ahead != NULL; ahead = ahead->next)
	{
		if (ahead == tmp)
			return count_ahead;
		count_ahead++;
	}

	for (struct leaf *back = last; back != NULL; back = back->prev)
	{
		if (back == tmp)
			return back_count;
		back_count++;
	}
	return -1;
}
struct leaf* remove_leaf_ptr(struct leaf *head, struct leaf *finded)
{
	if (finded == NULL)
		return head;

	if (finded == head)
	{
      if (finded->next == NULL)
      {
         free(finded);
         return NULL;
      }
		head = finded->next;
      free(finded);
      head->prev = NULL;
      return head;
	}	
   struct leaf *tmp = head;
   while(tmp!=NULL)
   {
      if (tmp->next == finded)
      {
         tmp->next = finded->next;
         if (finded->next != NULL)
            finded->next->prev = tmp;
         break;
      }
      tmp = tmp->next;
   }
	free(finded);
   return head;
}

