#include <iostream>
#include"Node.h"
using namespace std;

#ifndef LL_H
#define LL_H

class LL{
    NODE*hol;
    int size;
public:
     void add_node(NODE*&);
     void show_all();
     NODE* getHead() { return hol; }
  
     ~LL(); //de
     LL(); //con
    
};


LL::LL(){
       hol=NULL;
       size=0;
}

LL::~LL(){
     NODE *t;
     while (hol)
     {
          t = hol;
          hol = hol->move_next();
     }
     size = 0;
}

void LL::show_all(){
     NODE *t = hol;
     while(t != NULL)
     {
          t->show_node();
          t = t->move_next();
     }
}
void LL::add_node(NODE *&A){
     if (hol == NULL){
          hol = A;
     }
     else {
          NODE* t = hol;
          while (t->move_next() != NULL){
               t = t->move_next();
          }
          t->insert(A);
     }
     size++;
}

#endif 
