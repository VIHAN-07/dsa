#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>

using namespace std;

class DisjointSet {
public:
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;

    void makeSet(const string& v) {
        parent[v] = v;
        rank[v] = 0;
    }

    string find(const string& v) {
        if (parent[v] != v) {
            parent[v] = find(parent[v]); // Path compression
        }
        return parent[v];
    }

    void unionSets(const string& u, const string& v) {
        string rootU = find(u);
        string rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Function to find Minimum Spanning Tree using Kruskal's Algorithm
void kruskalMST(const unordered_map<string, vector<pair<string, int>>>& adjList) {
    vector<tuple<int, string, string>> edges;

    // Create a list of edges
    for (const auto& pair : adjList) {
        const string& u = pair.first;
        for (const auto& edge : pair.second) {
            const string& v = edge.first;
            int weight = edge.second;
            edges.emplace_back(weight, u, v);
        }
    }

    // Sort edges based on weight
    sort(edges.begin(), edges.end());

    DisjointSet ds;
    for (const auto& pair : adjList) {
        ds.makeSet(pair.first);
    }

    cout << "Edges in Minimum Spanning Tree (Kruskal's Algorithm):" << endl;
    for (const auto& edge : edges) {
        int weight;
        string u, v;
        tie(weight, u, v) = edge;

        if (ds.find(u) != ds.find(v)) {
            ds.unionSets(u, v);
            cout << u << " - " << v << " : " << weight << endl;
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

    // Find Minimum Spanning Tree using Kruskal's Algorithm
    kruskalMST(campusGraph);

    return 0;
}