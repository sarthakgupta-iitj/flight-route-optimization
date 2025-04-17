// graph.cpp
#include "graph.h"
#include <algorithm>
#include <iostream>

Graph::Graph() {
    // Initialize with 15 Indian cities
    cities = {"Delhi", "Mumbai", "Kolkata", "Chennai", "Bangalore", 
              "Hyderabad", "Ahmedabad", "Pune", "Jaipur", "Lucknow", 
              "Kanpur", "Nagpur", "Indore", "Thane", "Bhopal"};
    
    // Add cities to the graph
    for (const auto& city : cities) {
        addCity(city);
    }
    
    // Add edges with distances (in km) and fares (in rupees)
    // Delhi connections
    addEdge("Delhi", "Mumbai", 1400, 5500);
    addEdge("Delhi", "Kolkata", 1300, 4800);
    addEdge("Delhi", "Jaipur", 280, 2200);
    addEdge("Delhi", "Lucknow", 500, 3000);
    
    // Mumbai connections
    addEdge("Mumbai", "Delhi", 1400, 5500);
    addEdge("Mumbai", "Bangalore", 980, 4200);
    addEdge("Mumbai", "Hyderabad", 700, 3800);
    addEdge("Mumbai", "Pune", 150, 1800);
    addEdge("Mumbai", "Ahmedabad", 530, 3000);
    
    // Kolkata connections
    addEdge("Kolkata", "Delhi", 1300, 4800);
    addEdge("Kolkata", "Chennai", 1660, 5800);
    addEdge("Kolkata", "Hyderabad", 1500, 5200);
    
    // Chennai connections
    addEdge("Chennai", "Kolkata", 1660, 5800);
    addEdge("Chennai", "Bangalore", 350, 2500);
    addEdge("Chennai", "Hyderabad", 630, 3500);
    
    // Bangalore connections
    addEdge("Bangalore", "Mumbai", 980, 4200);
    addEdge("Bangalore", "Chennai", 350, 2500);
    addEdge("Bangalore", "Hyderabad", 570, 3200);
    
    // Hyderabad connections
    addEdge("Hyderabad", "Mumbai", 700, 3800);
    addEdge("Hyderabad", "Chennai", 630, 3500);
    addEdge("Hyderabad", "Bangalore", 570, 3200);
    addEdge("Hyderabad", "Kolkata", 1500, 5200);
    addEdge("Hyderabad", "Nagpur", 500, 2800);
    
    // Ahmedabad connections
    addEdge("Ahmedabad", "Mumbai", 530, 3000);
    addEdge("Ahmedabad", "Jaipur", 640, 3500);
    addEdge("Ahmedabad", "Indore", 400, 2700);
    
    // Pune connections
    addEdge("Pune", "Mumbai", 150, 1800);
    addEdge("Pune", "Bangalore", 840, 3900);
    addEdge("Pune", "Nagpur", 710, 3400);
    
    // Jaipur connections
    addEdge("Jaipur", "Delhi", 280, 2200);
    addEdge("Jaipur", "Ahmedabad", 640, 3500);
    addEdge("Jaipur", "Lucknow", 570, 3200);
    
    // Lucknow connections
    addEdge("Lucknow", "Delhi", 500, 3000);
    addEdge("Lucknow", "Jaipur", 570, 3200);
    addEdge("Lucknow", "Kanpur", 80, 1200);
    
    // Kanpur connections
    addEdge("Kanpur", "Lucknow", 80, 1200);
    addEdge("Kanpur", "Nagpur", 770, 3700);
    
    // Nagpur connections
    addEdge("Nagpur", "Pune", 710, 3400);
    addEdge("Nagpur", "Hyderabad", 500, 2800);
    addEdge("Nagpur", "Kanpur", 770, 3700);
    addEdge("Nagpur", "Indore", 440, 2600);
    addEdge("Nagpur", "Bhopal", 350, 2400);
    
    // Indore connections
    addEdge("Indore", "Ahmedabad", 400, 2700);
    addEdge("Indore", "Nagpur", 440, 2600);
    addEdge("Indore", "Bhopal", 190, 1900);
    
    // Thane connections (near Mumbai)
    addEdge("Thane", "Mumbai", 25, 800);
    addEdge("Thane", "Pune", 120, 1600);
    
    // Bhopal connections
    addEdge("Bhopal", "Indore", 190, 1900);
    addEdge("Bhopal", "Nagpur", 350, 2400);

    // Expanded dataset with additional edges (no new cities)

// Delhi connections (additional)
    addEdge("Delhi", "Chennai", 2200, 6500);
    addEdge("Delhi", "Bangalore", 2100, 6200);
    addEdge("Delhi", "Hyderabad", 1500, 5000);
    addEdge("Delhi", "Ahmedabad", 900, 4000);
    addEdge("Delhi", "Pune", 1400, 5300);
    addEdge("Delhi", "Nagpur", 1100, 4500);
    addEdge("Delhi", "Indore", 800, 3800);
    addEdge("Delhi", "Bhopal", 750, 3600);
    addEdge("Delhi", "Kanpur", 400, 2500);
    addEdge("Delhi", "Thane", 1350, 5200);

    // Mumbai connections (additional)
    addEdge("Mumbai", "Kolkata", 1900, 6000);
    addEdge("Mumbai", "Chennai", 1300, 4800);
    addEdge("Mumbai", "Jaipur", 1150, 4600);
    addEdge("Mumbai", "Lucknow", 1400, 5100);
    addEdge("Mumbai", "Kanpur", 1300, 4900);
    addEdge("Mumbai", "Nagpur", 830, 3900);
    addEdge("Mumbai", "Indore", 580, 3200);
    addEdge("Mumbai", "Bhopal", 780, 3700);

    // Kolkata connections (additional)
    addEdge("Kolkata", "Bangalore", 1800, 5700);
    addEdge("Kolkata", "Jaipur", 1500, 5100);
    addEdge("Kolkata", "Lucknow", 1000, 4200);
    addEdge("Kolkata", "Kanpur", 950, 4000);
    addEdge("Kolkata", "Nagpur", 1100, 4600);
    addEdge("Kolkata", "Bhopal", 1300, 4900);
    addEdge("Kolkata", "Ahmedabad", 2000, 6200);
    addEdge("Kolkata", "Pune", 1800, 5800);

    // Chennai connections (additional)
    addEdge("Chennai", "Delhi", 2200, 6500);
    addEdge("Chennai", "Ahmedabad", 1700, 5500);
    addEdge("Chennai", "Pune", 1100, 4500);
    addEdge("Chennai", "Jaipur", 2100, 6300);
    addEdge("Chennai", "Lucknow", 1900, 5900);
    addEdge("Chennai", "Kanpur", 1800, 5700);
    addEdge("Chennai", "Nagpur", 1000, 4300);
    addEdge("Chennai", "Indore", 1200, 4700);
    addEdge("Chennai", "Bhopal", 1400, 5100);

    // Bangalore connections (additional)
    addEdge("Bangalore", "Delhi", 2100, 6200);
    addEdge("Bangalore", "Kolkata", 1800, 5700);
    addEdge("Bangalore", "Ahmedabad", 1500, 5000);
    addEdge("Bangalore", "Jaipur", 2000, 6000);
    addEdge("Bangalore", "Lucknow", 1800, 5600);
    addEdge("Bangalore", "Kanpur", 1700, 5400);
    addEdge("Bangalore", "Nagpur", 900, 4100);
    addEdge("Bangalore", "Indore", 1100, 4500);
    addEdge("Bangalore", "Bhopal", 1200, 4700);
    addEdge("Bangalore", "Thane", 950, 4300);

    // Hyderabad connections (additional)
    addEdge("Hyderabad", "Delhi", 1500, 5000);
    addEdge("Hyderabad", "Ahmedabad", 1100, 4500);
    addEdge("Hyderabad", "Jaipur", 1400, 4800);
    addEdge("Hyderabad", "Lucknow", 1200, 4600);
    addEdge("Hyderabad", "Kanpur", 1100, 4400);
    addEdge("Hyderabad", "Indore", 800, 3900);
    addEdge("Hyderabad", "Bhopal", 650, 3600);
    addEdge("Hyderabad", "Thane", 680, 3700);
    addEdge("Hyderabad", "Pune", 560, 3300);

    // Ahmedabad connections (additional)
    addEdge("Ahmedabad", "Delhi", 900, 4000);
    addEdge("Ahmedabad", "Kolkata", 2000, 6200);
    addEdge("Ahmedabad", "Chennai", 1700, 5500);
    addEdge("Ahmedabad", "Bangalore", 1500, 5000);
    addEdge("Ahmedabad", "Hyderabad", 1100, 4500);
    addEdge("Ahmedabad", "Pune", 660, 3400);
    addEdge("Ahmedabad", "Nagpur", 700, 3600);
    addEdge("Ahmedabad", "Bhopal", 500, 3000);
    addEdge("Ahmedabad", "Lucknow", 1100, 4600);

    // Pune connections (additional)
    addEdge("Pune", "Delhi", 1400, 5300);
    addEdge("Pune", "Kolkata", 1800, 5800);
    addEdge("Pune", "Chennai", 1100, 4500);
    addEdge("Pune", "Ahmedabad", 660, 3400);
    addEdge("Pune", "Jaipur", 1200, 4700);
    addEdge("Pune", "Lucknow", 1300, 4900);
    addEdge("Pune", "Kanpur", 1200, 4700);
    addEdge("Pune", "Indore", 600, 3300);
    addEdge("Pune", "Bhopal", 780, 3700);
    addEdge("Pune", "Thane", 120, 1600);

    // Jaipur connections (additional)
    addEdge("Jaipur", "Chennai", 2100, 6300);
    addEdge("Jaipur", "Bangalore", 2000, 6000);
    addEdge("Jaipur", "Hyderabad", 1400, 4800);
    addEdge("Jaipur", "Pune", 1200, 4700);
    addEdge("Jaipur", "Nagpur", 900, 4100);
    addEdge("Jaipur", "Indore", 550, 3100);
    addEdge("Jaipur", "Bhopal", 600, 3300);
    addEdge("Jaipur", "Kanpur", 500, 3000);
    addEdge("Jaipur", "Thane", 1100, 4500);

    // Lucknow connections (additional)
    addEdge("Lucknow", "Mumbai", 1400, 5100);
    addEdge("Lucknow", "Chennai", 1900, 5900);
    addEdge("Lucknow", "Bangalore", 1800, 5600);
    addEdge("Lucknow", "Hyderabad", 1200, 4600);
    addEdge("Lucknow", "Ahmedabad", 1100, 4600);
    addEdge("Lucknow", "Pune", 1300, 4900);
    addEdge("Lucknow", "Nagpur", 800, 3900);
    addEdge("Lucknow", "Indore", 700, 3600);
    addEdge("Lucknow", "Bhopal", 550, 3200);
    addEdge("Lucknow", "Thane", 1350, 5000);

    // Kanpur connections (additional)
    addEdge("Kanpur", "Mumbai", 1300, 4900);
    addEdge("Kanpur", "Chennai", 1800, 5700);
    addEdge("Kanpur", "Bangalore", 1700, 5400);
    addEdge("Kanpur", "Hyderabad", 1100, 4400);
    addEdge("Kanpur", "Ahmedabad", 1000, 4200);
    addEdge("Kanpur", "Pune", 1200, 4700);
    addEdge("Kanpur", "Jaipur", 500, 3000);
    addEdge("Kanpur", "Indore", 650, 3400);
    addEdge("Kanpur", "Bhopal", 500, 3100);
    addEdge("Kanpur", "Thane", 1250, 4800);

    // Nagpur connections (additional)
    addEdge("Nagpur", "Delhi", 1100, 4500);
    addEdge("Nagpur", "Kolkata", 1100, 4600);
    addEdge("Nagpur", "Chennai", 1000, 4300);
    addEdge("Nagpur", "Bangalore", 900, 4100);
    addEdge("Nagpur", "Ahmedabad", 700, 3600);
    addEdge("Nagpur", "Jaipur", 900, 4100);
    addEdge("Nagpur", "Lucknow", 800, 3900);
    addEdge("Nagpur", "Thane", 780, 3700);

    // Indore connections (additional)
    addEdge("Indore", "Delhi", 800, 3800);
    addEdge("Indore", "Chennai", 1200, 4700);
    addEdge("Indore", "Bangalore", 1100, 4500);
    addEdge("Indore", "Hyderabad", 800, 3900);
    addEdge("Indore", "Pune", 600, 3300);
    addEdge("Indore", "Jaipur", 550, 3100);
    addEdge("Indore", "Lucknow", 700, 3600);
    addEdge("Indore", "Kanpur", 650, 3400);
    addEdge("Indore", "Thane", 550, 3200);

    // Thane connections (additional)
    addEdge("Thane", "Delhi", 1350, 5200);
    addEdge("Thane", "Bangalore", 950, 4300);
    addEdge("Thane", "Hyderabad", 680, 3700);
    addEdge("Thane", "Ahmedabad", 500, 3100);
    addEdge("Thane", "Jaipur", 1100, 4500);
    addEdge("Thane", "Lucknow", 1350, 5000);
    addEdge("Thane", "Kanpur", 1250, 4800);
    addEdge("Thane", "Nagpur", 780, 3700);
    addEdge("Thane", "Indore", 550, 3200);
    addEdge("Thane", "Bhopal", 750, 3600);

    // Bhopal connections (additional)
    addEdge("Bhopal", "Delhi", 750, 3600);
    addEdge("Bhopal", "Kolkata", 1300, 4900);
    addEdge("Bhopal", "Chennai", 1400, 5100);
    addEdge("Bhopal", "Bangalore", 1200, 4700);
    addEdge("Bhopal", "Hyderabad", 650, 3600);
    addEdge("Bhopal", "Ahmedabad", 500, 3000);
    addEdge("Bhopal", "Pune", 780, 3700);
    addEdge("Bhopal", "Jaipur", 600, 3300);
    addEdge("Bhopal", "Lucknow", 550, 3200);
    addEdge("Bhopal", "Kanpur", 500, 3100);
    addEdge("Bhopal", "Thane", 750, 3600);
}

