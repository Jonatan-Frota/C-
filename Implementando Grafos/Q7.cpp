#include <iostream>
#include <list>
using namespace std;

template <typename T>
class Vertex
{
private:
    T value;
    float weight;

public:
    Vertex(T u, float w);
    T get_value() { return value; }
    bool operator==(const Vertex &other) const
    {
        return this->value == other.value;
    }
    float get_weight() { return weight; }
};

template <typename T>
Vertex<T>::Vertex(T u_value, float _weight)
{
    value = u_value;
    weight = _weight;
}

template <typename T>
class Graph
{
private:
    unsigned int num_vertex;
    unsigned int num_edges;
    list<Vertex<T>> *adj;

public:
    Graph(unsigned int num_v);
    ~Graph();
    void add_edge(T u, T v, float _weight);
    void delete_edge(T u, T v);
    void display_graph();
    void display_list(T u);
    list<Vertex<T>> get_adj(T u) { return adj[u]; }
    unsigned int get_num_vertex() { return num_vertex; }
    unsigned int get_num_edges() { return num_edges; }
};

template <typename T>
Graph<T>::Graph(unsigned int num_v)
{
    num_vertex = num_v;
    adj = new list<Vertex<T>>[num_vertex];
}

template <typename T>
Graph<T>::~Graph()
{
    for (int i = 0; i < num_vertex; i++)
    {
        adj[i].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_vertex = 0;
    num_edges = 0;
}

template <typename T>
void Graph<T>::add_edge(T u, T v, float _weight)
{

    for (auto it = adj[u].begin(); it != adj[u].end(); it++)
    {
        if (it->get_value() == v)
        {
            cout << "\nEdge already inserted!";
            return;
        }
    }

    adj[u].push_back(Vertex<T>(v, _weight));
    num_edges++;
}

template <typename T>
void Graph<T>::delete_edge(T u, T v)
{
    for (auto it = adj[u].begin(); it != adj[u].end(); it++)
    {
        if (it->get_value() == v)
        {
            adj[u].erase(it);
            num_edges--;
            return;
        }
    }
}

template <typename T>
void Graph<T>::display_graph()
{
    for (int i = 0; i < num_vertex; i++)
    {
        cout<< i << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); it++)
        {
            cout << "(" << it->get_value() << ", " << it->get_weight() << "), ";
        }
        cout << "\n";
    }
}

template <typename T>
void Graph<T>::display_list(T u)
{
    for (auto it = adj[u].begin(); it != adj[u].end(); it++)
    {
        cout << "(" << u << ", " << it->get_value() << it->get_weight() << ") ";
    }
}

void input_graph(Graph<int> &g, unsigned int num_edges)
{
    int u, v;
    float _weight;
    for (int i = 0; i < num_edges; i++)
    {
        cin >> u;
        cin >> v;
        cin >> _weight;
        g.add_edge(u, v, _weight);
    }
}

int main()
{
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    Graph<int> g{num_vertices};
    input_graph(g, num_edges);
    g.display_graph();

    return 0;
}
