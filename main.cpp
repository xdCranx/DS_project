#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Graph.hpp"
using namespace std;

//vector<vector<int>> GRAPH[vertice][edge]


int main() {

    Graph chuj("tsp.csv");
    chuj.kruskalAlg();


    return 0;
}