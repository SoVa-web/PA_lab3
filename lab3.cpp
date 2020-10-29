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
  bool alive(vector<int> ch);
  void funcDef();
  int minInPop();
  int maxInPop();
  
  //variaties
  int start;
  int end;
  int numberNodes = 300;
  int maxDeegreesNode = 15;
  int minEdge = 5;
  int maxEdge = 150;
  int nuumberPoints  = 1;
  int numberMutation = 1;
  int numberBetter = 1;
  int**graph;
  vector<vector<int>> population;
  int* funcMin;
  int record =0;
  vector<int> person;
  vector<int> firstSet;
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
  int firstParent = maxInPop(), secondParent = minInPop();  
   firstSet = potentialCross(population[firstParent], population[secondParent]);
  if(firstSet.size()/2 >= nuumberPoints){
    vector<int> ch1, ch2, buf;
    int t =1, k =1;
     ch1.push_back(start);
     ch2.push_back(start);
    for (int i = 0; i < nuumberPoints; i++){
      while (t <= firstSet[2*i]){
        ch1.push_back(population[firstParent][t]);
        t++;
      }
      while (k <= firstSet[2*i+1]){
        ch2.push_back(population[secondParent][k]);
       k++;
      }
      buf = ch1;
      ch1 = ch2;
      ch2 = buf;
    }
     while (t != population[firstParent].size()){
        ch1.push_back(population[firstParent][t]);
        t++;
      }
      while (k != population[secondParent].size()){
        ch2.push_back(population[secondParent][k]);
       k++;
      }
      bool areYouAlive1, areYouAlive2;
      areYouAlive1 = alive(ch1);
      areYouAlive2 = alive(ch2);
      int func1=0, func2=0;
      for(int j =0; j < ch1.size()-1; j++){
       func1+=graph[ch1[j]][ch1[j+1]];
      }
      for(int j =0; j < ch2.size()-1; j++){
       func2+=graph[ch2[j]][ch2[j+1]];
      }
      if(areYouAlive1){
        int index = maxInPop();
        if(funcMin[index] > func1)
        population[index] = ch1;
      }
      funcDef();
       if(areYouAlive2){
        int index = maxInPop();
        if(funcMin[index] > func2)
        population[index] = ch2;
      }
      funcDef();
  }
  firstSet.clear();
}

bool Graph::alive(vector<int> ch){
   bool areYouAlive1;
      for(int i =0; i < ch.size(); i++){//винести в функцію
       for(int j =0; j <ch.size(); j++){
          if(i != j && ch[i] == ch[j]){
            areYouAlive1 = false;
            break;
          }else{
            areYouAlive1 = true;
          }
       }
       if(!areYouAlive1)
       break;
      }
      return areYouAlive1;
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

/*void Graph::mutation(){
}*/

void Graph::better(){
    for (int i = 0; i < population.size(); i++)
        for (int j = 2; j < population[i].size(); j++)
            if (graph[population[i][j - 2]][population[i][j]] != 0 &&
                graph[population[i][j - 2]][population[i][j]] < graph[population[i][j - 2]][population[i][j - 1]] + graph[population[i][j - 1]][population[i][j]])
            {
                population[i].erase(population[i].begin() + j - 1);
                j--;
            }
funcDef();
}

int main(){
  Graph ggraph(1, 7);
  ggraph.generAdjacencyMatrix();
  ggraph.funcDef();
   cout<<"Graph : "<<endl;
  /*for(int i =0; i < ggraph.numberNodes ; i++){
   for(int  j =0; j < ggraph.numberNodes; j++){
      cout<<setw(4)<<ggraph.graph[i][j];
   }
   cout<<endl;
  }*/
  int index =0;
  for(int i =0; i < 20; i++){
     ggraph.crossover();
 for(int i =0; i < ggraph.numberMutation; i++){
   //ggraph.mutation();
 }
 for(int i =0; i < ggraph.numberBetter; i++){
   ggraph.better();
 }
 ggraph.funcDef();
  index = ggraph.minInPop();
  cout<<" Вага : "<<ggraph.funcMin[index]<<endl;
  cout<<" Шлях : "<<endl;
  for(int i =0; i < ggraph.population[index].size(); i++){
    cout<< ggraph.population[index][i]<<"-->";
  }
  cout<<endl;
  }
}
