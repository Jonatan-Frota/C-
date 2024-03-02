#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

typedef unsigned int Vertex;

template <typename T>
class DigraphAL
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj;

public:
    DigraphAL(unsigned int vertices, unsigned int edges) : num_vertices(vertices), num_edges(edges)
    {
        adj = new list<Vertex>[num_vertices];
    }

    ~DigraphAL();

    void add_edge(Vertex u, Vertex v)
    {
        if (std::find(adj[u].begin(), adj[u].end(), v) == adj[u].end())
        {
            adj[u].emplace_back(v);
        }
    }

    unsigned int get_num_vertices() const
    {
        return num_vertices;
    }

    unsigned int get_num_edges() const
    {
        return num_edges;
    }

    list<T> get_adj(Vertex v) const
    {
        return adj[v];
    }
};

template <typename T>
DigraphAL<T>::~DigraphAL()
{
    delete[] adj;
}

template <typename T>
void printAdjList(const DigraphAL<T> &graph)
{
    for (unsigned int i = 0; i < graph.get_num_vertices(); ++i)
    {
        cout << i << ": ";
        for (const Vertex &pair : graph.get_adj(i))
        {
            cout << pair << ", ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    vector<float> values;
    float value = 0.0;

    for (int i = 1; i < argc; i++)
    {
        value = stof(argv[i]);
        values.push_back(value);
    }

    unsigned int num_vertices = (unsigned int)(values[0]);
    unsigned int num_edges = (unsigned int)(values[1]);

    DigraphAL<Vertex> graph(num_vertices, num_edges);

    for (unsigned int i = 2; i <= (num_edges * 2); i += 2)
    {
        Vertex u = static_cast<unsigned int>(values[i]);
        Vertex v = static_cast<unsigned int>(values[i + 1]);
        graph.add_edge(u, v);
    }

    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;

    printAdjList(graph);

    return 0;
}