// server.cpp
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "graph.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Simple HTTP server to handle API requests
class HttpServer {
private:
    int serverSocket;
    int port;
    Graph graph;

    std::string handleRequest(const std::string& request) {
        // Parse HTTP request
        if (request.find("GET /api/cities") != std::string::npos) {
            return getCitiesResponse();
        } else if (request.find("GET /api/routes") != std::string::npos) {
            // Extract query parameters
            size_t sourcePos = request.find("source=");
            size_t destPos = request.find("destination=");
            size_t typePos = request.find("type=");
            
            if (sourcePos != std::string::npos && destPos != std::string::npos && typePos != std::string::npos) {
                std::string source, destination, type;
                
                // Extract source
                sourcePos += 7; // length of "source="
                size_t sourceEnd = request.find('&', sourcePos);
                source = request.substr(sourcePos, sourceEnd - sourcePos);
                
                // Extract destination
                destPos += 12; // length of "destination="
                size_t destEnd = request.find('&', destPos);
                destination = request.substr(destPos, destEnd - destPos);
                
                // Extract type
                typePos += 5; // length of "type="
                size_t typeEnd = request.find(' ', typePos);
                type = request.substr(typePos, typeEnd - typePos);
                
                return getRouteResponse(source, destination, type == "distance");
            }
        }
        
        // Default: return 404
        return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nAccess-Control-Allow-Origin: *\r\n\r\nNot Found";
    }

    std::string getCitiesResponse() {
        json response;
        response["cities"] = graph.getCities();
        
        std::string responseBody = response.dump();
        
        std::stringstream ss;
        ss << "HTTP/1.1 200 OK\r\n";
        ss << "Content-Type: application/json\r\n";
        ss << "Content-Length: " << responseBody.size() << "\r\n";
        ss << "Access-Control-Allow-Origin: *\r\n";
        ss << "\r\n";
        ss << responseBody;
        
        return ss.str();
    }

std::string getRouteResponse(const std::string& source, const std::string& destination, bool byDistance) {
    PathInfo path = graph.findShortestPath(source, destination, byDistance);
    
    // Debug output to see what path was found
    std::cout << "Path found: ";
    for (const auto& city : path.path) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    
    json response;
    if (path.path.empty() || path.totalDistance == -1) {
        response["error"] = "No path found";
    } else {
        response["path"] = path.path;
        response["totalDistance"] = path.totalDistance;
        response["totalFare"] = path.totalFare;
        
        // Add coordinates for visualization
        json coordinates;
        // These are approximate coordinates for the cities
        std::unordered_map<std::string, std::pair<float, float>> cityCoords = {
            {"Delhi", {77.1025, 28.7041}},
            {"Mumbai", {72.8777, 19.0760}},
            {"Kolkata", {88.3639, 22.5726}},
            {"Chennai", {80.2707, 13.0827}},
            {"Bangalore", {77.5946, 12.9716}},
            {"Hyderabad", {78.4867, 17.3850}},
            {"Ahmedabad", {72.5714, 23.0225}},
            {"Pune", {73.8567, 18.5204}},
            {"Jaipur", {75.7873, 26.9124}},
            {"Lucknow", {80.9462, 26.8467}},
            {"Kanpur", {80.3319, 26.4499}},
            {"Nagpur", {79.0882, 21.1458}},
            {"Indore", {75.8577, 22.7196}},
            {"Thane", {72.9781, 19.2183}},
            {"Bhopal", {77.4126, 23.2599}}
        };
        
        for (const auto& city : path.path) {
            json coord;
            coord["city"] = city;
            coord["lat"] = cityCoords[city].second;
            coord["lng"] = cityCoords[city].first;
            coordinates.push_back(coord);
        }
        response["coordinates"] = coordinates;
        
        // Use the edges directly from the PathInfo
        json edges;
        for (size_t i = 0; i < path.edges.size(); ++i) {
            json edge;
            edge["from"] = path.path[i];
            edge["to"] = path.path[i + 1];
            edge["distance"] = path.edges[i].distance;
            edge["fare"] = path.edges[i].fare;
            
            // Debug output for edge details
            std::cout << "Edge: " << path.path[i] << " -> " << path.path[i + 1] 
                      << " (dist: " << path.edges[i].distance 
                      << ", fare: " << path.edges[i].fare << ")" << std::endl;
                      
            edges.push_back(edge);
        }
        response["edges"] = edges;
    }
    
    std::string responseBody = response.dump();
    
    std::stringstream ss;
    ss << "HTTP/1.1 200 OK\r\n";
    ss << "Content-Type: application/json\r\n";
    ss << "Content-Length: " << responseBody.size() << "\r\n";
    ss << "Access-Control-Allow-Origin: *\r\n";
    ss << "\r\n";
    ss << responseBody;
    
    return ss.str();
}

public:
    HttpServer(int p) : port(p) {
        // Initialize socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            std::cerr << "Failed to create socket\n";
            exit(1);
        }
        
        // Set socket options
        int opt = 1;
        if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            std::cerr << "Failed to set socket options\n";
            exit(1);
        }
        
        // Bind to port
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        
        if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
            std::cerr << "Failed to bind to port " << port << "\n";
            exit(1);
        }
        
        // Listen for connections
        if (listen(serverSocket, 10) < 0) {
            std::cerr << "Failed to listen on socket\n";
            exit(1);
        }
        
        std::cout << "Server started on port " << port << "\n";
    }
    
    void start() {
        while (true) {
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            
            int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket < 0) {
                std::cerr << "Failed to accept connection\n";
                continue;
            }
            
            char buffer[4096] = {0};
            int bytesRead = read(clientSocket, buffer, 4096);
            if (bytesRead < 0) {
                std::cerr << "Failed to read from client\n";
                close(clientSocket);
                continue;
            }
            
            std::string request(buffer);
            std::string response = handleRequest(request);
            
            send(clientSocket, response.c_str(), response.size(), 0);
            close(clientSocket);
        }
    }
    
    ~HttpServer() {
        close(serverSocket);
    }
};

int main() {
    // Start HTTP server on port 8080
    HttpServer server(8080);
    server.start();
    
    return 0;
}