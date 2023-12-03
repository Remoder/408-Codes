#include <iostream>
using namespace std;

class Disjoint_Set_Union{
private:
    int size, *fa; 
    int find_father(int);

public: 
    Disjoint_Set_Union(int _size=0):
        size(_size) {init();}

    ~Disjoint_Set_Union(){
        delete[] fa;
    }

    void init();
    void merge(int, int);
    bool check(int, int);
    bool invalid_id(int);
} ;

void Disjoint_Set_Union::init(){
    fa = new int(size+1);
    for (int i = 0; i <= size; i++)
        fa[i] = i;
}

int Disjoint_Set_Union::find_father(int x){
    return x == fa[x] ? fa[x] : fa[x] = find_father(fa[x]);
}

void Disjoint_Set_Union::merge(int x, int y){
    int i = find_father(x);
    int j = find_father(y);
    if (i != j)
        fa[i] = j; 
}

bool Disjoint_Set_Union::check(int x, int y){
    return find_father(x) == find_father(y);
}

bool Disjoint_Set_Union::invalid_id(int id){
    return 0 <= id && id <= size;
}

void Disjoint_Set_Union_test(){
    int n, x, y;
    cout << "Input the size of data: "; cin >> n;
    Disjoint_Set_Union* dsu = new Disjoint_Set_Union(n);
    while (1){
        cout << "\nInput [0] to exit,\n";
        cout << "Input [1 x y] to merge x and y,\n";
        cout << "Input [2 x y] to check if x and y in the same set.\n";
        cout << "INPUT: "; cin >> n;
        if (!n) break;
        cin >> x >> y;
        if (!dsu->invalid_id(x) || !dsu->invalid_id(y)){
            printf("Invalid index!\n"); continue;
        }
        if (n == 1) {
            dsu->merge(x, y);
            printf("Merge successfully!\n");
        } else if (dsu->check(x, y))
            printf("%d and %d are in the same set!\n", x, y);
        else 
            printf("%d and %d are NOT in the same set!\n", x, y);
    }
}

int main(){
    Disjoint_Set_Union_test();
    return 0;
}