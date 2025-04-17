// visualization.js
let map;
let routeLayer;

document.addEventListener('DOMContentLoaded', function() {
    // Initialize map centered on India
    map = L.map('map').setView([23.0, 80.0], 5);
    
    // Add OpenStreetMap tile layer
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(map);
    
    // Create a layer group for the route
    routeLayer = L.layerGroup().addTo(map);
});

// Clear the map
function clearMap() {
    if (routeLayer) {
        routeLayer.clearLayers();
    }
}

// Visualize the route on the map
function visualizeRoute(coordinates, edges) {
    // Clear previous route
    clearMap();
    
    if (!coordinates || coordinates.length === 0) {
        return;
    }
    
    // Add markers for each city in the path
    const markers = [];
    const bounds = [];
    
    coordinates.forEach((coord, index) => {
        const isStart = index === 0;
        const isEnd = index === coordinates.length - 1;
        
        // Create a marker for the city
        const marker = L.marker([coord.lat, coord.lng], {
            icon: L.divIcon({
                className: 'custom-marker',
                html: `<div class="${isStart ? 'start-marker' : isEnd ? 'end-marker' : 'mid-marker'}">${coord.city}</div>`,
                iconSize: [100, 40],
                iconAnchor: [50, 40]
            })
        }).addTo(routeLayer);
        
        // Add popup with city name
        marker.bindPopup(`<b>${coord.city}</b>`);
        
        markers.push(marker);
        bounds.push([coord.lat, coord.lng]);
    });
    
    // Draw lines between connected cities
    for (let i = 0; i < coordinates.length - 1; i++) {
        const from = coordinates[i];
        const to = coordinates[i + 1];
        
        // Find the edge data for this connection
        const edge = edges.find(e => e.from === from.city && e.to === to.city);
        
        // Draw a line between the cities
        const line = L.polyline([
            [from.lat, from.lng],
            [to.lat, to.lng]
        ], {
            color: '#3498db',
            weight: 3,
            opacity: 0.8
        }).addTo(routeLayer);
        
        // Add popup with edge information
        if (edge) {
            line.bindPopup(`
                <b>${edge.from} → ${edge.to}</b><br>
                Distance: ${edge.distance} km<br>
                Fare: ₹${edge.fare}
            `);
        }
    }
    
    // Fit the map to show all markers
    if (bounds.length > 0) {
        map.fitBounds(bounds, { padding: [50, 50] });
    }
    
    // Add CSS for custom markers
    if (!document.getElementById('marker-styles')) {
        const style = document.createElement('style');
        style.id = 'marker-styles';
        style.textContent = `
            .custom-marker {
                text-align: center;
                font-weight: bold;
                white-space: nowrap;
            }
            .start-marker {
                color: #27ae60;
                font-size: 14px;
            }
            .end-marker {
                color: #e74c3c;
                font-size: 14px;
            }
            .mid-marker {
                color: #3498db;
                font-size: 12px;
            }
        `;
        document.head.appendChild(style);
    }
}