#include <iostream>
#include "..\Stack_And_Queue\Stack.cpp"
using namespace std;

const int MEMORY = 130;

class Sequence_Binary_Tree{
public:
    int t[MEMORY]; 

public:
    Sequence_Binary_Tree(){
        for (int i = 1; i < MEMORY; i++)
            t[i] = 0;
    }

    void init(int);
    void set(int, int);
    void increase(int);
    void pre_order();
    void in_order();
    void post_order();
} ;

void Sequence_Binary_Tree_test(){
    int n, x, y;
    cin >> n;
    Sequence_Binary_Tree *t = new Sequence_Binary_Tree();
    while (cin >> x >> y){
        t->set(x, y);
    }
    t->pre_order();
    t->in_order();
}

void Sequence_Binary_Tree::set(int idx, int val){
    if (idx < 1 || idx > MEMORY)
        printf("Invalid index!\n");
    else
        t[idx] = val;
}

void Sequence_Binary_Tree::pre_order(){
    int id = 1;
    Stack s; s.push(id);
    while ((id <= MEMORY && t[id]) || !s.empty()){
        if (t[id]){
            cout << t[id] << ' '; 
            id *= 2;
            if (t[id])
                s.push(id);
        } else {
            id = s.top(); s.pop();
            id = id * 2 + 1;
            if (t[id])
                s.push(id);
        }
    }
    cout << endl;
}

void Sequence_Binary_Tree::in_order(){
    int id = 1; Stack s;
    while ((id <= MEMORY && t[id]) || !s.empty()){
        if (t[id]){
            s.push(id);
            id *= 2;
        } else {
            id = s.top(); s.pop();
            cout << t[id] << ' ';
            id = id * 2 + 1;
        }
    }
    cout << endl;
}