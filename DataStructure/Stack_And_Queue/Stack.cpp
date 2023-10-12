#include "..\Linear_List\Linked_List.cpp"
#include <iostream>

class Stack: public Linked_List_Without_Head{
public:
    void push(int);
    void pop();
    int top();
} ;

void stack_test(){
    Stack s;
    int n;
    while (cin >> n){
        s.push(n);
    }
    while (!s.empty()){
        printf("%d ", s.top());
        s.pop();
    }
}

int main(){
    stack_test();
    return 0;
}

void Stack::push(int x){
    insert_elem(get_len()+1, x);
}

void Stack::pop(){
    if (Linked_List_Without_Head::empty()){
        printf("No element!\n");
    } else {
        del_elem(get_len());
    }
}

int Stack::top(){
    if (Linked_List_Without_Head::empty()){
        printf("No element!\n");
    } else {
        return get_elem(get_len());
    }
}