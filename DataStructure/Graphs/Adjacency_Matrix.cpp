#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 1010;
const int INF = 1e9 + 100;

class Adjacency_Matrix{
private:
    int size, idx;
    char node[MAX_SIZE];
    bool matrix[MAX_SIZE][MAX_SIZE];

public:
    Adjacency_Matrix(int);
    void init();
    void add_edge(int, int, int);
    void del_edge(int, int);
    void add_node(int, char);
    void del_node(int);
    bool adjacent(int, int);
    vector<int> neighbors(int);
    int first_neighbor(int);
    int next_neightbor(int, int);
} ;

Adjacency_Matrix::Adjacency_Matrix(int _size = MAX_SIZE): 
    size(_size) {init();}

void Adjacency_Matrix::init(){
    idx = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = INF;
}

void Adjacency_Matrix::add_edge(int u, int v, int w=1){
    if (node[u] == ' ' || node[v] == ' ')
        printf("No such a node!");
    else 
        matrix[u][v] = w;
}

void Adjacency_Matrix::del_edge(int u, int v){
    if (node[u] == ' ' || node[v] == ' ')
        printf("No such a node!\n");
    else     
        matrix[u][v] = INF;
}

void Adjacency_Matrix::add_node(int id, char ch=' '){
    if (node[id] != ' ')
        printf("Such a node has been existed!\n");
    else {
        node[id] = ch;
        matrix[id][id] = 0;
    }
}

void Adjacency_Matrix::del_node(int id){
    if (node[id] = ' ') return ;
    node[id] = ' ';
    for (int i = 0; i < size; i++)
        matrix[i][id] = matrix[id][i] = INF;
}

bool Adjacency_Matrix::adjacent(int u, int v){
    if (node[u] == ' ' || node[v] == ' ')
        printf("No such a node!");
    else     
        return matrix[u][v] != INF;
}

vector<int> Adjacency_Matrix::neighbors(int id){
    vector<int> res;
    if (node[id] == ' '){
        printf("No such a node!");
        return res;
    } else {
        for (int i = 0; i < size; i++)
            if ((matrix[id][i] != INF && matrix[i][id] != 0) || (matrix[id][i] != INF && matrix[id][i] != 0))
                res.push_back(i);
        return res;
    }
}

int Adjacency_Matrix::first_neighbor(int id){
    if (node[id] == ' '){
        printf("No such a node!");
        return -1;
    } else {
        vector<int> res = neighbors(id);
        if (res.empty()) return -1;
        return res[0];
    }
}

int Adjacency_Matrix::next_neightbor(int id, int goal){
    if (node[id] == ' '){
        printf("No such a node!");
        return -1;
    } else {
        vector<int> res = neighbors(id);
        int ans = -1, sz = res.size();
        for (int i = 0; i < sz; i++)
            if (res[i] > ans){
                ans = res[i];
                break;
            }
        return ans;
    }
}




