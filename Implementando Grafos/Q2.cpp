#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>
#include <iomanip> // setw
using namespace std;

template <typename T>
class Edge
{
public:
    T weight;
    Edge() : weight(0) {}
    Edge(T _weight) : weight(_weight) {}
};

template <typename T>
class Graph
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Edge<T> **adj;

public:
    Graph(unsigned int);
    ~Graph();
    void add_edge(T, T);
    list<T> get_adj(T);
    T get_weight_edge(T, T);
    void display_matadj_graph(Graph &);
    void display_list(list<T>);
    void display_lstadj_graph(Graph &);
    unsigned int get_num_vertices();
    unsigned int get_num_edges();
};

template <typename T>
unsigned int Graph<T>::get_num_vertices()
{
    return num_vertices;
}

template <typename T>
unsigned int Graph<T>::get_num_edges()
{
    return num_edges;
}

template <typename T>
Graph<T>::Graph(unsigned int _num_vertices) : num_vertices(_num_vertices),
                                              num_edges(0)
{
    const unsigned int LINHAS = num_vertices;
    const unsigned int COLUNAS = num_vertices;
    adj = new Edge<T> *[LINHAS];
    for (int i = 0; i < LINHAS; ++i)
    {
        adj[i] = new Edge<T>[COLUNAS];
    }
}

template <typename T>
Graph<T>::~Graph()
{
    const unsigned int LINHAS = num_vertices;
    for (int i = 0; i < LINHAS; ++i)
    {
        delete[] adj[i];
    }
    delete[] adj;
}

template <typename T>
void Graph<T>::add_edge(T u, T v)
{

    if (adj[u][v].weight != 0 || adj[v][u].weight != 0)
    {
        cout << "Edge already inserted: (" << u << ", " << v << ")\n";
        return;
    }
    Edge<T> edge{1};
    adj[u][v] = edge;
    adj[v][u] = edge;
    num_edges++;
}

template <typename T>
list<T> Graph<T>::get_adj(T u)
{
    list<T> values;
    for (int v = 0; v < num_vertices; ++v)
    {
        if (adj[u][v].weight != 0)
        {
            values.push_back(v);
        }
    }
    return values;
}

template <typename T>
T Graph<T>::get_weight_edge(T u, T v)
{
    return adj[u][v].weight;
}

template <typename T>
void display_matadj_graph(Graph<T> &g)
{
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << "\n";

    for (unsigned int i = 0; i < g.get_num_vertices(); i++)
    {
        for (unsigned int j = 0; j < g.get_num_vertices(); j++)
        {
            cout << g.get_weight_edge(i, j) << " ";
        }
        cout << endl;
    }
}

template <typename T>
void display_list(list<T> &lst)
{
    for (auto v : lst)
        cout << v << ", ";
    cout << "\n";
}

template <typename T>
void display_lstadj_graph(Graph<T> &g)
{
    for (T v = 0; v < g.get_num_vertices(); v++)
    {
        list<T> lst_adj = g.get_adj(v);
        cout << "v[" << v << "] : ";
        display_list(lst_adj);
    }
}

int main()
{
    // Inserindo valores diretamente na linha de comando
    unsigned int num_vertices, num_edges;
    cin >> num_vertices >> num_edges;

    Graph<unsigned int> g{num_vertices};

    // Adiciona arestas ao grafo
    for (int i = 0; i < num_edges; ++i)
    {
        unsigned int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }


    display_matadj_graph(g);

    return 0;
}
