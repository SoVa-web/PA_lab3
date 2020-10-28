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
  void crossover();
  vector<int> potentialCross(vector<int> a, vector<int> b); 
  void mutation();
  void better();
  void funcDef();
  int minInPop();
  int maxInPop();
  


  //variaties
  int start;
  int end;
  int numberNodes = 25;
  int maxDeegreesNode = 10;
  int minEdge = 5;
  int maxEdge = 150;
  int nuumberPoints  = 2;
  int numberMutation = 2;
  int numberBetter = 2;
  int**graph;
  vector<vector<int>> population;
  int* funcMin;
  int record =0;

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
  funcMin = new int[population.size()];
  funcDef();
  record = minInPop();
}

void Graph::funcDef(){
   int sum;
   for(int i =0; i < population.size(); i++){
     sum = 0;
     for(int j =0; j < population[i].size()-1; j++){
       sum+=graph[population[i][j]][population[i][j+1]];
     }
     funcMin[i] = sum;
   }
}

int Graph::minInPop(){
  int minimum = funcMin[0];
  int index;
  for(int i =0; i < population.size(); i++){
    if(minimum >= funcMin[i]){
        minimum = funcMin[i];
        index = i;
    }
  }
  return index;
}

int Graph::maxInPop(){
int maximum = funcMin[0];
int index;
  for(int i =0; i < population.size(); i++){
    if(maximum <= funcMin[i]){
      maximum = funcMin[i];
    index = i;
    }
  }
  return index;
}

void Graph::crossover(){
   for(int i =0; i < population.size(); i++){
    cout<<funcMin[i]<<"-";
  }
  cout<<endl;
  int firstParent = maxInPop();
  cout<<"max"<<firstParent<<endl;
  int secondParent = minInPop();  
  cout<<"min"<<secondParent<<endl;
  vector<int> firstSet = potentialCross(population[firstParent], population[secondParent]);//непарні від макс
  vector<int> secondSet = potentialCross(population[secondParent], population[firstParent]);//парні від макс
  /*for(int i =0; i < firstSet.size(); i++)
   cout<<firstSet[i]<<"  ";
   cout<<"firstSet"<<endl;
  for(int j =0; j < secondSet.size(); j++){
    cout<<secondSet[j]<<"  ";
  }
  cout<<"secod"<<endl;*/
}

vector<int> Graph::potentialCross(vector<int> a, vector<int> b){
  int finish =1;
  vector<int> res;
  for(int i =1; i < a.size()-1; i++){
    for(int j = finish; j < b.size()-1; j++){
       if(a[i] == b[j]){
         res.push_back(i);
         res.push_back(j);
         finish = j+1;
         break;
       }
    }
  }
  return res;
}

int main(){
  Graph ggraph(1, 7);
  ggraph.generAdjacencyMatrix();
  ggraph.funcDef();
  for(int i =0; i < ggraph.population.size(); i++){
    for(int j =0; j < ggraph.population[i].size(); j++){
      cout<<ggraph.population[i][j]<<"-->";
    }
    cout<<endl;
  }
  ggraph.crossover();
  /*for(int i =0; i < ggraph.numberNodes ; i++){
   for(int  j =0; j < ggraph.numberNodes; j++){
      cout<<setw(4)<<ggraph.graph[i][j];
   }
   cout<<endl;
  }*/
}
