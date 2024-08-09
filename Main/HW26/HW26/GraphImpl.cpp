#include <iostream>
#include <vector>
#include <list>
class Graph
{
public:
    Graph(unsigned vertixes) : m_vertixes(vertixes)
    {
        m_adjacencyList.resize(vertixes);
    }

    //undirected
    //TODO: Validate if not already added
    void addEdge(unsigned from, unsigned to)
    {
        m_adjacencyList[from].push_back(to);
        m_adjacencyList[to].push_back(from);
    }

    void dfs(int vertex)
    {
        std::vector<bool> visited;
        visited.resize(m_vertixes, false);

        dfsImpl(vertex, visited);
    }

    void dfsImpl(int vertex, std::vector<bool>& visited)
    {
        visited[vertex] = true;
        std::cout << vertex << " -> ";

        for (unsigned vertexCurrent : m_adjacencyList[vertex])
        {
            if (!visited[vertexCurrent])
                dfsImpl(vertexCurrent, visited);
        }
    }

private:
    std::vector<std::list<int>> m_adjacencyList;
    unsigned m_vertixes = 0;
};

int main()
{
    Graph myGraph(10);

    myGraph.addEdge(0, 1);
    myGraph.addEdge(0, 2);
    myGraph.addEdge(0, 3);
    myGraph.addEdge(1, 4);
    myGraph.addEdge(4, 8);
    myGraph.addEdge(2, 5);
    myGraph.addEdge(2, 6);
    myGraph.addEdge(5, 9);
    myGraph.addEdge(3, 7);

    myGraph.dfs(0);
}
