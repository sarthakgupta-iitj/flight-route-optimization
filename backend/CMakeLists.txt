# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(FlightRouteOptimizer)

set(CMAKE_CXX_STANDARD 17)

# Find nlohmann/json package (you might need to install this first)
# macOS: brew install nlohmann-json
find_package(nlohmann_json 3.2.0 REQUIRED)

# Add executable
add_executable(
    flight_route_optimizer
    src/main.cpp
    src/graph.cpp
)

# Add server executable
add_executable(
    flight_route_server
    src/server.cpp
    src/graph.cpp
)

# Link libraries
target_link_libraries(flight_route_server PRIVATE nlohmann_json::nlohmann_json)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)