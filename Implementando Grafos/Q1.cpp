#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Implementação de uma fila simples
template <typename T>
class Queue
{
private:
    std::list<T> lst;

public:
    void enqueue(T item); 
    T dequeue();          
    bool isEmpty();       
};


template <typename T>
void Queue<T>::enqueue(T item)
{
    lst.push_back(item);
}


template <typename T>
T Queue<T>::dequeue()
{
    T front = lst.front();
    lst.pop_front();
    return front;
}


template <typename T>
bool Queue<T>::isEmpty()
{
    return lst.empty();
}

// Classe representando o grafo do tabuleiro:
class TabuleiroGrafo
{
public:
    TabuleiroGrafo();              
    void add_Cavalo(int x, int y);  // Adiciona um cavaleiro ao tabuleiro
    void add_Rei(int x, int y);   // Adiciona um rei ao tabuleiro
    void Ameacas();           // Encontra as ameaças ao rei
    list<int> &obterAmeacas();      // Obtém a lista de ameaças

private:
    vector<list<pair<int, int>>> Lista_adj;  // Representação do grafo em lista de adjacência
    vector<pair<int, int>> cavaleiros;       // Posição dos cavaleiros
    pair<int, int> rei;                      // Posição do rei
    list<int> ameacas;                       // Lista que armazena ameaças.

    bool ehValido(int x, int y);            // Verifica se a posição é válida
    int bfs(pair<int, int> inicio, pair<int, int> destino);  // Definição da BFS
    list<pair<int, int>> Movimentos_validos(int x, int y);  // Obtém movimentos válidos 
};

// Construtor para inicializar o grafo:
TabuleiroGrafo::TabuleiroGrafo()
{
    Lista_adj.resize(64);
}

// Método para adicionar um cavaleiro ao tabuleiro:
void TabuleiroGrafo::add_Cavalo(int x, int y)
{
    int vertex = x * 8 + y;
    Lista_adj[vertex].push_back({x, y});
    cavaleiros.emplace_back(x, y);
}

// Metodo para adicionar um rei ao tabuleiro:
void TabuleiroGrafo::add_Rei(int x, int y)
{
    rei = {x, y};
}

// Método para encontrar ameaças ao rei:
void TabuleiroGrafo::Ameacas()
{
    int menor = 8;
    list<int> menores;

    for (auto &cavaleiro : cavaleiros)
    {
        int movimentos = bfs(cavaleiro, rei);
        if (movimentos != -1 && movimentos < menor)
        {
            menor = movimentos;
            menores.clear();
            menores.push_back(menor);
        }
        else if (movimentos == menor)
        {
            menores.push_back(movimentos);
        }
    }

    ameacas.insert(ameacas.end(), menores.begin(), menores.end());
}

// Método para obter a lista de ameaças:
list<int> &TabuleiroGrafo::obterAmeacas()
{
    return ameacas;
}

// Método para verificar se uma posição é válida:
bool TabuleiroGrafo::ehValido(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

// BFS:
int TabuleiroGrafo::bfs(pair<int, int> inicio, pair<int, int> destino)
{
    vector<vector<bool>> visitado(8, vector<bool>(8, false));
    Queue<pair<pair<int, int>, int>> fila;

    int startVertex = inicio.first * 8 + inicio.second;
    fila.enqueue(make_pair(inicio, 0));
    visitado[inicio.first][inicio.second] = true;

    while (!fila.isEmpty())
    {
        pair<pair<int, int>, int> atual = fila.dequeue();

        if (atual.first == destino)
        {
            return atual.second;
        }

        for (auto &movimento : Movimentos_validos(atual.first.first, atual.first.second))
        {
            int nextVertex = movimento.first * 8 + movimento.second;
            if (!visitado[movimento.first][movimento.second])
            {
                fila.enqueue(make_pair(movimento, atual.second + 1));
                visitado[movimento.first][movimento.second] = true;
            }
        }
    }

    return -1;
}

// Método para obter movimentos válidos para posição:
list<pair<int, int>> TabuleiroGrafo::Movimentos_validos(int x, int y)
{
    list<pair<int, int>> movimentos = {
        {x + 1, y + 2}, {x + 1, y - 2}, {x - 1, y + 2}, {x - 1, y - 2}, {x + 2, y + 1}, {x + 2, y - 1}, {x - 2, y + 1}, {x - 2, y - 1}};

    list<pair<int, int>> movimentosValidos;
    for (auto &movimento : movimentos)
    {
        if (ehValido(movimento.first, movimento.second))
        {
            movimentosValidos.push_back(movimento);
        }
    }

    return movimentosValidos;
}

// Main:
int main()
{
    int Testes;
    cin >> Testes;

    list<int> todasAmeacas;

    for (int teste = 0; teste < Testes; ++teste)
    {
        TabuleiroGrafo tabuleiro;

        for (int i = 0; i < 4; ++i)
        {
            char coluna;
            int linha;
            cin >> coluna >> linha;

            int x = linha - 1;
            int y = coluna - 'a';
            tabuleiro.add_Cavalo(x, y);
        }

        char coluna;
        int linha;
        cin >> coluna >> linha;
        int x = linha - 1;
        int y = coluna - 'a';
        tabuleiro.add_Rei(x, y);

        tabuleiro.Ameacas();
        list<int> &ameacas = tabuleiro.obterAmeacas();
        todasAmeacas.insert(todasAmeacas.end(), ameacas.begin(), ameacas.end());
    }

    for (auto &ameaca : todasAmeacas)
    {
        cout << ameaca - 1;
    }

    return 0;
}
