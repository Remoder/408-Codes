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
    bool ltag, rtag;
    Linked_Binary_Tree *ls, *rs, *fa;

    /* used for functions about thread */
    Linked_Binary_Tree* in_order_thread_find_first_tree(); 
    Linked_Binary_Tree* in_order_thread_find_last_tree();
    Linked_Binary_Tree* in_order_thread_find_nxt_tree();
    Linked_Binary_Tree* in_order_thread_find_pre_tree();
    Linked_Binary_Tree* pre_order_thread_find_last_tree();
    Linked_Binary_Tree* pre_order_thread_find_nxt_tree();
    Linked_Binary_Tree* pre_order_thread_find_pre_tree();
    Linked_Binary_Tree* post_order_thread_find_first_tree();
    Linked_Binary_Tree* post_order_thread_find_nxt_tree();
    Linked_Binary_Tree* post_order_thread_find_pre_tree();
    void clear_thread(); // clear all thread
    void in_thread(); // used for function <create_in_thread>
    void pre_thread(); // used for function <create_pre_thread>
    void post_thread(); // used for function <create_post_thread>

    bool is_used_id(int); // if id has been used in this tree or not
    bool is_comflict(Linked_Binary_Tree*); // if the two trees comflict because of id or not

public:
    Node *rt;

    Linked_Binary_Tree(Node *_rt=NULL):
        rt(NULL), ls(NULL), rs(NULL), fa(NULL), ltag(0), rtag(0) {init(_rt);}

    ~Linked_Binary_Tree(){
        destroy();
    }

    void init(Node*);
    void destroy();
    void add(int, char, int, int); // add (id, val) as a [ch](l/r) son of (f)
    void add(int, char, Linked_Binary_Tree*); // add (other_tree) as a [ch](l/r) son of (f) 
    void display_tree();

    /* Functions about visit order recursively*/
    void recursive_pre_order();
    void recursive_in_order();
    void recursive_post_order();

    /* Functions about in-order thread */
    void create_in_thread(); // create in-order thread tree
    void thread_in_order();  // in-order visit by thread 
    void reverse_thread_in_order(); // reversed in-order visit by thread

    /* Functions about pre-order thread */
    void create_pre_thread(); // create pre-order thread tree
    void thread_pre_order(); // pre-order visit by thread
    void reverse_thread_pre_order(); // reversed pre-order visit by thread

    /* Functions about post-order thread */
    void create_post_thread(); // create post-order thread tree
    void thread_post_order(); // post-order visit by thread
    void reverse_thread_post_order(); // reversed post-order visit by thread
} ;

Linked_Binary_Tree* pre = NULL; // used for create thread

