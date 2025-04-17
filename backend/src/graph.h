#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <functional>

struct Edge {
    std::string destination;
    int distance;  // in kilometers
    int fare;      // in rupees
};

// Define EdgeInfo before using it in PathInfo
struct EdgeInfo {
    std::string destination;
    int distance;
    int fare;
};

struct PathInfo {
    std::vector<std::string> path;
    int totalDistance;
    int totalFare;
    std::vector<EdgeInfo> edges;  // Now EdgeInfo is already defined
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    std::vector<std::string> cities;

public:
    Graph();
    void addCity(const std::string& city);
    void addEdge(const std::string& source, const std::string& destination, int distance, int fare);
    PathInfo findShortestPath(const std::string& source, const std::string& destination, bool byDistance);
    std::vector<std::string> getCities() const;
    std::unordered_map<std::string, std::vector<Edge>> getAdjacencyList() const;
};

#endif // GRAPH_H