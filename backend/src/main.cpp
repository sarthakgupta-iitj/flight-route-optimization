// main.cpp
#include <iostream>
#include "graph.h"

int main() {
    // Create graph
    Graph graph;
    
    // Example usage
    std::string source = "Delhi";
    std::string destination = "Mumbai";
    
    // Find shortest path by distance
    PathInfo pathByDistance = graph.findShortestPath(source, destination, true);
    
    std::cout << "Shortest path from " << source << " to " << destination << " by distance:\n";
    for (const auto& city : pathByDistance.path) {
        std::cout << city;
        if (city != destination) std::cout << " -> ";
    }
    std::cout << "\nTotal distance: " << pathByDistance.totalDistance << " km\n";
    std::cout << "Total fare: ₹" << pathByDistance.totalFare << "\n\n";
    
    // Find shortest path by fare
    PathInfo pathByFare = graph.findShortestPath(source, destination, false);
    
    std::cout << "Cheapest path from " << source << " to " << destination << " by fare:\n";
    for (const auto& city : pathByFare.path) {
        std::cout << city;
        if (city != destination) std::cout << " -> ";
    }
    std::cout << "\nTotal distance: " << pathByFare.totalDistance << " km\n";
    std::cout << "Total fare: ₹" << pathByFare.totalFare << "\n";
    
    return 0;
}