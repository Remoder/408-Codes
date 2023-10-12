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
    void del_elem(int);
    void set_elem(int, int);
    int get_len();
    bool is_empty();
    void display();
    void increase(int);
} ;

void sequence_list_test(){
    Sequence_List a(10);
    cout << "Add numbers from 1 to 10: ";
    for (int i = 1; i <= 10; i++)
        a.insert_elem(i,i);
    a.display();
    cout << "After set the 3rd number to 10: ";
    a.set_elem(3, 10);
    a.display();
    cout << "After del the 4th number: ";
    a.del_elem(4);
    a.display();
    cout << "Now the length is " << a.get_len() << ", and the 3rd number is " << a.get_elem(3) << endl;
    cout << "The first 5 appear at " << a.get_idx(5) << endl;
    cout << "Test finished\n";
}

// int main(){
//     sequence_list_test();
//     return 0;
// }

void Sequence_List::init(int _mem){
    if (_mem < 0){
        printf("Invalid memory!\n");
        return ;
    }
    len = -1; mem = _mem;
    p = new int(_mem);
}

int Sequence_List::get_elem(int idx){
    if (1 <= idx && idx <= len)
        return p[idx];
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
    if (idx > mem || idx <= 0){
        printf("Invalid index!\n");
        return ;
    }
    if (len == mem){
        printf("No more memory!\n");
    }
    for (int i = len - 1; i > idx - 1; i--)
        p[i+1] = p[i];
    p[idx-1] = elem;
    len++;
} 

void Sequence_List::del_elem(int idx){
    if (1 <= idx && idx <= len){
        for (int i = idx - 1; i < len; i++)
            p[i] = p[i+1];
        len--;
    } else {
        printf("Invalid index!\n");
    }
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
    for (int i = 0; i < len; i++)
        printf("%d ", p[i]);
    printf("\n");
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
