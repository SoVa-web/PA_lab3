#include<iostream>
#include<ctime>
#include<random>
#include<iomanip>
#include<vector>
#include<cmath>

using namespace std;

class Graph{
    public:
  //prototypes
  Graph(int n, int deegree, int minE, int maxE);
  int** initMatrix(int**matrix, int row, int columns);
  void generAdjacencyMatrix();

  //variaties
  int numberNodes;
  int maxDeegreesNode;
  int minEdge;
  int maxEdge;
  int**graph;

};

Graph:: Graph(int n, int deegree, int minE, int maxE){
    numberNodes = n;
    maxDeegreesNode = deegree;
    minEdge = minE;
    maxEdge = maxE;
    graph = initMatrix(graph, n, n);
}

int** Graph::initMatrix(int**matrix, int row, int column){
   srand(time(NULL));
   matrix = new int*[row];
   for(int i =0; i < row; i++){
       matrix[i] = new int[column];
   }
   return matrix;
}

void Graph::generAdjacencyMatrix(){
for(int i =0; i < numberNodes ; i++){
    int k = 0;
   for(int  j =0; j < numberNodes; j++){
      if(k < maxDeegreesNode-1) graph[i][j] = graph[j][i] = rand()%2;
      else  graph[i][j] = graph[j][i] = 0;
      if(graph[i][j] != 0) k++;
      if(i == j) graph[i][j] = 0;
   }
}
for(int i =0; i < numberNodes-1; i++){
   graph[i][i+1] =  graph[i+1][i] = 1;
}
for(int i =0; i < numberNodes ; i++){
   for(int  j =0; j < numberNodes; j++){
     if(graph[i][j] == 1){
         graph[i][j] = graph[j][i] = minEdge + 1 +  rand()%(maxEdge-minEdge);
     }
   }
}

}

int main(){
    int num = 7;
    int d = 4;
  int minEdge = 5;
  int maxEdge = 150;
  Graph ggraph(num, d, minEdge, maxEdge);
  ggraph.generAdjacencyMatrix();
  for(int i =0; i < ggraph.numberNodes ; i++){
   for(int  j =0; j < ggraph.numberNodes; j++){
      cout<<setw(4)<<ggraph.graph[i][j];
   }
   cout<<endl;
}
}
