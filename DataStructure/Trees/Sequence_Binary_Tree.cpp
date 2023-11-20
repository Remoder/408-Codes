#include <iostream>
using namespace std;

class Node{
private:
    int val; int id;
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

class Sequence_Binary_Tree{
private:
    Node *t;
    int mem;
public:
    Sequence_Binary_Tree(int _mem=10){
        init(_mem);
    }

    ~Sequence_Binary_Tree(){
        delete[] t;
    }

    void init(int);
    bool is_valid_idx(int);
    int get_idx_of_id(int, int);
    void destroy(int);
    void add(int, char, int, int);
    void pre_order(int);
    void in_order(int);
    void post_order(int);
} ;

void Sequence_Binary_Tree_test(){
    int a, b, c; char ch;
    Sequence_Binary_Tree *t = new Sequence_Binary_Tree();
    while (cin >> a >> ch >> b >> c){
        t->add(a, ch, b, c);
    }
    cout << t->is_valid_idx(3) << endl;
    // t->pre_order(1); cout << endl;
    // t->in_order(1); cout << endl;
    // t->post_order(1); cout << endl;
    return ;
}

int main(){
    Sequence_Binary_Tree_test();
    return 0;
}

void Sequence_Binary_Tree::init(int _mem){
    mem = (1<<_mem);
    t = new Node(mem+1);
}

bool Sequence_Binary_Tree::is_valid_idx(int idx){
    cout << idx << ' ' << t[idx].get_id() << endl;
    return idx <= mem && t[idx].get_id();
}

int Sequence_Binary_Tree::get_idx_of_id(int idx, int goal_id){
    int res = 0;
    if (goal_id == 0)
        return 0;
    if (t[idx].get_id() == goal_id)
        res = idx;
    else {
        if (!res && is_valid_idx(idx*2))
            res = get_idx_of_id(idx*2, goal_id);
        if (!res && is_valid_idx(idx*2+1))
            res = get_idx_of_id(idx*2+1, goal_id);
    }
    return res;
}

void Sequence_Binary_Tree::destroy(int id){
    int idx = get_idx_of_id(1, id);
    if (is_valid_idx(idx*2))
        destroy(id*2);
    if (is_valid_idx(idx*2+1))
        destroy(id*2+1);
    t[id].set_id(0);
}

void Sequence_Binary_Tree::add(int f, char ch, int id, int val){
    int idx = get_idx_of_id(1, f);
    int goal_idx = (ch == 'r' ? idx*2 : idx*2+1);
    if (is_valid_idx(goal_idx)){
        t[goal_idx].set_id(id);
        t[goal_idx].set_val(val);
    }
}

void Sequence_Binary_Tree::pre_order(int idx){
    if (t[idx].get_id())
        printf("%d ", t[idx].get_val());
    if (is_valid_idx(idx*2))
        pre_order(idx*2);
    if (is_valid_idx(idx*2+1))
        pre_order(idx*2+1);
}

void Sequence_Binary_Tree::in_order(int idx){
    if (is_valid_idx(idx*2))
        in_order(idx*2);
    if (t[idx].get_id())
        printf("%d ", t[idx].get_val());
    if (is_valid_idx(idx*2+1))
        in_order(idx*2+1);
}

void Sequence_Binary_Tree::post_order(int idx){
    if (is_valid_idx(idx*2))
        post_order(idx*2);
    if (is_valid_idx(idx*2+1))
        post_order(idx*2+1);
    if (t[idx].get_id())
        printf("%d ", t[idx].get_val());
}
