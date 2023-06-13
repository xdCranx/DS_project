#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Graph.hpp"
#include "HashTable.hpp"
#include "HashTableOA.hpp"

using namespace std;

//vector<vector<int>> GRAPH[vertice][edge]


int main() {

    HashTableOA HT;

    //HashTable contents
    HT.add(264115, "Alek");
    HT.add(264125, "Dominik");
    HT.add(264135, "Filip");
    HT.add(264145, "Oskar");
    HT.add(264155, "Damian");
    HT.add(264165, "Kuba");
    HT.add(264175, "Kacper");
    HT.add(264185, "Bartek");
    HT.add(264195, "Milosz");


    HT.show();
    return 0;
}