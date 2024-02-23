#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 110;
const int INF = 1e9 + 100;

class Adjacency_Matrix{
private:
    int size;
    int matrix[MAX_SIZE][MAX_SIZE];

public:
    Adjacency_Matrix(int);
    void init(int);
    void add_edge(int, int, int);
    void del_edge(int, int);
    void add_node(int);
    void del_node(int);
    bool exist_node(int);
    bool adjacent(int, int);
    vector<int> neighbors(int);
    int first_neighbor(int);
    int next_neightbor(int, int);
    void display();
} ;

void Adjacency_Matrix_test(){
    int n, u, v, w;
    cout << "How many nodes in the graph: "; cin >> n;
    Adjacency_Matrix graph(n);
    cout << "Created Successfully!\n";
    while (n){
        cout << "\n***********************************************************\n| 0       | : Exit\n| 1 u v w | : Add an edge with value [w] from [u] to [v]\n| 2 u v   | : Del an edge from [u] to [v]\n| 3 id    | : Add the node with index [id]\n| 4 id    | : Del the node with index [id]\n| 5 u v   | : Check if [u] and [v] is adjacent or not\n| 6 id    | : Get all the neighbors of [id]\n| 7 id    | : Get the first neighbor of [id]\n| 8 id x  | : Get the next neighbor befind [x] of [id]\n| 9       | : Display the adjacency matrix of the graph\n***********************************************************\n";
        cin >> n;    
        switch (n) {
            case 0:
                break;
            case 1:
                cin >> u >> v >> w;
                if (graph.exist_node(u) && graph.exist_node(v)){
                    graph.add_edge(u, v, w);
                    if (graph.adjacent(u, v))
                        cout << "Edge added successfully!\n";
                } else {
                    printf("No such a node!\n");
                }
                break;
            case 2:
                cin >> u >> v;
                if (graph.exist_node(u) && graph.exist_node(v)){
                    graph.del_edge(u, v);
                    if (!graph.adjacent(u, v))
                        cout << "Edge deleted successfully!\n";
                } else {
                    printf("No such a node!\n");
                }
                break;
            case 3:
                cin >> u;
                if (!graph.exist_node(u)){
                    graph.add_node(u);
                    if (graph.exist_node(u))
                        cout << "Node added successfully!\n";
                } else {
                    printf("The node has been already existed!\n");
                }
                break;
            case 4:
                cin >> u;
                if (graph.exist_node(u)){
                    graph.del_node(u);
                    if (!graph.exist_node(u))
                        cout << "Node deleted successfully!\n";
                } else {
                    printf("No such a node!\n");
                }
                break;
            case 5:
                cin >> u >> v;
                if (graph.exist_node(u) && graph.exist_node(v)){
                    if (graph.adjacent(u, v))
                        cout << "They are adjacent!\n";
                    else cout << "They are not adjacent!\n";
                } else {
                    printf("No such a node!\n");
                }
                break;
            case 6: {
                cin >> u;
                if (graph.exist_node(u)){
                    vector<int> res;
                    res = graph.neighbors(u);
                    cout << "The neighbors of " << u << " are: ";
                    for (vector<int>::iterator it = res.begin(); it != res.end(); it++)
                        cout << *it << ' ';
                    cout << endl;
                } else {
                    printf("No such a node!\n");
                }
                break;
            }
            case 7:
                cin >> u;
                if (graph.exist_node(u)){
                    v = graph.first_neighbor(u);
                    if (v != -1) cout << "The first neighbor of " << u << " is " << v << " !\n";
                    else cout << "It seems " << u << " has no neighbor!\n";
                } else {
                    printf("No such a node!\n");
                }
                break;
            case 8:
                cin >> u >> v; w = 0;
                if (graph.exist_node(u) && graph.exist_node(v)){
                    w = graph.next_neightbor(u, v);
                    if (w != -1) cout << "The next neighbor of " << u << " after " << v << " is " << w << " !\n";
                    else cout << "It seems " << u << " has no more neighbor!\n";
                } else {
                    printf("No such a node!\n");
                }
                break;
            case 9:
                graph.display();
                break;
        }
    }
}

int main(){
    Adjacency_Matrix_test();
    return 0;
}

Adjacency_Matrix::Adjacency_Matrix(int _size = MAX_SIZE){
    init(_size); 
}

void Adjacency_Matrix::init(int _size = MAX_SIZE){
    size = _size;
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            matrix[i][j] = INF;
    cout << matrix[1][3] << endl;
}

void Adjacency_Matrix::add_edge(int u, int v, int w=1){
    if (!exist_node(u) || !exist_node(v))
        printf("No such a node!\n");
    else 
        matrix[u][v] = w;
}

void Adjacency_Matrix::del_edge(int u, int v){
    if (!exist_node(u) || !exist_node(v))
        printf("No such a node!\n");
    else if (u == v)
        printf("Cannot do so!\n");
    else if (adjacent(u, v))
        printf("There is no path!\n");
    else     
        matrix[u][v] = INF;
}

void Adjacency_Matrix::add_node(int id){
    if (id > size)
        printf("Can not create such a node!\n");
    matrix[id][id] = 0;    
}

void Adjacency_Matrix::del_node(int id){
    if (!exist_node(id)) return ;
    for (int i = 1; i <= size; i++)
        matrix[i][id] = matrix[id][i] = INF;
}

bool Adjacency_Matrix::exist_node(int id){
    return 1 <= id && id <= size && matrix[id][id] == 0;
}

bool Adjacency_Matrix::adjacent(int u, int v){
    if (!exist_node(u) || !exist_node(v)){
        printf("No such a node!\n");
        return false;
    } else     
        return matrix[u][v] != INF;
}

vector<int> Adjacency_Matrix::neighbors(int id){
    vector<int> res;
    if (!exist_node(id)){
        printf("No such a node!\n");
        return res;
    } else {
        for (int i = 1; i <= size; i++)
            if ((matrix[id][i] != INF && matrix[i][id] != 0) || (matrix[id][i] != INF && matrix[id][i] != 0))
                res.push_back(i);
        return res;
    }
}

int Adjacency_Matrix::first_neighbor(int id){
    if (!exist_node(id)){
        printf("No such a node!\n");
        return -1;
    } else {
        for (int i = 1; i <= size; i++)
            if (matrix[id][i] && id != i)
                return i;
        return -1;
    }
}

int Adjacency_Matrix::next_neightbor(int id, int goal){
    if (!exist_node(id)){
        printf("No such a node!\n");
        return -1;
    } else {
        for (int i = goal + 1; i <= size; i++)
            if (matrix[id][i] && id != i)
                return i;
        return -1;
    }
}

void Adjacency_Matrix::display(){
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            if (matrix[i][j] != INF && i != j)
                printf("%d is adjacency to %d\n", i, j);
}



