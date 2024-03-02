#include <iostream>
#include <list>


using namespace std;

class Horse{
private:
int x;
int y;
list<pair<int, int>> adj;
public:
Horse(string pos);
};

Horse::Horse(string pos){
     x = static_cast<int>(pos[0]) - 64;
     y = static_cast<int>(pos[1] - '0');
     int movimentos[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

      for (int i = 0; i < 8; ++i) {
        int novaX = x + movimentos[i][0];
        int novaY = y + movimentos[i][1];

        // Verifica se a nova posição está dentro dos limites do tabuleiro (8x8)
        if (novaX >= 1 && novaX <= 8 && novaY >= 1 && novaY <= 8) {
            adj.push_back(make_pair(novaX, novaY));
        }
    }

}


class King{
    private:
    int x;
    int y;
    public:
    King(string pos);
};

King::King(string pos){
     x = static_cast<int>(pos[0]) - 64;
     y = static_cast<int>(pos[1] - '0');
}


class Table{
    
}




int main(){

    return 0;
}