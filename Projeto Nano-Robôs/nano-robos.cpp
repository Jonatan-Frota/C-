#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <vector>

#define INT_MAX 9999

using namespace std;

typedef unsigned int Vertex;
typedef float Distance, Weight;

class MinimumPQ {
public:
    vector<Vertex> heap;
    int lenHeap;

    MinimumPQ(const vector<Vertex>& array) : heap(array), lenHeap(array.size()) {
        buildminHeap();
    }

    int parent(int i) {
        return i / 2;
    }

    int left(int i) {
        return 2 * i;
    }

    int right(int i) {
        return 2 * i + 1;
    }

    void hepify(int i) {
        int l = left(i);
        int r = right(i);
        int minor = i;

        if (l < lenHeap && heap[l] < heap[minor]) {
            minor = l;
        }

        if (r < lenHeap && heap[r] < heap[minor]) {
            minor = r;
        }

        if (minor != i) {
            unsigned int aux = heap[i];
            heap[i] = heap[minor];
            heap[minor] = aux;
            hepify(minor);
        }
    }

    void buildminHeap() {
        for (int i = lenHeap / 2 - 1; i >= 0; --i) {
            hepify(i);
        }
    }

    int min() const {
        if (lenHeap >= 1) {
            return heap[0];
        } else {
            return -1; 
        }
    }

    Vertex extractmin() {
        if (lenHeap >= 1) {
            Vertex minVal = heap[0];
            heap[0] = heap[lenHeap - 1];
            lenHeap--;
            hepify(0);
            return minVal;
        } else {
            // Return an appropriate default value for Vertex when the heap is empty
            return Vertex(); 
        }
    }

    void decreaseKey(int i, unsigned int k) {
        if (i >= 0 && i < lenHeap) {
            heap[i] = k;
            while (i > 0 && heap[parent(i)] > heap[i]) {
                unsigned int aux = heap[i];
                heap[i] = heap[parent(i)];
                heap[parent(i)] = aux;
                i = parent(i);
            }
        }
    }

    void insert(int key) {
        lenHeap++;
        heap.push_back(INT_MAX); 
        decreaseKey(lenHeap - 1, key);
    }

    void displayArray() {
        cout << "heap: ";
        for (int i = 0; i < lenHeap; i++) {
            cout << heap[i] << " ";
        }
        cout << "\n";
    }
};

class UnionFind {
public:
    vector<int> parent, h;

    UnionFind(int n) : parent(n), h(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;  // Initialize parent to individual nodes
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);  // Path compression for optimization
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (h[rootU] < h[rootV]) {
                parent[rootU] = rootV;
            } else if (h[rootU] > h[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootU] = rootV;
                h[rootV]++;
            }
        }
    }
};

class Neuron{
public:
	Vertex vertexNum;
	Weight weight;
	Neuron() {};
	Neuron(Vertex _vertexNum, Weight _weight): vertexNum(_vertexNum), weight(_weight) {};
	
};

class NeuronBlock {
private:
    unsigned int numVertices;
    unsigned int numEdges;
	unsigned int numBadNeuron;
    Vertex vertexNum;
	Weight weight;
    NeuronBlock* pred;

public:
    vector<vector<Neuron>> listAdjNeur;
    NeuronBlock();
    NeuronBlock(unsigned int, Vertex, Weight, NeuronBlock*);
    void addEdge(Vertex u, Vertex v, Weight p);

    vector<Neuron> getAdj(Vertex v) { return listAdjNeur[v]; }
	unsigned int getNumVertices() const { return numVertices; }
	unsigned int getNumEdges() const { return numEdges; }
	Vertex getVertexNum() const { return vertexNum; }
	unsigned int getNumBadDoentes() const { return numBadNeuron; }
	Weight getWeight() const { return weight; }
	NeuronBlock* getPred()  { return pred; }

