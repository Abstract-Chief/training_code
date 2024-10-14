//file main_c was created by abstract at 17:43
 
#include<stdio.h>
#include"list.h"
 
int main(int argc, char **argv){
   

   struct leaf* list = NULL, *last = NULL;
   const char *str= "Hello";
   list = last =append_leaf(list, str);// const char * -> void *

   printf("%s\n", (char*)list->data);

   return 0;
}
 
