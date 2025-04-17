// main.js
document.addEventListener('DOMContentLoaded', function() {
    const baseUrl = 'http://localhost:8080/api';
    const sourceSelect = document.getElementById('source');
    const destinationSelect = document.getElementById('destination');
    const routeForm = document.getElementById('route-form');
    const pathDetails = document.getElementById('path-details');
    
    // Fetch cities from API
    async function fetchCities() {
        try {
            const response = await fetch(`${baseUrl}/cities`);
            const data = await response.json();
            
            // Populate dropdowns
            data.cities.forEach(city => {
                const sourceOption = document.createElement('option');
                sourceOption.value = city;
                sourceOption.textContent = city;
                sourceSelect.appendChild(sourceOption);
                
                const destOption = document.createElement('option');
                destOption.value = city;
                destOption.textContent = city;
                destinationSelect.appendChild(destOption);
            });
        } catch (error) {
            console.error('Error fetching cities:', error);
            alert('Failed to fetch cities. Make sure the backend server is running.');
        }
    }
    
    // Find route between cities
    async function findRoute(source, destination, type) {
        try {
            const response = await fetch(`${baseUrl}/routes?source=${source}&destination=${destination}&type=${type}`);
            const data = await response.json();
            
            // main.js (continued)
            if (data.error) {
                pathDetails.innerHTML = `<div class="error">${data.error}</div>`;
                clearMap();
                return;
            }
            
            // Display path details
            displayPathDetails(data, type);
            
            // Visualize route on map
            visualizeRoute(data.coordinates, data.edges);
            
        } catch (error) {
            console.error('Error finding route:', error);
            pathDetails.innerHTML = `<div class="error">Failed to find route. Make sure the backend server is running.</div>`;
            clearMap();
        }
    }
    
    // Display path details in the UI
    function displayPathDetails(data, type) {
        const cities = data.path.join(' → ');
        const totalDistance = data.totalDistance;
        const totalFare = data.totalFare;
        
        let html = `
            <div class="route-path">
                <h3>Flight Path</h3>
                <div class="path-cities">${cities}</div>
                <ul class="path-steps">
        `;
        
        // Add each step in the path
        for (let i = 0; i < data.edges.length; i++) {
            const edge = data.edges[i];
            html += `
                <li>
                    <strong>${edge.from} → ${edge.to}</strong>
                    <div>Distance: ${edge.distance} km | Fare: ₹${edge.fare}</div>
                </li>
            `;
        }
        
        html += `
                </ul>
            </div>
            <div class="route-summary">
                <p><strong>Optimization:</strong> ${type === 'distance' ? 'Shortest Distance' : 'Lowest Fare'}</p>
                <p><strong>Total Distance:</strong> ${totalDistance} km</p>
                <p><strong>Total Fare:</strong> ₹${totalFare}</p>
            </div>
        `;
        
        pathDetails.innerHTML = html;
    }
    
    // Handle form submission
    routeForm.addEventListener('submit', function(e) {
        e.preventDefault();
        
        const source = sourceSelect.value;
        const destination = destinationSelect.value;
        const type = document.querySelector('input[name="type"]:checked').value;
        
        if (source === destination) {
            pathDetails.innerHTML = `<div class="error">Source and destination cannot be the same.</div>`;
            clearMap();
            return;
        }
        
        findRoute(source, destination, type);
    });
    
    // Initialize
    fetchCities();
});