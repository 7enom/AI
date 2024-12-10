#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Graph {
public:
    Graph(int vertices);
    void addEdge(int u, int v, int cost);
    void AStar(int start, int goal, vector<int>& heuristic);

private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjList.resize(vertices);
}

void Graph::addEdge(int u, int v, int cost) {
    adjList[u].emplace_back(v, cost);
    adjList[v].emplace_back(u, cost);
}

void Graph::AStar(int start, int goal, vector<int>& heuristic) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> openSet;
    unordered_set<int> closedSet;
    unordered_map<int, int> parent;
    unordered_map<int, int> gCost; 
    int expandedNodes = 0;

    openSet.emplace(heuristic[start], start);
    gCost[start] = 0;

    while (!openSet.empty()) {
        int current = openSet.top().second;
        openSet.pop();
        expandedNodes++;
        closedSet.insert(current);

        if (current == goal) {
            vector<int> path;
            int totalCost = gCost[goal];
            while (current != start) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            cout << "Path: ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << endl;

            cout << "Total Cost: " << totalCost << endl;

            cout << "Closed Set: ";
            for (int node : closedSet) {
                cout << node << " ";
            }
            cout << endl;

            cout << "Number of Expanded Nodes: " << expandedNodes << endl;
            return;
        }
        for (const auto& neighbor : adjList[current]) {
            int nextNode = neighbor.first;
            int edgeCost = neighbor.second;
            if (closedSet.find(nextNode) != closedSet.end()) {
                continue;
            }
            int tentativeGCost = gCost[current] + edgeCost;
            if (gCost.find(nextNode) == gCost.end() || tentativeGCost < gCost[nextNode]) {
                parent[nextNode] = current;
                gCost[nextNode] = tentativeGCost;
                int fCost = tentativeGCost + heuristic[nextNode];
                openSet.emplace(fCost, nextNode);
            }
        }
    }
    cout << "No path found!" << endl;
}

int main() {
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 5, 1);
    vector<int> heuristic = {7, 6, 2, 1, 5, 0};
    int start = 0, goal = 4;
    g.AStar(start, goal, heuristic);
    return 0;
}