void Graph::addCity(const std::string& city) {
    if (adjacencyList.find(city) == adjacencyList.end()) {
        adjacencyList[city] = std::vector<Edge>();
    }
}

void Graph::addEdge(const std::string& source, const std::string& destination, int distance, int fare) {
    adjacencyList[source].push_back({destination, distance, fare});
}

PathInfo Graph::findShortestPath(const std::string& source, const std::string& destination, bool byDistance) {
    // Initialize result
    PathInfo result;
    result.totalDistance = 0;
    result.totalFare = 0;
    
    // Check if source and destination exist in the graph
    if (adjacencyList.find(source) == adjacencyList.end() || 
        adjacencyList.find(destination) == adjacencyList.end()) {
        return result; // Return empty path
    }
    
    // Standard Dijkstra's algorithm implementation
    std::unordered_map<std::string, int> distance;
    std::unordered_map<std::string, int> fare;
    std::unordered_map<std::string, std::string> previous;
    
    // Initialize all distances to infinity
    for (const auto& pair : adjacencyList) {
        distance[pair.first] = INT_MAX;
        fare[pair.first] = 0;
    }
    
    // Priority queue for Dijkstra's
    std::priority_queue<std::pair<int, std::string>, 
                       std::vector<std::pair<int, std::string>>, 
                       std::greater<std::pair<int, std::string>>> pq;
    
    distance[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        std::string current = pq.top().second;
        int currentCost = pq.top().first;
        pq.pop();
        
        if (current == destination) break;
        
        if (currentCost > distance[current]) continue;
        
        for (const auto& edge : adjacencyList[current]) {
            int newDistance = distance[current] + edge.distance;
            int newFare = fare[current] + edge.fare;
            int newCost = byDistance ? newDistance : newFare;
            
            if (newCost < (byDistance ? distance[edge.destination] : fare[edge.destination]) || 
                distance[edge.destination] == INT_MAX) {
                distance[edge.destination] = newDistance;
                fare[edge.destination] = newFare;
                previous[edge.destination] = current;
                pq.push({newCost, edge.destination});
            }
        }
    }
    
    // Path not found
    if (distance[destination] == INT_MAX) {
        return result;
    }
    
    // Build the path and simultaneously collect edge information
    std::vector<std::string> path;
    std::string current = destination;
    
    while (current != source) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(source);
    
    // Reverse to get source to destination order
    std::reverse(path.begin(), path.end());
    result.path = path;
    
    // Set the totals
    result.totalDistance = distance[destination];
    result.totalFare = fare[destination];
    
    // Store individual edge details
    for (size_t i = 0; i < path.size() - 1; i++) {
        std::string from = path[i];
        std::string to = path[i + 1];
        
        // Find the edge in the adjacency list
        for (const auto& edge : adjacencyList[from]) {
            if (edge.destination == to) {
                // Create an exact clone of the edge to store
                EdgeInfo edgeInfo;
                edgeInfo.destination = edge.destination;
                edgeInfo.distance = edge.distance;
                edgeInfo.fare = edge.fare;
                
                result.edges.push_back(edgeInfo);
                break;
            }
        }
    }
    
    return result;
}

std::vector<std::string> Graph::getCities() const {
    return cities;
}


std::unordered_map<std::string, std::vector<Edge>> Graph::getAdjacencyList() const {
    // Debug: Print the entire adjacency list to verify its contents
    std::cout << "Adjacency List Contents:" << std::endl;
    for (const auto& [city, edges] : adjacencyList) {
        std::cout << city << " has " << edges.size() << " outgoing edges:" << std::endl;
        for (const auto& edge : edges) {
            std::cout << "  -> " << edge.destination 
                      << " (dist: " << edge.distance 
                      << ", fare: " << edge.fare << ")" << std::endl;
        }
    }
    
    return adjacencyList;
}