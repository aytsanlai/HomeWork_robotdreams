#include "Graph.h"
#include <queue>
#include <algorithm>
#include <vector>

void Graph::addEdge(unsigned x, unsigned y)
{
    // Add an edge from x to y
    adjList[x].emplace_back(y);
    adjList[y].emplace_back(x);
}

std::vector<unsigned> Graph::bfs(unsigned start, unsigned destination)
{
    std::vector<bool> visited(adjList.size(), false);
    std::vector<unsigned> predecessor(adjList.size(), -1);

    std::queue<unsigned> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        const unsigned current = q.front();
        q.pop();

        if (current == destination) {
            // Reconstruct the path from start to destination
            std::vector<unsigned> path;
            for (unsigned at = destination; at != -1; at = predecessor[at]) {
                path.emplace_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const unsigned neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                predecessor[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    return {}; // Return an empty path if no path is found
}
