#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>
#include <iomanip> // setw
#include <limits>
using namespace std;

template <typename T>
class Edge
{
public:
    T weight;
    Edge() : weight(numeric_limits<T>::infinity()) {}
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
    void add_edge(unsigned int, unsigned int, T weight);
    list<unsigned int> get_adj(unsigned int);
    T get_weight_edge(unsigned int, unsigned int);
    void display_matadj_graph(Graph<T> &);
    void display_list(list<unsigned int>);
    void display_lstadj_graph(Graph<T> &);
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
void Graph<T>::add_edge(unsigned int u, unsigned int v, T weight)
{
    if (adj[u][v].weight != numeric_limits<T>::infinity())
    {
        cout << "Edge already inserted: (" << u << ", " << v << ")\n";
        return;
    }
    Edge<T> edge{weight};
    adj[u][v] = edge;
    num_edges++;
}

template <typename T>
list<unsigned int> Graph<T>::get_adj(unsigned int u)
{
    list<unsigned int> values;
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
T Graph<T>::get_weight_edge(unsigned int u, unsigned int v)
{
    return adj[u][v].weight;
}

template <typename T>
void display_matadj_graph(Graph<T> &g)
{
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges();
    int k = 3; // largura do campo numerico

    cout << endl;
    // Constroi cada linha da matriz
    for (unsigned int i = 0; i < g.get_num_vertices(); i++)
    {
   
        // Valores da linha
        for (unsigned int j = 0; j < g.get_num_vertices(); j++)
        {
            if (g.get_weight_edge(i, j) != numeric_limits<T>::infinity())
            {
                cout << setw(k) << g.get_weight_edge(i, j);
            }
            else
            {
                cout << "inf";
            }
            cout<<"";
        }
        cout << endl;
    }
}

template <typename T>
void display_list(const list<T> &lst)
{
    for (const auto &v : lst)
        cout << v << ", ";

}

template <typename T>
void display_lstadj_graph(Graph<T> &g)
{
    for (unsigned int v = 0; v < g.get_num_vertices(); v++)
    {
        list<unsigned int> lst_adj = g.get_adj(v);
        cout << "v[" << v << "] : ";
        display_list(lst_adj);
    }
}

int main()
{
    // Inserindo valores diretamente na linha de comando
    unsigned int num_vertices, num_edges;
    float weight;
    cin >> num_vertices >> num_edges;

    Graph<float> g{num_vertices};

    // Adiciona arestas ao grafo
    for (int i = 0; i < num_edges; ++i)
    {
        unsigned int u, v;
        cin >> u >> v;
        cin >> weight;
        g.add_edge(u, v, weight);
    }

    
    display_matadj_graph(g);

    return 0;
}