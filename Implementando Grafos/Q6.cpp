#include <iostream>
#include <vector>
#include <cstdlib> // atoi
#include <string>  // stod
#include <iomanip> // setw

using namespace std;

typedef unsigned int Vertex;

class DigraphAM
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Vertex **adj_matrix;

public:
    DigraphAM(unsigned int vertices, unsigned int edge) : num_vertices(vertices), num_edges(edge)
    {

        adj_matrix = new Vertex *[num_vertices];
        for (unsigned int i = 0; i < num_vertices; ++i)
        {
            adj_matrix[i] = new Vertex[num_vertices];
            // Inicializando a matriz com inf
            fill(adj_matrix[i], adj_matrix[i] + num_vertices, 0);
        }
    }

    ~DigraphAM();

    void add_edge(Vertex u, Vertex v)
    {
        adj_matrix[u][v] = 1;
    }

    void remove_edge(Vertex u, Vertex v)
    {
        adj_matrix[u][v] = 0;
    }

    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }
    Vertex **get_adj() { return adj_matrix; }
    float get_weight_edge(Vertex u, Vertex v) { return adj_matrix[u][v]; }
};

DigraphAM::~DigraphAM()
{
    for (unsigned int i = 0; i < num_vertices; ++i)
    {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
}

void display_matadj_graph(DigraphAM &g)
{

    for (unsigned int i = 0; i < g.get_num_vertices(); i++)
    {
        for (unsigned int j = 0; j < g.get_num_vertices(); j++)
        {
            cout << g.get_weight_edge(i, j) << " ";
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

    unsigned int vert = (unsigned int)values[0];
    unsigned int edg = (unsigned int)values[1];
    DigraphAM graph(vert, edg);

    for (unsigned int i = 2; i <= (edg * 2); i += 2)
    {
        Vertex u = (unsigned int)values[i];
        Vertex v = (unsigned int)values[i + 1];
        graph.add_edge(u, v);
    }

    cout << "num_vertices: " << graph.get_num_vertices() << endl;
    cout << "num_edges: " << graph.get_num_edges() << endl;

    display_matadj_graph(graph);

    return 0;
}