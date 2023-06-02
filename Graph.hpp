#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>

#include "DisjointSet.hpp"

class Graph
{

private:
    struct Edge
    {
        int source, destination, weight;

    };

    std::vector<std::vector<int>> matrixGraph;
    std::vector<Edge> edgeList;
    int VERTICES;

public:
    Graph(const std::string &filename)
    {
        this->matrixGraph = loadGraphFromCSV(filename);
        this->VERTICES = matrixGraph.size();
        // EDGE_LIST - {weight, source, destination}

        for (int node = 0; node < this->matrixGraph.size(); node++)
            for (int connection = 0; connection < this->matrixGraph[node].size(); connection++)
            {
                if (matrixGraph[node][connection] == 0)
                    continue;
                edgeList.push_back({this->matrixGraph[node][connection], node, connection});
            }
    };
    ~Graph(){};

    std::vector<std::vector<int>> loadGraphFromCSV(const std::string &filename)
    {
        std::ifstream file(filename);
        std::vector<std::vector<int>> graph;

        if (!file)
        {
            std::cout << "Error opening file: " << filename << std::endl;
            return graph;
        }

        std::string line;
        while (getline(file, line))
        {
            std::vector<int> vertice;
            std::stringstream ss(line);
            std::string edge;

            while (getline(ss, edge, ','))
            {
                vertice.push_back(stoi(edge));
            }

            graph.push_back(vertice);
        }

        file.close();

        return graph;
    };

    void printEdges()
    {

        for (auto i : this->edgeList)
        {
            std::cout << i.weight << " " << i.source << " " << i.destination << std::endl;
        }
    };

    void kruskalMST()
    {

        std::sort(edgeList.begin(), edgeList.end());

        DS set(VERTICES);
        int weight_sum = 0;

        for (auto edge : edgeList)
        {
            int weight = edge.weight;
            int source = edge.source;
            int destination = edge.destination;

            if (set.find(source) != set.find(destination))
            {
                set.unite(source, destination);
                weight_sum += weight;
                std::cout << "From: " << source << " To: " << destination << " | Weight: " << weight << std::endl;
            }
        }
        std::cout << "Cost: " << weight_sum << std::endl;
    };

    bool isValidEdge(int u, int v, std::vector<bool> inMST)
    {
        if (u == v)
            return false;
        if (inMST[u] == false && inMST[v] == false)
                return false;
        else if (inMST[u] == true && inMST[v] == true)
                return false;
        return true;
    };
    

    void primMST()
    { 
        std::vector<bool> inMST(VERTICES, false);
    
        // Include first vertex in MST
        inMST[0] = true;
    
        // Keep adding edges while number of included
        // edges does not become V-1.
        int edge_count = 0, mincost = 0;
        while (edge_count < VERTICES - 1) {
    
            // Find minimum weight valid edge. 
            int min = INT_MAX, a = -1, b = -1;
            for (int i = 0; i < VERTICES; i++) {
                for (int j = 0; j < VERTICES; j++) {              
                    if (matrixGraph[i][j] < min) {
                        if (isValidEdge(i, j, inMST)) {
                            min = matrixGraph[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
            if (a != -1 && b != -1) {
                printf("Edge %d:(%d, %d) cost: %d \n",
                            edge_count++, a, b, min);
                mincost = mincost + min;
                inMST[b] = inMST[a] = true;
            }
        }
        printf("\n Minimum cost= %d \n", mincost);
    };

};

#endif