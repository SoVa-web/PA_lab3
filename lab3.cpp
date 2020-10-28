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
  Graph(int s, int e);
  int** initMatrix(int**matrix, int row, int columns);
  void generAdjacencyMatrix();
  void startPopulation();


  //variaties
  int start;
  int end;
  int numberNodes = 12;
  int maxDeegreesNode = 8;
  int minEdge = 5;
  int maxEdge = 150;
  int**graph;
  vector<vector<int>> population;
  int numberPopulation = 2;

};

Graph:: Graph(int s, int e){
    start = s-1;
    end = e-1;
    graph = initMatrix(graph, numberNodes, numberNodes);
}

int** Graph::initMatrix(int**matrix, int row, int column){
   srand(time(NULL));
   matrix = new int*[row];
   for(int i =0; i < row; i++) matrix[i] = new int[column];
   for(int i =0; i < row; i++){
     for(int j =0; j < column; j++) matrix[i][j] = 0;
   }
   return matrix;
}

void Graph::generAdjacencyMatrix(){ 
  int arrNumber[numberNodes];
  vector<int> person;
  for(int i =0; i < numberNodes; i++) arrNumber[i] = i;
  int count;
  if(maxDeegreesNode/2 >2 ) count = maxDeegreesNode/2; else count = 2;
  for(int i =0; i < maxDeegreesNode/2; i++){
     for (int j = 0; j < numberNodes/2; j++){
        int a = rand()%numberNodes;//місця які міняємо
        int b =  rand()%numberNodes;
        int c = arrNumber[a];
        arrNumber[a] = arrNumber[b];
        arrNumber[b] = c;
     }
     for(int j =0; j < numberNodes-1; j++)
       graph[arrNumber[j]][arrNumber[j+1]] = graph[arrNumber[j+1]][arrNumber[j]] = minEdge+1+rand()%(maxEdge-minEdge);
     for(int j =0; j < numberNodes; j++)
       cout<<arrNumber[j]<<"--";
     cout<<endl;
     int indexS =0,  indexE = 0;
     for (int j = 0; j < numberNodes; j++){
      if (arrNumber[j] == start)indexS = j;
      if ( arrNumber[j] == end)indexE = j;
     }
     if(indexE > indexS){
        person.push_back(arrNumber[indexS]);
        while (indexE != indexS){
          indexS++;
          person.push_back(arrNumber[indexS]);
        }
     }else{
         person.push_back(arrNumber[indexS]);
        while (indexE != indexS){
          indexS--;
          person.push_back(arrNumber[indexS]);
        }
     }
     population.push_back(person);
     person.clear();
  }
}

void Graph::startPopulation(){
   
}

int main(){
  Graph ggraph(1, 7);
  ggraph.generAdjacencyMatrix();
  for(int i =0; i < ggraph.population.size(); i++){
    for(int j =0; j < ggraph.population[i].size(); j++){
      cout<<ggraph.population[i][j]<<"-->";
    }
    cout<<endl;
  }
  for(int i =0; i < ggraph.numberNodes ; i++){
   for(int  j =0; j < ggraph.numberNodes; j++){
      cout<<setw(4)<<ggraph.graph[i][j];
   }
   cout<<endl;
  }
}
