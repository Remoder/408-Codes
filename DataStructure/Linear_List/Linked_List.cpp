#include <iostream>
using namespace std;

class Node{
private:
    int val;

public:
    Node *nxt, *pri;
    Node(int _val = 0):
        val(_val), nxt(NULL), pri(NULL) {}
    
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
        Node *_p = head, *_nxt = NULL;
        while (_p){
            _nxt = _p->nxt;
            delete _p;
            _p = _nxt;
        }
    }

    void init();
    int get_len();
    bool empty();
    virtual int get_elem(int) = 0;
    virtual int get_idx(int) = 0;
    virtual void insert_elem(int, int) = 0;
    virtual void del_elem(int) = 0;
    virtual void set_elem(int, int) = 0;
    virtual void display() = 0;
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

void Linked_List_test(){
    int x, y, cur_len, op = 0;
    Linked_List_Without_Head *a = new Linked_List_Without_Head();
    cout << "Created Successfully!\n";
    while (op != 8){
        cout << "\n***********************\n| 1 x   | : get the x-th element\n| 2 x   | : get the index of value x\n| 3 a b | : insert b as the a-th elemt\n| 4 x   | : delete the x-th element\n| 5 a b | : set the a-th element with value b\n| 6     | : get the length of the list\n| 7     | : display the list\n| 8     | : quit\n***********************\n";
        cin >> op;
        switch (op){
            case 1:
                cin >> x;
                if (x < 1 || x > a->get_len()) {cout << "Invalid index!" << endl; break;}
                cout << "The " << x << "-th element is " << a->get_elem(x) << "." << endl;
                break;
            case 2:
                cin >> x;
                if (a->get_idx(x) != -1)
                    cout << x << " is the " << a->get_idx(x) << "-th element." << endl;
                else 
                    cout << x << " is not in the list." << endl;
                break;
            case 3:
                cin >> x >> y;
                cur_len = a->get_len();
                if (x < 1 || x > a->get_len() + 1) {cout << "Invalid index!" << endl; break;}
                a->insert_elem(x, y);
                if (a->get_len() != cur_len)
                    cout << "Insert successfully." << endl;
                break;
            case 4:
                cin >> x;
                if (x < 1 || x > a->get_len()) {cout << "Invalid index!" << endl; break;}
                a->del_elem(x);
                cout << "The " << x << "-th element has been deleted." << endl;
                break;
            case 5:
                cin >> x >> y;
                if (x < 1 || x > a->get_len()) {cout << "Invalid index!" << endl; break;}
                a->set_elem(x, y);
                cout << "The " << x << "-th element has been " << y << "." << endl;
                break;
            case 6:
                cout << "The length of Sequence List is " << a->get_len() << "." << endl;
                break;
            case 7:
                cout << "The list is: ";
                a->display();
                break;
            case 8:
                break;
            default:
                cout << "Unknown order!" << endl;
                break;
        }
    }   
}

int main(){
    Linked_List_test();
    return 0;
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

