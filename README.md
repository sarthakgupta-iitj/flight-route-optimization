# Flight Route Optimization System

A DSA project implementing Dijkstra's algorithm to find the shortest and cheapest flight routes between Indian cities.

## Overview

This project consists of:
- **C++ Backend**: Implements the graph data structure and Dijkstra's algorithm to find optimal routes.
- **JavaScript Frontend**: Provides a user interface for selecting cities and visualizing the optimal routes.

## Features

- Find the shortest route (by distance) between any two Indian cities
- Find the cheapest route (by fare) between any two Indian cities
- Visualize the route on an interactive map
- Display detailed route information including:
  - Total distance
  - Total fare
  - Step-by-step flight path

## Prerequisites

- C++17 compiler
- CMake (version 3.10 or higher)
- nlohmann/json library for C++
- Web browser with JavaScript enabled

## Project Structure

```
flight-route-optimizer/
├── backend/
│   ├── src/
│   │   ├── main.cpp        # Main C++ program
│   │   ├── graph.h         # Graph data structure header
│   │   ├── graph.cpp       # Graph implementation
│   │   └── server.cpp      # Simple HTTP server
│   ├── Makefile
│   └── CMakeLists.txt      # CMake configuration
├── frontend/
│   ├── index.html          # HTML structure
│   ├── styles.css          # CSS styling
│   ├── js/
│   │   ├── main.js         # Main JavaScript logic
│   │   └── visualization.js # Map visualization logic
│   └── assets/
│       └── india_map.svg   # SVG map of India
└── README.md               # This file
```

## Installation and Setup

### Backend Setup

1. Install the required libraries:
   
   ```bash
   # On macOS
   brew install nlohmann-json
   
   # On Ubuntu/Debian
   sudo apt-get install nlohmann-json3-dev
   ```

2. Build the backend:
   
   ```bash
   cd backend
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Start the server:
   
   ```bash
   ./flight_route_server
   ```

### Frontend Setup

1. Navigate to the frontend directory:
   
   ```bash
   cd frontend
   ```

2. Open `index.html` in your web browser or use a local development server:
   
   ```bash
   # Using Python's built-in HTTP server
   python -m http.server 3000
   ```

3. Access the application at `http://localhost:3000`

## Usage

1. Select a source city from the dropdown menu
2. Select a destination city from the dropdown menu
3. Choose optimization criteria:
   - Shortest Distance: Find the path with the least total distance
   - Lowest Fare: Find the path with the least total fare
4. Click "Find Route" to calculate and display the optimal route
5. View the route visualization on the map and the detailed information

## Algorithm Details

The project implements Dijkstra's algorithm to find the shortest path in a weighted graph:

1. Each city is a vertex in the graph
2. Flight connections between cities are edges
3. Each edge has two weights: distance and fare
4. When optimizing for distance, the algorithm uses distance as the edge weight
5. When optimizing for fare, the algorithm uses fare as the edge weight

## Contributing

Feel free to submit issues or pull requests to improve the project.

## License

This project is licensed under the MIT License - see the LICENSE file for details.