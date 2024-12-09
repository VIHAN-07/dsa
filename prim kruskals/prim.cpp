#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>

using namespace std;

// Function to find Minimum Spanning Tree using Prim's Algorithm
void primMST(const unordered_map<string, vector<pair<string, int>>>& adjList) {
    unordered_map<string, bool> inMST;
    priority_queue<pair<int, pair<string, string>>, vector<pair<int, pair<string, string>>>, greater<pair<int, pair<string, string>>>> edges;

    // Start from the first department
    string start = adjList.begin()->first;
    inMST[start] = true;

    // Add edges to the priority queue
    for (const auto& edge : adjList.at(start)) {
        edges.emplace(edge.second, make_pair(start, edge.first));
    }

    cout << "Edges in Minimum Spanning Tree (Prim's Algorithm):" << endl;
    while (!edges.empty()) {
        auto edge = edges.top();
        edges.pop();

        int weight = edge.first;
        string u = edge.second.first;
        string v = edge.second.second;

        if (!inMST[v]) {
            cout << u << " - " << v << " : " << weight << endl;
            inMST[v] = true;

            // Add new edges to the priority queue
            for (const auto& nextEdge : adjList.at(v)) {
                if (!inMST[nextEdge.first]) {
                    edges.emplace(nextEdge.second, make_pair(v, nextEdge.first));
                }
            }
        }
    }
}

int main() {
    // Create the graph
    unordered_map<string, vector<pair<string, int>>> campusGraph;
    campusGraph["CS"].emplace_back("EE", 10);
    campusGraph["CS"].emplace_back("ME", 15);
    campusGraph["EE"].emplace_back("ME", 5);
    campusGraph["EE"].emplace_back("CE", 20);
    campusGraph["ME"].emplace_back("CE", 25);
    campusGraph["CE"].emplace_back("MATH", 30);
    campusGraph["MATH"].emplace_back("CS", 35);

    // Find Minimum Spanning Tree using Prim's Algorithm
    primMST(campusGraph);

    return 0;
}