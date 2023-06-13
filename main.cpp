#include <iostream>
#include <chrono>
#include "Graph.hpp"
#include "HashTable.hpp"
#include "HashTableOA.hpp"

using namespace std;

//vector<vector<int>> GRAPH[vertice][edge]

// Graph ... ("tsp.csv", 1)- Matrix
// Graph .. ("tsp.csv", 0)- Adjacency list

int main() {

    Graph matrix("tsp.csv", 1);
    Graph list("tsp.csv", 0);
    
    cout << "\n|KRUSKAL for MATRIX|\n";
    auto s_kruskal_matrix = chrono::high_resolution_clock::now();
    matrix.kruskalMST();
    auto e_kruskal_matrix = chrono::high_resolution_clock::now();
    auto kruskal_matrix_duration = chrono::duration_cast<chrono::microseconds>(e_kruskal_matrix - s_kruskal_matrix);
    cout << "(Time: " << kruskal_matrix_duration.count() << " microsecs)\n";

    cout << "\n|KRUSKAL for LIST|\n";
    auto s_kruskal_list = chrono::high_resolution_clock::now();
    list.kruskalMST();
    auto e_kruskal_list = chrono::high_resolution_clock::now();
    auto kruskal_list_duration = chrono::duration_cast<chrono::microseconds>(e_kruskal_list - s_kruskal_list);
    cout << "(Time: " << kruskal_list_duration.count() << " microsecs)\n";


    cout << "\n|PRIM for MATRIX|\n";
    auto s_prim_matrix = chrono::high_resolution_clock::now();
    matrix.primMST();
    auto e_prim_matrix = chrono::high_resolution_clock::now();
    auto prim_matrix_duration = chrono::duration_cast<chrono::microseconds>(e_prim_matrix - s_prim_matrix);
    cout << "(Time: " << prim_matrix_duration.count() << " microsecs)\n";

    cout << "\n|PRIM for LIST|\n";
    auto s_prim_list = chrono::high_resolution_clock::now();
    list.primMST();
    auto e_prim_list = chrono::high_resolution_clock::now();
    auto prim_list_duration = chrono::duration_cast<chrono::microseconds>(e_prim_list - s_prim_list);
    cout << "(Time: " << prim_list_duration.count() << " microsecs)\n";
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