	void setNumVertices(unsigned int _numVertices) { numVertices = _numVertices; }
	void setNumEdges(unsigned int _numEdges) { numEdges = _numEdges; }
	void setNumBadNeuron(unsigned int _numBadNeuron) { numBadNeuron = _numBadNeuron; }
	void setPred(NeuronBlock* _bloco) { pred = _bloco; }
	void setVertexNum(Vertex _vertexNum) { vertexNum = _vertexNum; }
	
};

NeuronBlock::NeuronBlock() : numVertices(0), numEdges(0), numBadNeuron(0), vertexNum(0), weight(0.0), pred(nullptr) {}

NeuronBlock::NeuronBlock(unsigned int _numVertices, Vertex _vertexNum, Weight _weight, NeuronBlock* _pred):numVertices(_numVertices), vertexNum(_vertexNum), weight(_weight), pred(_pred), listAdjNeur(_numVertices) {}

void NeuronBlock::addEdge(Vertex u, Vertex v, Weight w) {
	Neuron n1{v, w};
	listAdjNeur[u-1].push_back(n1);	
	Neuron n2{u, w};
	listAdjNeur[v-1].push_back(n2);	
	numEdges++;
}

class Brain {
private:
    unsigned int numVertices;
    unsigned int numEdges;
    vector<Distance> distanceVector;
    Vertex StartNeuronBlock;
    Vertex EndNeuronBlock;

public:
    
	vector<NeuronBlock>* listAdjBrain;
    Brain(unsigned int numVertices);
    void addEdge(Vertex u, Vertex v, Weight p);
    vector<NeuronBlock> getAdj(Vertex v) { return listAdjBrain[v]; }
	unsigned int getNumVertices() { return numVertices; }
	unsigned int getNumEdges() { return numEdges; }
    NeuronBlock& getNeuronBlock(Vertex u) {return listAdjBrain[0][u-1];}
    Vertex getStart() {return StartNeuronBlock;}
    Vertex getEnd() {return EndNeuronBlock;}
    void setDistancias(Vertex pos, Distance d) {distanceVector[pos] = d;}
    Distance getDistance(Vertex pos) {return distanceVector[pos];}

	void setNeuronBlockStart(Vertex _StartNeuronBlock) { StartNeuronBlock = _StartNeuronBlock; }
	void setNeuronBlockEnd(Vertex _EndNeuronBlock) { EndNeuronBlock = _EndNeuronBlock; }
};

Brain::Brain(unsigned int _numVertices): numVertices(_numVertices), distanceVector(_numVertices) {
	listAdjBrain = new vector<NeuronBlock>[numVertices+1];
	listAdjBrain[0].resize(numVertices);
}

void Brain::addEdge(Vertex u, Vertex v, Weight w) {
	NeuronBlock nb1{0, v, w, nullptr};
	listAdjBrain[u].push_back(nb1);	
	NeuronBlock nb2{0, u, w, nullptr};
	listAdjBrain[v].push_back(nb2);	
	numEdges++;
	listAdjBrain[0][u-1] = nb2;
	listAdjBrain[0][v-1] = nb1;
}

void inputBrain(Brain &brain, unsigned int numEdges) {
	//input dos blocos de neuronio
    Vertex u = 0, v = 0;
	Weight p = 0;

	for (unsigned int i = 0; i < numEdges; ++i) {
		cin >> u >> v >> p;
		brain.addEdge(u, v, p);

	}

    //definindo entrada e saida do cerebro
	cin >> u >> v;
	brain.setNeuronBlockStart(u);
	brain.setNeuronBlockEnd(v);

	//input dos neuronios
    unsigned int n;
	n = brain.getNumVertices();

	for (unsigned int i = 0; i < n; i++) {
		NeuronBlock& block = brain.listAdjBrain[0][i];
		unsigned int numVertices, numEdges, numBadNeuron;
        Vertex u = 0, v = 0;
        Weight w = 0;

        cin >> numVertices >> numEdges;
        cin >> numBadNeuron;

        block.setNumEdges(numEdges);
        block.setNumVertices(numVertices);
        block.setNumBadNeuron(numBadNeuron);
        block.listAdjNeur.resize(numVertices);

        for (unsigned int i = 0; i < numBadNeuron; ++i) {
            cin >> u;
        }

        for (unsigned int i = 0; i < numEdges; ++i) {
            cin >> u >> v >> w;
            block.addEdge(u, v, w);

        }
	}

}

