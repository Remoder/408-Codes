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
    Node *rt; bool ltag, rtag;
    Linked_Binary_Tree *ls, *rs, *fa;

    /* used for functions about thread */
    Linked_Binary_Tree* in_order_thread_find_first_tree(); 
    Linked_Binary_Tree* in_order_thread_find_last_tree();
    Linked_Binary_Tree* in_order_thread_find_nxt_tree();
    Linked_Binary_Tree* in_order_thread_find_pre_tree();
    Linked_Binary_Tree* pre_order_thread_find_nxt_tree();
    void clear_thread();
    void in_thread(); // used for function <create_in_thread>
    void pre_thread(); // used for function <create_pre_thread>
    void post_thread(); // used for function <create_post_thread>
    bool is_used_id(int);

public:
    Linked_Binary_Tree(Node *_rt=NULL):
        rt(NULL), ls(NULL), rs(NULL), fa(NULL), ltag(0), rtag(0) {init(_rt);}

    ~Linked_Binary_Tree(){
        destroy();        
    }

    void init(Node*);
    void destroy();
    void add(int, char, int, int); // add (id, val) as a [ch](l/r) son of (f)
    void recursive_pre_order();
    void recursive_in_order();
    void recursive_post_order();
    void create_in_thread(); // create in-order thread 
    void thread_in_order();  // in-order visit by thread
    void reverse_thread_in_order(); // reversed in-order visit by thread
    void create_pre_thread(); // create pre-order thread
    void thread_pre_order(); // pre-order visit by thread
    void reverse_thread_pre_order(); // reversed pre-order visit by thread
    void display_tree();
} ;

Linked_Binary_Tree* pre = NULL; // used for create thread

void Linked_Binary_Tree_test(){
    int a, b, c; char ch;
    Linked_Binary_Tree* t = new Linked_Binary_Tree();
    while (cin >> a >> ch >> b >> c){
        t->add(a, ch, b, c);
    }
    // Tree Check
    t->recursive_pre_order(); cout << endl;
    // t->recursive_in_order(); cout << endl;
    // t->recursive_post_order(); cout << endl;

    // In-order Tread Check
    // t->create_in_thread();
    // t->display_tree();
    // t->thread_in_order();

    // Pre-order Tread Check
    t->create_pre_thread();
    // t->display_tree();
    t->thread_pre_order();
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
    if (!f){
        rt->set_id(id);
        rt->set_val(val);
        return ;
    }
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
        p->fa = this;
    } else {
        if (ls) ls->add(f, ch, id, val);
        if (rs) rs->add(f, ch, id, val);
    }
}

void Linked_Binary_Tree::recursive_pre_order(){
    if (rt->get_id())
        printf("%d ", rt->get_val());
    if (ls) ls->recursive_pre_order();
    if (rs) rs->recursive_pre_order();
}

void Linked_Binary_Tree::recursive_in_order(){
    if (ls) ls->recursive_in_order();
    if (rt->get_id())
        printf("%d ", rt->get_val());
    if (rs) rs->recursive_in_order();
}

void Linked_Binary_Tree::recursive_post_order(){
    if (ls) ls->recursive_post_order();
    if (rs) rs->recursive_post_order();
    if (rt->get_id())
        printf("%d ", rt->get_val());
}

Linked_Binary_Tree* Linked_Binary_Tree::in_order_thread_find_first_tree(){
    Linked_Binary_Tree* p = this;
    while (p->ls && !p->ltag)
        p = p->ls;
    return p;
}

Linked_Binary_Tree* Linked_Binary_Tree::in_order_thread_find_last_tree(){
    Linked_Binary_Tree* p = this;
    while (p->rs && !p->rtag)
        p = p->rs;
    return p;
}

Linked_Binary_Tree* Linked_Binary_Tree::in_order_thread_find_nxt_tree(){
    if (rtag) return rs;
    return rs->in_order_thread_find_first_tree();
}

Linked_Binary_Tree* Linked_Binary_Tree::in_order_thread_find_pre_tree(){
    if (ltag) return ls;
    return ls->in_order_thread_find_last_tree();
}

Linked_Binary_Tree* Linked_Binary_Tree::pre_order_thread_find_nxt_tree(){
    if (ls && !ltag) return ls;
    if (rs) return rs;
}

void Linked_Binary_Tree::clear_thread(){
    if (ltag) ltag = 0, ls = NULL;
    if (rtag) rtag = 0, rs = NULL;
    if (ls) ls->clear_thread();
    if (rs) rs->clear_thread();
}

void Linked_Binary_Tree::in_thread(){
    if (ls && !ltag)
        ls->in_thread();
    if (!ls && !ltag){
        ls = pre;
        ltag = 1;
    }
    if (pre && !pre->rs && !pre->rtag){
        pre->rs = this;
        pre->rtag = 1;
    }
    pre = this;
    if (rs && !rtag)
        rs->in_thread();
}

void Linked_Binary_Tree::create_in_thread(){
    clear_thread(); 
    pre = NULL; // this is a global var
    in_thread(); 
    if (pre){
        pre->rs = NULL;
        pre->rtag = 1;
    }
}

void Linked_Binary_Tree::thread_in_order(){
    for (Linked_Binary_Tree* p = in_order_thread_find_first_tree(); p; p = p->in_order_thread_find_nxt_tree())
        cout << p->rt->get_val() << ' ';
    cout << endl;
}

void Linked_Binary_Tree::reverse_thread_in_order(){
    for (Linked_Binary_Tree* p = in_order_thread_find_last_tree(); p; p = p->in_order_thread_find_pre_tree())
        cout << p->rt->get_val() << ' ';
    cout << endl;
}

void Linked_Binary_Tree::pre_thread(){
    if (!ls && !ltag){
        ls = pre;
        ltag = 1;
    }
    if (pre && !pre->rs && !pre->rtag){
        pre->rs = this;
        pre->rtag = 1;
    }
    pre = this;
    if (ls && !ltag)
        ls->pre_thread();
    if (rs && !rtag)
        rs->pre_thread();
}

void Linked_Binary_Tree::create_pre_thread(){
    clear_thread();
    pre = NULL; // this is a global var
    pre_thread();
    if (pre){
        pre->rs = NULL;
        pre->rtag = 1;
    }
}

void Linked_Binary_Tree::thread_pre_order(){
    for (Linked_Binary_Tree* p = this; p; p = p->pre_order_thread_find_nxt_tree())
        cout << p->rt->get_val() << ' ';
    cout << endl;
}

void Linked_Binary_Tree::display_tree(){
    if (ls && !ltag)
        ls->display_tree();
    printf("[%d]'s father is %d, while left_son is %d and right_son is %d.\n", rt ? rt->get_id() : 0, fa ? fa->rt->get_id() : 0, ls ? ls->rt->get_id() : 0, rs ? rs->rt->get_id() : 0);
    if (rs && !rtag)
        rs->display_tree();
}

/*
0 l 1 1
1 l 2 2
1 r 3 3
2 l 4 4
4 r 7 7
3 l 5 5
3 r 6 6
7 l 9 9 
4 l 10 10
*/