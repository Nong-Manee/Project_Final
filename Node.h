#include <iomanip>
using namespace std;

#ifndef NODE_H
#define NODE_H

class NODE{
protected:
    long memberId;
    static long memberIdCount;
    string name;
    NODE *next;
public:
    NODE();
    virtual void show_node();
    void insert(NODE*);
    NODE* move_next();
    virtual ~NODE();
    static long addMemberId();
};

long NODE::memberIdCount = 0;
NODE::NODE(){
    memberId=addMemberId();
    next=NULL;
}
long NODE::addMemberId(){
    return ++memberIdCount;
}
NODE:: ~NODE(){
    cout<<"Node "<<memberId<<" is being deleted"<<endl;
}

NODE *NODE::move_next(){
    return next;
}
void NODE:: show_node(){
    cout<<"Member ID : "<<setfill('0')<<setw(5)<<memberId<<endl;
 }
void NODE::insert(NODE* x){
    temp->next = x;
}

#endif 