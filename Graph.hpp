#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <list>

#include "DisjointSet.hpp"
class Graph
{

private:
    struct Edge
    {
        int source, destination, weight;
    };

    bool mode;
    int VERTICES;

    std::vector<std::vector<int>> matrixGraph;
    std::vector<std::list<int>> listGraph;

    std::vector<Edge> edgeList;

public:
    Graph(const std::string &filename, bool co)
    {
        if (co == 1)
        {
            this->matrixGraph = loadGraphFromCSV(filename);
            this->VERTICES = matrixGraph.size();
            this->mode = co;
        }
        if (co == 0)
        {
            this->listGraph = loadGraphToAlist(filename);
            this->VERTICES = listGraph.size();
            this->mode = co;
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

    std::vector<std::list<int>> loadGraphToAlist(const std::string &filename)
    {
        std::ifstream file(filename);
        std::vector<std::list<int>> graph;

        if (!file)
        {
            std::cout << "Error opening file: " << filename << std::endl;
            return graph;
        }

        std::string line;
        while (getline(file, line))
        {
            std::list<int> node;
            std::stringstream ss(line);
            std::string edge;

            while (getline(ss, edge, ','))
            {
                if (edge == "0")
                    continue;
                else
                    node.push_back(stoi(edge));
            }

            graph.push_back(node);
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

    void print()
    {
        for (auto i : this->listGraph)
        {
            for (auto j : i)
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }

    void kruskalMST()
    {
        if (mode)
        {
            for (int node = 0; node < this->matrixGraph.size(); node++)
                for (int connection = 0; connection < this->matrixGraph[node].size(); connection++)
                {
                    if (matrixGraph[node][connection] == 0)
                        continue;
                    int source = node;
                    int destination = connection;
                    int weight = matrixGraph[node][connection];
                    edgeList.push_back({node, connection, weight});
                }
        }
        if (!mode)
        {
            for (int node = 0; node < listGraph.size(); node++)
            {
                int connection = 0;

                for (auto weight : listGraph[node])
                {
                    if (node == connection)
                    {
                        connection++;
                    }
                    edgeList.push_back({node, connection, weight});
                    connection++;
                }
            }
        }

        std::sort(edgeList.begin(), edgeList.end(), [](const Edge &edge1, const Edge &edge2)
                  {
                                                        int result = 0;
                                                        if((edge2.weight > edge1.weight) || 
                                                        ((edge2.weight == edge1.weight) && 
                                                        (edge2.destination > edge1.destination)))
                                                        {
                                                            result = 1;
                                                        }
                                                            return result; });

        DS set(VERTICES);
        int weight_sum = 0;

        for (int i = 0; i < edgeList.size(); i++)
        {
            int weight = edgeList[i].weight;
            int source = edgeList[i].source;
            int destination = edgeList[i].destination;

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
        if (mode)
        {
            while (edge_count < VERTICES - 1)
            {

                // Find minimum weight valid edge.
                int min = INT_MAX, a = -1, b = -1;
                for (int i = 0; i < VERTICES; i++)
                {
                    for (int j = 0; j < VERTICES; j++)
                    {
                        if (matrixGraph[i][j] < min)
                        {
                            if (isValidEdge(i, j, inMST))
                            {
                                min = matrixGraph[i][j];
                                a = i;
                                b = j;
                            }
                        }
                    }
                }
                if (a != -1 && b != -1)
                {
                    std::cout << "Edge " << edge_count++ <<": (" 
                    << a <<", "<< b << ") | Weight: " << min << std::endl;

                    mincost = mincost + min;
                    inMST[b] = inMST[a] = true;
                }
            }
            printf("\n Minimum cost= %d \n", mincost);
        }
        if (!mode)
        {
            while (edge_count < VERTICES - 1)
            {
                int min = INT_MAX, a = -1, b = -1;
                for (int i = 0; i < VERTICES; i++)
                {
                    int connection = 0;
                    for (auto j : listGraph[i])
                    {
                        if (i == connection)
                            connection++;
                        if (j < min)
                        {
                            if (isValidEdge(i, connection, inMST))
                            {
                                min = j;
                                a = i;
                                b = connection;
                            }
                        }
                        connection++;
                    }
                }
                if (a != -1 && b != -1)
                {
                    std::cout << "Edge " << edge_count++ <<": (" 
                    << a <<", "<< b << ") | Weight: " << min << std::endl;
                    
                    mincost = mincost + min;
                    inMST[b] = inMST[a] = true;
                }
            }
            printf("\n Minimum cost= %d \n", mincost);
        }
    };
};

#endif