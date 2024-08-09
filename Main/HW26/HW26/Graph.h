#pragma once
#include <vector>
#include <list>

class Graph {
public:
    
    Graph(unsigned numVertices);

  
    void addEdge(unsigned x, unsigned y);

   
    std::vector<unsigned> bfs(unsigned start, unsigned destination);

private:
    unsigned m_vertixes;                  
    std::vector<std::list<int>> m_adjacencyList; 
};
