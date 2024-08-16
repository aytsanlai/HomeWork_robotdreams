#pragma once
#include <vector>

class Graph {
public:
    explicit Graph(unsigned numVertices)
            : adjList(numVertices)
    {
        // Initialize the adjacency list with numVertices size
    }

    void addEdge(unsigned x, unsigned y);

    std::vector<unsigned> bfs(unsigned start, unsigned destination);

private:
    std::vector<std::vector<unsigned>> adjList;
};
