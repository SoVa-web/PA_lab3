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
   for(int i =0; i < row; i++)
       matrix[i] = new int[column];
   return matrix;
}

void Graph::generAdjacencyMatrix(){ 
for(int i =0; i < numberNodes ; i++){
    int k = 0;
   for(int  j =0; j < numberNodes; j++){
      if(k < maxDeegreesNode) graph[i][j] = graph[j][i] = rand()%2;
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
     if(graph[i][j] == 1) graph[i][j] = graph[j][i] = minEdge + 1 +  rand()%(maxEdge-minEdge);
   }
}
}

void Graph::startPopulation(){
    vector<int> buf;
    vector<int> person;
    bool check[numberNodes];
    for(int i =0; i < numberNodes; i++){
        check[i] = false;
    }
    check[start] = true;
  //  while (population.size() < numberPopulation){ 
     int temp = start;
     person.push_back(temp);
       while (temp != end){
          for(int i =0; i < numberNodes; i++){
              if(graph[temp][i] != 0 && !check[i]) buf.push_back(i);
          }
          if(buf.size()!= 0){
               int b = buf[0];
          for(int i =0; i < buf.size(); i++){
              if(b>= buf[i]) {
                  b = buf[i];
                  check[b] = true;
              }
          }
          buf.clear(); 
          person.push_back(b);
          temp =b;
          }else{
            person.pop_back();
            temp = person[person.size()-1];
          }
       }
       population.push_back(person);
       for(int i =0; i < person.size(); i++){
           cout<<person[i]+1<<"-->";
       }
  //  }
    
}

int main(){
    int num = 12;
    int d = 7;
  int minEdge = 5;
  int maxEdge = 150;
  Graph ggraph(1, 7);
  ggraph.generAdjacencyMatrix();
  ggraph.startPopulation();
  /*for(int i =0; i < ggraph.numberNodes ; i++){
   for(int  j =0; j < ggraph.numberNodes; j++){
      cout<<setw(4)<<ggraph.graph[i][j];
   }
   cout<<endl;
  }*/
}
