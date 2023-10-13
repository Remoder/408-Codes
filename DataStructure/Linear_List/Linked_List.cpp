#include <iostream>
using namespace std;

class Node{
private:
    int val;

public:
    Node *nxt, *pri;
    Node(int _val = 0):
        val(_val), nxt(NULL), pri(NULL) {}

    ~Node(){
        delete nxt;
        delete pri;
    }
    
    int get_val()
        {return val;}
    
    void set_val(int _val)
        {val = _val;}
};

class Linked_List_Base{
protected:
    int len;
    Node *head;

public:
    Linked_List_Base(int _len = 0):
        len(_len), head(NULL){init();}

    ~Linked_List_Base(){
        delete[] head;
    }

    void init();
    int get_len();
    bool empty();
} ;

class Linked_List_Without_Head: public Linked_List_Base{
public:
    int get_elem(int);
    int get_idx(int);
    void insert_elem(int, int);
    void del_elem(int);
    void set_elem(int, int);
    void display();
} ;

class Linked_List_With_Head: public Linked_List_Base{
public:
    int get_elem(int);
    int get_idx(int);
    void insert_elem(int, int);
    void del_elem(int);
    void set_elem(int, int);
    void display();
} ;

void linked_list_test(){
    Linked_List_With_Head a;
    cout << "Add numbers from 1 to 10: ";
    for (int i = 1; i <= 10; i++)
        a.insert_elem(i,i);
    a.display();
    cout << "After set the 3rd number to 10: ";
    a.set_elem(3, 10);
    a.display();
    cout << "After del the 1th number: ";
    a.del_elem(1);
    a.display();
    cout << "Now the length is " << a.get_len() << ", and the 3rd number is " << a.get_elem(3) << endl;
    cout << "The first 5 appear at " << a.get_idx(5) << endl;
    cout << "Test finished\n";
}

void Linked_List_Base::init(){
    head = new Node;
    head->nxt = NULL;
    head->pri = NULL;
}

int Linked_List_Base::get_len(){
    return len;
}

bool Linked_List_Base::empty(){
    return !len;
}

int Linked_List_Without_Head::get_elem(int idx){
    if (1 <= idx && idx <= len){
        Node *cur = head;
        for (int i = 1; i < idx; i++){
            cur = cur->nxt;
        }
        return cur->get_val();
    } else {
        printf("Invalid index!\n");
        return -1;
    }
}

int Linked_List_Without_Head::get_idx(int elem){
    Node *cur = head;
    if (cur->get_val() == elem)
        return 1;
    for (int i = 2; i <= len; i++){
        cur = cur->nxt;
        if (cur->get_val() == elem)
            return i;
    }
    return -1;
}

void Linked_List_Without_Head::insert_elem(int idx, int elem){
    if (idx < 1 || idx > len + 1) {
        printf("Invalid index!\n");
        return ;
    }
    Node *p = new Node;
    p->set_val(elem);
    if (len == 0){
        head->set_val(elem);
    } else if (idx == 1){
        p->nxt = head;
        head->pri = p;
        head = p;
    } else {    
        Node *cur = head;
        for (int i = 2; i < idx; i++)
            cur = cur->nxt;
        p->pri = cur;
        p->nxt = cur->nxt;
        if (cur->nxt)
            cur->nxt->pri = p;
        cur->nxt = p;
    }
    len++;
}

void Linked_List_Without_Head::del_elem(int idx){
    if (1 <= idx && idx <= len){
        Node *cur = head;
        for (int i = 1; i < idx; i++)
            cur = cur->nxt;
        if (cur->pri)
            cur->pri->nxt = cur->nxt;
        else 
            head = cur->nxt;
        if (cur->nxt)
            cur->nxt->pri = cur->pri;
    } else {
        printf("Invalid index!\n");
    }
    if (--len == 0)
        init();
}

void Linked_List_Without_Head::set_elem(int idx, int elem){
    if (1 <= idx && idx <= len){
        Node *cur = head;
        for (int i = 1; i < idx; i++)
            cur = cur->nxt;
        cur->set_val(elem);
    } else {
        printf("Invalid index!\n");
    }
}

void Linked_List_Without_Head::display(){
    if (!len){
        cout << "No element!\n";
        return ;
    }
    Node *cur = head;
    do {
        printf("%d ", cur->get_val());
        cur = cur->nxt;
    } while (cur);
    printf("\n");
}

int Linked_List_With_Head::get_elem(int idx){
    if (1 <= idx && idx <= len){
        Node *cur = head;
        for (int i = 1; i <= idx; i++)
            cur = cur->nxt;
        return cur->get_val();
    } else {
        printf("Invalid index!\n");
        return -1;
    }
}

int Linked_List_With_Head::get_idx(int elem){
    int res = 0;
    Node *cur = head;
    while (cur->nxt){
        res++;
        cur = cur->nxt;
        if (cur->get_val() == elem)
            return res;
    }
    return -1;
}

void Linked_List_With_Head::insert_elem(int idx, int elem){
    if (idx < 1 || idx > len + 1){
        printf("Invalid index!\n");
        return ;
    }
    
    Node *cur = head;
    Node *p = new Node;
    p->set_val(elem);
    for (int i = 1; i < idx; i++)
        cur = cur->nxt;
    p->pri = cur;
    p->nxt = cur->nxt;
    if (cur->nxt)
        cur->nxt->pri = p;
    cur->nxt = p;
    len++;
}

void Linked_List_With_Head::del_elem(int idx){
    if (1 <= idx && idx <= len){
        Node *cur = head;
        for (int i = 1; i <= idx; i++)
            cur = cur->nxt;
        cur->pri->nxt = cur->nxt;
        if (cur->nxt)
            cur->nxt->pri = cur->pri;
    } else {
        printf("Invalid index!\n");
    }
    if (--len == 0)
        init();
}

void Linked_List_With_Head::set_elem(int idx, int elem){
    if (1 <= idx && idx <= len){
        Node *cur = head;
        for (int i = 1; i <= idx; i++)
            cur = cur->nxt;
        cur->set_val(elem);
    } else {
        printf("Invalid index!\n");
    }
}

void Linked_List_With_Head::display(){
    if (!len){
        cout << "No element!\n";
        return ;
    }
    Node *cur = head;
    do {
        cur = cur->nxt;
        printf("%d ", cur->get_val());
    } while (cur->nxt);
    printf("\n");
}

