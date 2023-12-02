#include "Linked_Binary_Tree.cpp"
#include <iostream>
#include <queue>
using namespace std;

class helper_cmp{
public:
    bool operator() (const Linked_Binary_Tree* a, const Linked_Binary_Tree* b) const {
        return a->rt->get_val() > b->rt->get_val();
    }
} ;

Linked_Binary_Tree* create_huffman_tree(int num, int* arr){
    int id = 2 * num - 1;
    Linked_Binary_Tree* t = new Linked_Binary_Tree();
    priority_queue<Linked_Binary_Tree*, vector<Linked_Binary_Tree*>, helper_cmp> q;
    for (int i = 0; i < num; i++){
        q.push(new Linked_Binary_Tree(new Node(id--, arr[i])));
    }
    while (q.size() >= 2){
        Linked_Binary_Tree* t1 = q.top(); q.pop();
        Linked_Binary_Tree* t2 = q.top(); q.pop();
        Linked_Binary_Tree* t3 = new Linked_Binary_Tree(new Node(id--, t1->rt->get_val() + t2->rt->get_val()));
        t3->add(id+1, 'l', t1);
        t3->add(id+1, 'r', t2);
        q.push(t3);
    }
    t = q.top(); q.pop();
    return t;
}

int main(){
    int* arr = new int[5];
    arr[0] = 7; arr[1] = 5; arr[2] = 2; arr[3] = 4;
    Linked_Binary_Tree* t = new Linked_Binary_Tree();
    t = create_huffman_tree(4, arr);
    t->display_tree();
    return 0;
}