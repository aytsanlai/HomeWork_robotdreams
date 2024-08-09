#include "Graph.h"
#include <queue>
#include <unordered_map>

Graph::Graph(unsigned vertixes) : m_vertixes(vertixes) {
    m_adjacencyList.resize(vertixes);
}

void Graph::addEdge(unsigned x, unsigned y) {
    m_adjacencyList[x].push_back(y);
    m_adjacencyList[y].push_back(x);
}

std::vector<unsigned> Graph::bfs(unsigned start, unsigned destination) {
    std::vector<bool> visited(m_vertixes, false);
    std::vector<int> parent(m_vertixes, -1);

    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == destination) {
            break;
        }

        for (auto neighbor : m_adjacencyList[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    std::vector<unsigned> path;
    for (int v = destination; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    if (path[0] == start) {
        return path;
    }

    return {}; 
}
