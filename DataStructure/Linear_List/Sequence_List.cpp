#include <iostream>
using namespace std;

class Sequence_List{
private:    
    int len, mem, *p;
public:
    Sequence_List(int _mem){
        init(_mem);
    }
    
    ~Sequence_List(){
        delete[] p;
    }
    
    void init(int);
    int get_elem(int);
    int get_idx(int);
    void insert_elem(int, int);
    void del_idx(int);
    void del_elem(int);
    void set_elem(int, int);
    int get_len();
    bool is_empty();
    void display();
    void increase(int);
} ;

void Sequence_List_test(){
    int op=0; int x, y, cur_len;
    cout << "How long the Sequence List should be created: ";
    cin >> x;
    Sequence_List s(max(0, x));
    cout << "The Sequence List with length of " << max(0, x) << " has been created.\n";
    while (op != 10){
        cout << "\n***********************\n| 1 x   | : get the x-th element\n| 2 x   | : get the index of value x\n| 3 a b | : insert b as the a-th elemt\n| 4 x   | : delete the x-th element\n| 5 x   | : delete the first element with value of x\n| 6 a b | : set the a-th element with value b\n| 7     | : get the length of the list\n| 8 x   | : extend x memory\n| 9     | : display the list\n| 10    | : quit\n***********************\n";
        cin >> op;
        switch (op){
            case 1:
                cin >> x;
                if (x < 1 || x > s.get_len()) {cout << "Invalid index!" << endl; break;}
                cout << "The " << x << "-th element is " << s.get_elem(x) << "." << endl;
                break;
            case 2:
                cin >> x;
                if (s.get_idx(x) != -1)
                    cout << x << " is the " << s.get_idx(x) << "-th element." << endl;
                else 
                    cout << x << " is not in the list." << endl;
                break;
            case 3:
                cin >> x >> y;
                cur_len = s.get_len();
                if (x < 1 || x > s.get_len() + 1) {cout << "Invalid index!" << endl; break;}
                s.insert_elem(x, y);
                if (s.get_len() != cur_len)
                    cout << "Insert successfully." << endl;
                break;
            case 4:
                cin >> x;
                if (x < 1 || x > s.get_len()) {cout << "Invalid index!" << endl; break;}
                s.del_idx(x);
                cout << "The " << x << "-th element has been deleted." << endl;
                break;
            case 5:
                cin >> x;
                if (s.get_idx(x) == -1) {
                    cout << "No such an element in the list!" << endl;
                } else {
                    s.del_elem(x);
                    cout << "The first element " << x << " has been deleted." << endl;
                }
                break;
            case 6:
                cin >> x >> y;
                if (x < 1 || x > s.get_len()) {cout << "Invalid index!" << endl; break;}
                s.set_elem(x, y);
                cout << "The " << x << "-th element has been " << y << "." << endl;
                break;
            case 7:
                cout << "The length of Sequence List is " << s.get_len() << "." << endl;
                break;
            case 8:
                cin >> x;
                s.increase(x);
                cout << "Increase successfully." << endl;
                break;
            case 9:
                s.display();
                break;
            case 10:
                break;
            default:
                cout << "Unknown order!" << endl;
                break;
        }
    }   
}

void Sequence_List::init(int _mem){
    if (_mem < 0){
        printf("Invalid memory!\n");
        return ;
    }
    len = 0; mem = _mem;
    p = new int(_mem);
}

int Sequence_List::get_elem(int idx){
    if (1 <= idx && idx <= len)
        return p[idx-1];
    else {
        printf("Invalid index!\n");
        return -1;
    }
}

int Sequence_List::get_idx(int elem){
    for (int i = 0; i < len; i++)
        if (p[i] == elem)
            return i + 1;
    return -1;
}

void Sequence_List::insert_elem(int idx, int elem){
    if (idx > len + 1 || idx < 1){
        printf("Invalid index!\n");
        return ;
    }
    if (len == mem){
        printf("No more memory!\n");
        return ;
    }
    for (int i = len - 1; i >= idx - 1; i--)
        p[i+1] = p[i];
    p[idx-1] = elem;
    len++;
} 

void Sequence_List::del_idx(int idx){
    if (1 <= idx && idx <= len){
        for (int i = idx - 1; i < len; i++)
            p[i] = p[i+1];
        len--;
    } else {
        printf("Invalid index!\n");
    }
}

void Sequence_List::del_elem(int elem){
    if (get_idx(elem) == -1)
        return ;
    del_idx(get_idx(elem));
}

void Sequence_List::set_elem(int idx, int elem){
    if (1 <= idx && idx <= len){
        p[idx-1] = elem;
    } else {
        printf("Invalid index!\n");
    }
}

int Sequence_List::get_len(){
    return len;
}

bool Sequence_List::is_empty(){
    return !len;
}

void Sequence_List::display(){
    cout << "The list is [";
    if (len)
        cout << p[0];
    for (int i = 1; i < len; i++)
        printf(",%d", p[i]);
    printf("]\n");
}

void Sequence_List::increase(int _mem){
    if (_mem < 0) {
        printf("Invalid momory!\n");
        return ;
    } 
    int *q = p; mem += _mem;
    p = new int[mem];
    for (int i = 0; i < len; i++)
        p[i] = q[i];
    delete[] q;
}
