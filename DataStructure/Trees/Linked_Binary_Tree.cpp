#include <iostream>
using namespace std;

class Node{
private:
    int val, id;
public:
    Node(int _id=0, int _val=0):
        val(_val), id(_id){}
    int get_val()
        {return val;}
    void set_val(int _val)
        {val = _val;}
    int get_id()
        {return id;}
    void set_id(int _id)
        {id = _id;}
} ;

class Linked_Binary_Tree{
private:
    Node *rt;
    Linked_Binary_Tree *ls, *rs, *fa;
public:
    Linked_Binary_Tree(Node *_rt=NULL):
        rt(NULL), ls(NULL), rs(NULL), fa(NULL) {init(_rt);}

    ~Linked_Binary_Tree(){
        destroy();        
    }

    void init(Node*);
    void destroy();
    bool is_used_id(int);
    void add(int, char, int, int);
    void pre_order();
    void in_order();
    void post_order();
} ;

void Linked_Binary_Tree_test(){
    int a, b, c; char ch;
    Linked_Binary_Tree* t = new Linked_Binary_Tree();
    while (cin >> a >> ch >> b >> c){
        t->add(a, ch, b, c);
    }
    t->pre_order(); cout << endl;
    t->in_order(); cout << endl;
    t->post_order(); cout << endl;
    return ;
}

int main(){
    Linked_Binary_Tree_test();
    return 0;
}

void Linked_Binary_Tree::init(Node *_rt){
    if (_rt) rt = _rt;
    else rt = new Node;
}

void Linked_Binary_Tree::destroy(){
    if (ls)
        ls->destroy();
    if (rs)
        rs->destroy();
    delete rt;
}

bool Linked_Binary_Tree::is_used_id(int id){
    if (rt->get_id() == id)
        return true;
    if (ls && ls->is_used_id(id))
        return true;
    if (rs && rs->is_used_id(id))
        return true;
    return false;
}

void Linked_Binary_Tree::add(int f, char ch, int id, int val){
    Linked_Binary_Tree *p = new Linked_Binary_Tree;
    p->rt->set_val(val); p->rt->set_id(id);
    if (is_used_id(id)){
        printf("The id has been used!\n");
        return ;
    }
    if (rt->get_id() == f){ // find father node.
        if (ch == 'l' && !ls) 
            ls = p;
        if (ch == 'r' && !rs) 
            rs = p;
    } else {
        if (ls) ls->add(f, ch, id, val);
        if (rs) rs->add(f, ch, id, val);
    }
}

void Linked_Binary_Tree::pre_order(){
    if (rt->get_id())
        printf("%d ", rt->get_val());
    if (ls) ls->pre_order();
    if (rs) rs->pre_order();
}

void Linked_Binary_Tree::in_order(){
    if (ls) ls->in_order();
    if (rt->get_id())
        printf("%d ", rt->get_val());
    if (rs) rs->in_order();
}

void Linked_Binary_Tree::post_order(){
    if (ls) ls->post_order();
    if (rs) rs->post_order();
    if (rt->get_id())
        printf("%d ", rt->get_val());
}

