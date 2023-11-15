#include <iostream>
using namespace std;

class Node{
private:
    int val;
    bool used;
public:
    Node(int _val=0):
        val(_val), used(0){}
    int get_val()
        {return val;}
    void set_val(int _val)
        {val = _val; used = 1;}
} ;

class Sequence_Tree{
private:
    Node *t;
    int mem;
public:
    Sequence_Tree(int _mem){
        init(_mem);
    }

    ~Sequence_Tree(){
        delete[] t;
    }

    void init(int);
    void add(int, int);
    
} ;

void Sequence_Tree::init(int _mem){
    mem = (1<<_mem);
    t = new Node(mem);
}






