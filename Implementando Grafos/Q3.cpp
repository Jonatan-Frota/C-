#include <iostream>
#include <cstdlib> // atoi
#include <string>  // stod
#include <vector>
#include <list>

using namespace std;

typedef unsigned int Vertex;
typedef float Weight;

class VertexWeightPair
{
public:
    Vertex vertex;
    Weight weight;
    VertexWeightPair(Vertex v, Weight w) : vertex(v), weight(w) {}
};

template <typename T>
class WeightedGraphAL
{
public:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj;

public:
    WeightedGraphAL(unsigned int vertices, unsigned int edges) : num_vertices(vertices), num_edges(edges)
    {
        adj = new list<VertexWeightPair>[num_vertices];
    }

    ~WeightedGraphAL();
    void add_edge(Vertex u, Vertex v, Weight w)
    {

        adj[u].emplace_back(v, w);
    }

    void remove_edge(Vertex u, Vertex v)
    {
        adj[u].remove_if([v](const VertexWeightPair &pair)
                         { return pair.vertex == v; });
        num_edges--;
    }

    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }

    list<T> get_adj(Vertex v) { return adj[v]; }
};

template <typename T>
WeightedGraphAL<T>::~WeightedGraphAL()
{
    for (unsigned int i = 0; i < num_vertices; ++i)
    {
        adj[i].clear();
    }
    delete[] adj;
}

template <typename T>
void display_graph(WeightedGraphAL<T> &g)
{
    for (unsigned int i = 0; i < g.num_vertices; ++i)
    {
        cout << i << ": ";
        for (const VertexWeightPair &pair : g.adj[i])
        {
            cout << "(" << pair.vertex << ", " << pair.weight << "), ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{

    // argc guarda a quantidade de elementos inserida
    // argv[0] guarda "a" (o nome do arquivo compilado)

    vector<float> values;
    float value = 0.0;

    for (int i = 1; i < argc; i++)
    {
        value = stof(argv[i]);
        values.push_back(value);
    }

    unsigned int num_vertices = (unsigned int)values[0];
    unsigned int num_edges = (unsigned int)values[1];

    WeightedGraphAL<VertexWeightPair> graph(num_vertices, num_edges);

    for (unsigned int i = 2; i < (num_edges * 3); i += 3)
    {
        Vertex u = (unsigned int)values[i];
        Vertex v = (unsigned int)values[i + 1];
        Weight w = values[i + 2];
        graph.add_edge(u, v, w);
        graph.add_edge(v, u, w);
    }

    display_graph(graph);

    return 0;
}