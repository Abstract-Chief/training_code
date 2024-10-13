/*File "vector.c" create by abstract, (2024-10-11)*/
#include"vector.h" 
#include<math.h>

Vector Add(Vector v1,Vector v2){
   Vector result={v1.x+v2.x,v1.y+v2.y};
   return result;
}
Vector Sub(Vector v1,Vector v2){
   Vector result={v1.x-v2.x,v1.y-v2.y};
   return result;
}
Vector Mul(Vector v1,float k){
   Vector result={v1.x*k,v1.y*k};
   return result;
}
Vector Normalize(Vector v){
   float module = Module(v);
   Vector result={v.x/module,v.y/module};
   return result;
}
void Move(Vector *v,Vector dir,float speed){
   v->x+=dir.x*speed;
   v->y+=dir.y*speed;
}

float Module(Vector v){
   return sqrt(v.x*v.x+v.y*v.y);
}

