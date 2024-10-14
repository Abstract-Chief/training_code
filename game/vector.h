/*File "vector.h" create by abstract, (2024-10-11)*/ 
#ifndef VECTOR_H_SENTURY
#define VECTOR_H_SENTURY

typedef struct{
   float x,y;
} Vector;

Vector Add(Vector v1,Vector v2);
Vector Sub(Vector v1,Vector v2);
Vector Mul(Vector v1,float k);

Vector Normalize(Vector v);

void Move(Vector *v,Vector dir,float speed);

float Module(Vector v);

 
#endif
