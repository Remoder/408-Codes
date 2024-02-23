void Adjacency_Matrix::add_edge(int u, int v, int w=1){
    if (!exist_node(u) || !exist_node(v))
        printf("No such a node!");
    else 
        matrix[u][v] = w;
}