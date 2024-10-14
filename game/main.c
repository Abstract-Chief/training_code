//file main_c was created by abstract at 17:43
 
<<<<<<< HEAD
#include <stdio.h>
#include "list.h"
 
int main(int argc, char **argv)
{
=======
#include<stdio.h>
#include"list.h"
 
int main(int argc, char **argv){
>>>>>>> 54e20aa (void array and multi entity system added)
   

   struct leaf* list = NULL, *last = NULL;
   const char *str= "Hello";
<<<<<<< HEAD
   list = last = append_leaf(list, str); // const char * -> void *
=======
   list = last =append_leaf(list, str);// const char * -> void *
>>>>>>> 54e20aa (void array and multi entity system added)

   printf("%s\n", (char*)list->data);

   return 0;
}
 