void Linked_Binary_Tree_test(){
    int a, b, c, n, x, s=0; char ch;
    Linked_Binary_Tree* t = new Linked_Binary_Tree();
    printf("Please enter the size of Tree: ");
    cin >> n;
    for (int i = 1; i <= n; i++){
        cout << "\nAdd [fa]'s [l/r] son (id, val), now enter [fa], [l/r], [id], [val]: ";
        cin >> a >> ch >> b >> c;
        t->add(a, ch, b, c);
    }
    while (n){
        printf("\n***************************\n| 0 | : Exit\n| 1 | : Build thread tree\n| 2 | : Visit by thread\n| 3 | : Visit recursively\n| 4 | : Display the tree\n***************************\n");
        cin >> n;
        switch (n){
            case 0:
                break;
            case 1:
                printf("\n***************************\n| 0 | : Exit\n| 1 | : Pre-Order\n| 2 | : In-Order\n| 3 | : Post-Order\n***************************\n");
                cin >> x;
                switch (x){
                    case 1: t->create_pre_thread(); s = 1; break; 
                    case 2: t->create_in_thread(); s = 2; break;
                    case 3: t->create_post_thread(); s = 3; break;
                    default: break;
                }
                break;
            case 2:
                if (!s){
                    printf("Thread should be built previously!");
                    break;
                } else {
                    printf("\n***************************\n| 0 | : Exit\n| 1 | : Ordered\n| 2 | : Reversed\n***************************\n");
                    cin >> x;
                    switch (x){
                        case 1: 
                            if (s == 1) {t->thread_pre_order(); break;}
                            if (s == 2) {t->thread_in_order(); break;}
                            if (s == 3) {t->thread_post_order(); break;}
                        case 2:
                            if (s == 1) {t->reverse_thread_pre_order(); break;}
                            if (s == 2) {t->reverse_thread_in_order(); break;}
                            if (s == 3) {t->reverse_thread_post_order(); break;}
                        default: break;
                    }
                }
                break;
            case 3:
                printf("\n***************************\n| 0 | : Exit\n| 1 | : Pre-Order\n| 2 | : In-Order\n| 3 | : Post-Order\n***************************\n");
                cin >> x;
                switch (x){
                    case 1: t->recursive_pre_order(); break;
                    case 2: t->recursive_in_order(); break;
                    case 3: t->recursive_post_order(); break;
                    default: break;
                }
                break;
            case 4:
                t->display_tree();
                break;
            default:
                printf("Unknown order!\n");
        }
    }
    return ;
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

bool Linked_Binary_Tree::is_comflict(Linked_Binary_Tree* other_tree){
    if (other_tree->is_used_id(rt->get_id()))
        return true;
    if (ls && ls->is_comflict(other_tree))
        return true;
    if (rs && rs->is_comflict(other_tree))
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
    if (!is_used_id(f)){
        if (!fa) // raise the message when there is no such a father id in the whole tree
            printf("No such a father node!\n");
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

void Linked_Binary_Tree::add(int f, char ch, Linked_Binary_Tree* other_tree){
    if (!f) {
        printf("No such a father node!\n");
        return ;
    }
    if (!is_used_id(f)){
        if (!fa) // raise the message when there is no such a father id in the whole tree
            printf("No such a father node!\n");
        return ;
    }
    if (is_comflict(other_tree)){
        printf("Repeated id exist!\n");
        return ;
    }
    if (rt->get_id() == f){
        if (ch == 'l' && !ls){
            ls = other_tree;
            other_tree->fa = this;
        }
        if (ch == 'r' && !rs){
            rs = other_tree;
            other_tree->fa = this;   
        }
    } else {
        if (ls) ls->add(f, ch, other_tree);
        if (rs) rs->add(f, ch, other_tree);
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

Linked_Binary_Tree* Linked_Binary_Tree::pre_order_thread_find_last_tree(){
    if (rs && !rtag) return rs->pre_order_thread_find_last_tree();
    if (ls && !ltag) return ls->pre_order_thread_find_last_tree();
    if (ltag && rtag) return this; 
}

Linked_Binary_Tree* Linked_Binary_Tree::pre_order_thread_find_nxt_tree(){
    if (ls && !ltag) return ls;
    if (rs) return rs;
}

Linked_Binary_Tree* Linked_Binary_Tree::pre_order_thread_find_pre_tree(){
    if (ltag) return ls;
    if (!fa) return NULL;
    if (fa->ls == this) return fa;
    if (fa->rs == this && fa->ltag) return fa;
    if (fa->rs == this && !fa->ltag) return fa->ls->pre_order_thread_find_last_tree();
}

Linked_Binary_Tree* Linked_Binary_Tree::post_order_thread_find_first_tree(){
    Linked_Binary_Tree* p = this;
    while (p->ls && !p->ltag)
        p = p->ls;
    return p;
}

Linked_Binary_Tree* Linked_Binary_Tree::post_order_thread_find_nxt_tree(){
    if (rtag) return rs;
    if (!fa) return NULL;
    if (fa->rs == this) return fa;
    if (fa->ls == this && fa->rtag) return fa;
    if (fa->ls == this && !fa->rtag) return fa->rs->post_order_thread_find_first_tree();
}

Linked_Binary_Tree* Linked_Binary_Tree::post_order_thread_find_pre_tree(){
    if (rs && !rtag) return rs;
    if (ls) return ls;
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

void Linked_Binary_Tree::reverse_thread_pre_order(){
    for (Linked_Binary_Tree* p = pre_order_thread_find_last_tree(); p; p = p->pre_order_thread_find_pre_tree())
        cout << p->rt->get_val() << ' ';
    cout << endl;
}

void Linked_Binary_Tree::post_thread(){
    if (ls && !ltag)
        ls->post_thread();
    if (rs && !rtag)
        rs->post_thread();
    if (!ls && !ltag){
        ls = pre;
        ltag = 1;
    }
    if (pre && !pre->rs && !pre->rtag){
        pre->rs = this;
        pre->rtag = 1;
    }
    pre = this;
}

void Linked_Binary_Tree::create_post_thread(){
    clear_thread();
    pre = NULL; // this is a global var
    post_thread();
}

void Linked_Binary_Tree::thread_post_order(){
    for (Linked_Binary_Tree* p = post_order_thread_find_first_tree(); p; p = p->post_order_thread_find_nxt_tree())
        cout << p->rt->get_val() << ' ';
    cout << endl;
}

void Linked_Binary_Tree::reverse_thread_post_order(){
    for (Linked_Binary_Tree* p = this; p; p = p->post_order_thread_find_pre_tree())
        cout << p->rt->get_val() << ' ';
    cout << endl;
}

void Linked_Binary_Tree::display_tree(){
    if (ls && !ltag)
        ls->display_tree();
    printf("[%d, %d]'s father is %d, while left_son is %d and right_son is %d.\n", rt ? rt->get_id() : 0, rt ? rt->get_val() : 0, fa ? fa->rt->get_id() : 0, ls ? ls->rt->get_id() : 0, rs ? rs->rt->get_id() : 0);
    if (rs && !rtag)
        rs->display_tree();
}

/*
A test data:
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