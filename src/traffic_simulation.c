#include <SDL2/SDL.h>
#include "traffic_simulation.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#define MAX_VEHICLES 100

Vehicle vehicles[MAX_VEHICLES]; // Queue for vehicles
TrafficLight trafficLights[4] = {
    {{250, 230, 50, 100}, false},  // Left
    {{475, 480, 50, 100}, false},  // Right
    {{475, 230, 50, 100}, false},  // Top
    {{250, 480, 50, 100}, false}   // Bottom
};

int currentLight = 0;

void createVehicle() {
    Vehicle newVehicle;
    newVehicle.active = true;
    newVehicle.rect = (SDL_Rect){0, 0, 18, 14};
    newVehicle.speed = 5;
    
    int direction = rand() % 4;
    switch(direction){
        case 0:
            newVehicle.direction = LEFT;
            break;
        case 1:
            newVehicle.direction = RIGHT;
            break;
        case 2:
            newVehicle.direction = TOP;
            break;
        case 3:
            newVehicle.direction = BOTTOM;
            break;
    }
    
    if (direction == LEFT && trafficLights[0].isGreen) {
        newVehicle.rect.x = -newVehicle.rect.w;
        newVehicle.rect.y = (rand() % 2 == 0) ? 350 : 380;
    } else if (direction == RIGHT && trafficLights[1].isGreen) {
        newVehicle.rect.x = SCREEN_WIDTH;
        newVehicle.rect.y = (rand() % 2 == 0) ? 400 : 430;
        newVehicle.speed = -5;
    } else if (direction == TOP && trafficLights[2].isGreen) {
        newVehicle.rect.x = (rand() % 2 == 0) ? 400 : 430;
        newVehicle.rect.y = -newVehicle.rect.h;
    } else if (direction == BOTTOM && trafficLights[3].isGreen) {
        newVehicle.rect.x = (rand() % 2 == 0) ? 350 : 380;
        newVehicle.rect.y = SCREEN_HEIGHT;
        newVehicle.speed = -5;
    } else {
        return;
    }
    // newVehicle.color = {rand() % 256, rand() % 256, rand() % 256, 255};

    for (int i = 0; i < MAX_VEHICLES; i++) {
        if (!vehicles[i].active) {
            vehicles[i] = newVehicle;
            break;
        }
    }
}
