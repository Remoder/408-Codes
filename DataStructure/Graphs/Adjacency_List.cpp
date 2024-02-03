#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 1010;

class Node_List{
public:
    int n;
    Node_List* nxt;
} ;

class Adjacency_List{
private:
    char info[MAX_SIZE]; 
    Node_List* node[MAX_SIZE];
public:
    Adjacency_List();
    void add_edge(int, int, int);
    void del_edge(int, int);
    void add_node(char);
    void del_node(int);
    bool adjacent(int, int);
    vector<int> neighbors(int);
    int first_neighbor(int);
    int next_neightbor(int, int);
} ;

Adjacency_List::Adjacency_List(){
    
}


