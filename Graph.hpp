#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "DisjointSet.hpp"

class Graph
{

private:
    std::vector<std::vector<int>> matrixGraph;
    std::vector<std::vector<int>> edgeList;
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

    void printEdges() {

        for (auto i : this -> edgeList)
        {
            std::cout << i[0] << " " << i[1] << " " << i[2] << std::endl;
        }
    };

    void kruskalAlg() {

        std::sort(edgeList.begin(), edgeList.end());

        DS set(VERTICES);
        int weight_sum = 0;

        for(auto edge : edgeList) {
            int weight = edge[0];
            int source = edge[1];
            int destination = edge[2];

            if(set.find(source) != set.find(destination)) {
                set.unite(source, destination);
                weight_sum += weight;
                std::cout << "From: " << source << " To: " << destination << " | Weight: " << weight << std::endl;

            }
        }
        std::cout << "Cost: " << weight_sum << std::endl;


    };

};

#endif