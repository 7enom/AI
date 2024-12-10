#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_set>
#include <utility>
using namespace std;
class Graph {
public:
    Graph(int vertices);
    void addEdge(int u, int v, int cost);
    void DFS(int start, int goal);

private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;
    void DFSUtil(int node, int goal, unordered_set<int>& closedSet, stack<int>& pathStack, int& totalCost, int& expandedNodes);
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjList.resize(vertices);
}

void Graph::addEdge(int u, int v, int cost) {
    adjList[u].emplace_back(v, cost);
    adjList[v].emplace_back(u, cost);
}

void Graph::DFS(int start, int goal) {
    vector<int> FPath, FColsedsect;
    unordered_set<int> closedSet;
    stack<int> pathStack;
    int totalCost = 0, expandedNodes = 0;

    pathStack.push(start);
    DFSUtil(start, goal, closedSet, pathStack, totalCost, expandedNodes);

    cout << "Path: ";
    while (!pathStack.empty()) {
        FPath.push_back(pathStack.top());
        pathStack.pop();
    }
    reverse(FPath.begin(), FPath.end());
    for(auto ver : FPath) {
        cout << ver << " ";
    }
    cout << endl;

    cout << "Total Cost: " << totalCost << endl;
    cout << "Closed Set: ";
    for (const auto& node : closedSet) {
        FColsedsect.push_back(node);
    }
    reverse(FColsedsect.begin(), FColsedsect.end());
    for(auto closeout : FColsedsect) {
        cout << closeout << " ";
    }
    cout << endl;
    cout << "Number of Expanded Nodes: " << expandedNodes << endl;
}

void Graph::DFSUtil(int node, int goal, unordered_set<int>& closedSet, stack<int>& pathStack, int& totalCost, int& expandedNodes) {
    closedSet.insert(node);
    expandedNodes++;

    if (node == goal) {
        totalCost = 0;
        stack<int> tempStack = pathStack;
        int prevNode = -1;

        while (!tempStack.empty()) {
            int currentNode = tempStack.top();
            tempStack.pop();
            if (prevNode != -1) {
                for (const auto& neighbor : adjList[prevNode]) {
                    if (neighbor.first == currentNode) {
                        totalCost += neighbor.second;
                        break;
                    }
                }
            }
            prevNode = currentNode;
        }
        return;
    }

    for (const auto& neighbor : adjList[node]) {
        int nextNode = neighbor.first;
        if (closedSet.find(nextNode) == closedSet.end()) {
            pathStack.push(nextNode);
            DFSUtil(nextNode, goal, closedSet, pathStack, totalCost, expandedNodes);
            if (totalCost > 0) {
                return;
            }
            pathStack.pop();
        }
    }
}

int main() {
    Graph g(6);
    g.addEdge(0, 1, 5); 
    g.addEdge(0, 2, 2); 
    g.addEdge(1, 3, 3); 
    g.addEdge(1, 4, 4); 
    g.addEdge(2, 5, 1);
    int star, goal;
    star = 0, goal = 5;
    g.DFS(star, goal);
    return 0;
}