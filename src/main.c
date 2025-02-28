#include <stdio.h>
#ifndef TRAFFIC_SIMULATION_H
#define TRAFFIC_SIMULATION_H
#define ROAD_WIDTH 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Enum for directions
typedef enum {
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3
} Direction;

// Vehicle struct declaration
typedef struct {
    SDL_Rect rect;
    bool active;
    int speed;
    Direction direction;
} Vehicle;

// TrafficLight struct declaration
typedef struct {
    SDL_Rect rect;
    bool isGreen;
} TrafficLight;

// Function prototypes
void createVehicle();
void updateVehicles();
void drawTrafficLightIndicator(SDL_Renderer *renderer);
void updateTrafficLight();

#define MAX_VEHICLES 100
extern Vehicle vehicles[MAX_VEHICLES];
extern TrafficLight trafficLights[4];
extern int currentLight; // Track which traffic light is green

#endif // TRAFFIC_SIMULATION_H