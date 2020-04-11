/**
    test.c
    Purpose: To simulate packet transfer between two static nodes 
    in randomly placed location.

    @author Rupam Chirom
*/

#include<stdio.h>
#include<stdlib.h>

#define NODES 2
#define RANGE 5000
// RANGE in kms; 

const struct node {
    float send, receive, lat, lon, lat_p_range, lat_m_range, lon_p_range, lon_m_range;
};

float location_generator(float limit) {
    // return a random number between -limit & limit
    float divisor = RAND_MAX / (limit*2 + 1);
    float retval;
    do {
        retval = (float)rand() / divisor;
    } while (retval > limit*2);
    return retval-limit;
}

float lat_km, lon_km, r=0;
float range_convertor(int r) {
    // converts the defined range into latitude and longitude
    lat_km = (1 / 110.575) * r;
    lon_km = (1 / 111.303) * r;
}

typedef struct node Struct;
Struct range_definition(float lat, float lon) {
    Struct def;
    def.lat = lat;
    def.lon = lon;
    def.lat_m_range = def.lat - lat_km;
    def.lat_p_range = def.lat + lat_km;
    def.lon_m_range = def.lon - lon_km;
    def.lon_p_range = def.lon + lon_km;
    return def;
}

void decorator() {
    printf("\n-----\n");
}

void main(){
    struct node node[NODES];
    printf("Initial data");
#ifdef RANGE
    r = RANGE;
#endif // RANGE
#ifndef RANGE
    printf("Set range for the nodes (in km):");
    scanf("%f", &r);
#endif // !RANGE
    range_convertor(r);
    printf("\nNode range in meters: %d \t Range for +/- %f, %f", r, lat_km, lon_km);
    for (int i = 0; i < NODES; i++) {
        node[i].send = 100;
        node[i].receive = 100;
        node[i].lat = location_generator(90);
        node[i].lon = location_generator(180);
        printf("\nnode%d \t Lat: %f \t Long: %f", i, node[i].lat, node[i].lon);
        range_definition(node[i].lat, node[i].lon);
        printf("\nExtension \t Lat: %f, %f \t Lat: %f, %f", node[i].lat_m_range, node[i].lat_p_range, node[i].lon_m_range, node[i].lon_p_range);
    }
    decorator();
}