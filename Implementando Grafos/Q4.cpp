#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib> // atoi
#include <string>  // stod
#include <iomanip> // setw

using namespace std;

typedef unsigned int Vertex;
typedef float Weight;

const Weight inf = numeric_limits<Weight>::infinity();

class WeightedGraphAM
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Weight **adj_matrix;

public:
    WeightedGraphAM(unsigned int vertices, unsigned int edge) : num_vertices(vertices), num_edges(edge)
    {

        adj_matrix = new Weight *[num_vertices];
        for (unsigned int i = 0; i < num_vertices; ++i)
        {
            adj_matrix[i] = new Weight[num_vertices];
            // Inicializando a matriz com inf
            fill(adj_matrix[i], adj_matrix[i] + num_vertices, inf);
        }
    }

    ~WeightedGraphAM();

    void add_edge(Vertex u, Vertex v, Weight w)
    {
        adj_matrix[u][v] = w;
        adj_matrix[v][u] = w;
    }

    void remove_edge(Vertex u, Vertex v)
    {
        adj_matrix[u][v] = numeric_limits<Weight>::infinity();
    }

    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }
    Weight **get_adj() { return adj_matrix; }
    float get_weight_edge(Vertex u, Vertex v) { return adj_matrix[u][v]; }
};

WeightedGraphAM::~WeightedGraphAM()
{
    for (unsigned int i = 0; i < num_vertices; ++i)
    {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
}

void display_matadj_graph(WeightedGraphAM &g)
{

    for (unsigned int i = 0; i < g.get_num_vertices(); i++)
    {
        for (unsigned int j = 0; j < g.get_num_vertices(); j++)
        {
            if (g.get_weight_edge(i, j) != inf)
            {
                cout << g.get_weight_edge(i, j) << " ";
            }
            else
            {
                cout << "inf ";
            }
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
    WeightedGraphAM graph(vert, edg);

    cout << vert << "\t" << edg << endl;

    for (unsigned int i = 2; i < (edg * 3); i += 3)
    {
        Vertex u = (unsigned int)values[i];
        Vertex v = (unsigned int)values[i + 1];
        Weight w = values[i + 2];
        graph.add_edge(u, v, w);
        graph.add_edge(v, u, w);
    }

    cout << "num_vertices: " << graph.get_num_vertices() << endl;
    cout << "num_edges: " << graph.get_num_edges() << endl;

    display_matadj_graph(graph);

    return 0;
}