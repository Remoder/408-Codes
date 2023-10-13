#include "..\Linear_List\Linked_List.cpp"
#include <iostream>

class Queue: public Linked_List_Without_Head{
public:
    ~Queue(){
        while (!empty())
            pop();
    }

    void push(int);
    void pop();
    int front();
} ;

void queue_test(){
    Queue q;
    int n;
    while (cin >> n){
        q.push(n);
    }
    while (!q.empty()){
        printf("%d ", q.front());
        q.pop();
    }
}

void Queue::push(int x){
    insert_elem(get_len()+1, x);
}

void Queue::pop(){
    if (Linked_List_Without_Head::empty()){
        printf("No element!\n");
    } else {
        del_elem(1);
    }
}

int Queue::front(){
    if (Linked_List_Without_Head::empty()){
        printf("No element!\n");
    } else {
        return get_elem(1);
    }
}
