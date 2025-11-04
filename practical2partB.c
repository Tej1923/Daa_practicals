#include <math.h>

// Earth's radius in kilometers
#define EARTH_RADIUS_KM 6371.0 
#define MAX_VERTICES 10

// Converts degrees to radians
double deg2rad(double deg) {
    return (deg * M_PI / 180);
}

// Function to calculate distance between two points using the Haversine formula
double haversine_distance(double lat1, double lon1, double lat2, double lon2) {
    // Convert degrees to radians
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    // Haversine formula
    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    // Distance in km
    double distance = EARTH_RADIUS_KM * c;

    return distance;
}

// Conceptual Structure for PART-B Calculation
void calculate_cost_matrix(double lat[], double lon[], int V, int cost_matrix[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                cost_matrix[i][j] = 0;
            } else {
                double dist = haversine_distance(lat[i], lon[i], lat[j], lon[j]);
                cost_matrix[i][j] = (int)round(dist); 
            }
        }
    }
}