void relaxBrain(Brain& brain, Vertex u, Vertex v, Weight weight, MinimumPQ& Q ) {
    NeuronBlock& bl1 = brain.getNeuronBlock(u);
    NeuronBlock& bl2 = brain.getNeuronBlock(v);

    if (brain.getDistance(v-1) > brain.getDistance(u-1) + weight) {
        brain.setDistancias(bl2.getVertexNum()-1, brain.getDistance(u-1) + weight);
        bl2.setPred(&bl1);
        Q.insert(bl2.getVertexNum());

    }
}

void djikstra(Brain& brain, NeuronBlock& blockInitial){
	Vertex init = blockInitial.getVertexNum();

    for (unsigned i = 0; i <= brain.getNumVertices(); i++){
        for(auto& blockInitial : brain.listAdjBrain[i] ){
        brain.setDistancias(blockInitial.getVertexNum()-1, INT_MAX);
        blockInitial.setPred(nullptr);
        }
    }
    brain.setDistancias(init-1, 0);

    vector<Vertex> S(1, init);
	MinimumPQ Q(S);

    while (Q.min() != -1) {

        Vertex u = Q.extractmin();

        for (NeuronBlock v : brain.getAdj(u)) {
            Weight weight = v.getWeight();
            relaxBrain(brain, u, v.getVertexNum(), weight, Q);
        }
    }
    
}

Weight kruskal(NeuronBlock& blockInitial) {

    vector<pair<Vertex, pair<Vertex, Weight>>> weight_vector;
    for (unsigned int i = 0; i < blockInitial.getNumVertices(); i++){
        for (auto& aresta : blockInitial.listAdjNeur[i]){
            pair<Vertex, pair<Vertex, Weight>> aux;
            Vertex u = i+1;
            Vertex v = aresta.vertexNum;
            Weight w = aresta.weight;
            aux.first = u;
            aux.second.first = v;
            aux.second.second = w;
            weight_vector.push_back(aux);
        }
    }
    
    pair<Vertex, pair<Vertex, Weight>> aux;
    for (unsigned int i = 0; i < weight_vector.size(); i++){
        for (unsigned int j = 0; j < weight_vector.size() -i -1; j++){
            if (weight_vector[j].second.second > weight_vector[j+1].second.second){
                aux = weight_vector[j];
                weight_vector[j] = weight_vector[j+1];
                weight_vector[j+1] = aux;
            }
        }
    }

    vector<pair<Vertex, pair<Vertex, Weight>>> mst;

    UnionFind uf(blockInitial.getNumVertices() + 1);

    for (const pair<Vertex, pair<Vertex, Weight>>& aresta : weight_vector) {
        Vertex u = aresta.first;
        Vertex v = aresta.second.first;

        int rootU = uf.find(u);
        int rootV = uf.find(v);

        if (rootU != rootV) {
            mst.push_back(aresta);
            uf.unite(rootU, rootV);
        }
    }

    Weight len = 0;
    for (unsigned int i = 0; i < mst.size(); i++) {
        len += mst[i].second.second;
    }

    return len;
}

void totalDistance(Brain& brain){

    Vertex end = brain.getEnd();
    NeuronBlock endBlock = brain.getNeuronBlock(end);

    NeuronBlock* aux = &endBlock;

    int distance = 0;

    while (aux != nullptr) {

        if(aux->getNumBadDoentes() != 0) {
            distance += kruskal(*aux);

        }

        aux = aux->getPred();
    }

    cout << distance;
}

int main(){

   	unsigned int numVertices = 0;
	unsigned int numEdges = 0;
	cin >> numVertices >> numEdges;
	
	Brain brain{numVertices};
	inputBrain(brain, numEdges);

    Vertex start = brain.getStart();
    NeuronBlock startBlock = brain.getNeuronBlock(start);
    djikstra(brain, startBlock);

    totalDistance(brain);

}