#include <SDL2/SDL.h>
#include "traffic_simulation.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#define MAX_VEHICLES 100

Vehicle vehicles[MAX_VEHICLES]; // Queue for vehicles
TrafficLight trafficLights[4] = {
    {{(SCREEN_WIDTH-ROAD_WIDTH)/2 - 50, (SCREEN_HEIGHT-ROAD_WIDTH)/2 - 100, 50, 100}, false},  // Left
    {{(SCREEN_WIDTH+ROAD_WIDTH)/2, (SCREEN_HEIGHT+ROAD_WIDTH)/2, 50, 100}, false},  // Right
    {{(SCREEN_WIDTH+ROAD_WIDTH)/2, (SCREEN_HEIGHT-ROAD_WIDTH)/2 - 100, 50, 100}, false},  // Top
    {{(SCREEN_WIDTH-ROAD_WIDTH)/2 - 50, (SCREEN_HEIGHT+ROAD_WIDTH)/2 , 50, 100}, false}   // Bottom
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
        newVehicle.rect.y = (rand() % 2 == 0) ? SCREEN_HEIGHT/2 - ROAD_WIDTH/4 : SCREEN_HEIGHT/2 + ROAD_WIDTH/4;
    } else if (direction == RIGHT && trafficLights[1].isGreen) {
        newVehicle.rect.x = SCREEN_WIDTH;
        newVehicle.rect.y = (rand() % 2 == 0) ? SCREEN_HEIGHT/2 + ROAD_WIDTH/4 : SCREEN_HEIGHT/2 - ROAD_WIDTH/4;
        newVehicle.speed = -5;
    } else if (direction == TOP && trafficLights[2].isGreen) {
        newVehicle.rect.x = (rand() % 2 == 0) ? SCREEN_HEIGHT/2 + ROAD_WIDTH/4 : SCREEN_WIDTH/2 - ROAD_WIDTH/4;
        newVehicle.rect.y = -newVehicle.rect.h;
    } else if (direction == BOTTOM && trafficLights[3].isGreen) {
        newVehicle.rect.x = (rand() % 2 == 0) ? SCREEN_WIDTH/2 - ROAD_WIDTH/4 : SCREEN_WIDTH/2 + ROAD_WIDTH/4;
        newVehicle.rect.y = SCREEN_HEIGHT;
        newVehicle.speed = -5;
    } else {
        return;
    }
    
    for (int i = 0; i < MAX_VEHICLES; i++) {
        if (!vehicles[i].active) {
            vehicles[i] = newVehicle;
            break;
        }
    }
}

void updateVehicles() {
    for (int i = 0; i < MAX_VEHICLES; i++) {
        if (vehicles[i].active) {
            bool shouldStop = false;
            
            if (vehicles[i].direction == LEFT && !trafficLights[0].isGreen && vehicles[i].rect.x < SCREEN_WIDTH * 0.4f) shouldStop = true;
            if (vehicles[i].direction == RIGHT && !trafficLights[1].isGreen && vehicles[i].rect.x > SCREEN_WIDTH * 0.6f) shouldStop = true;
            if (vehicles[i].direction == TOP && !trafficLights[2].isGreen && vehicles[i].rect.y < SCREEN_HEIGHT * 0.4f) shouldStop = true;
            if (vehicles[i].direction == BOTTOM && !trafficLights[3].isGreen && vehicles[i].rect.y > SCREEN_HEIGHT * 0.6f) shouldStop = true;

            if (!shouldStop) {
                if (vehicles[i].direction == LEFT || vehicles[i].direction == RIGHT) {
                    vehicles[i].rect.x += vehicles[i].speed;
                } else {
                    vehicles[i].rect.y += vehicles[i].speed;
                }
            }
            
            if (vehicles[i].rect.x > SCREEN_WIDTH || vehicles[i].rect.x < -vehicles[i].rect.w ||
                vehicles[i].rect.y > SCREEN_HEIGHT || vehicles[i].rect.y < -vehicles[i].rect.h) {
                vehicles[i].active = false;
            }
        }
    }
}

void drawTrafficLightIndicator(SDL_Renderer *renderer) {
    for (int i = 0; i < 4; i++) {
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
        SDL_RenderFillRect(renderer, &trafficLights[i].rect);
        
        SDL_Color lightColor = trafficLights[i].isGreen ? (SDL_Color){0, 255, 0, 255} : (SDL_Color){255, 0, 0, 255};
        SDL_SetRenderDrawColor(renderer, lightColor.r, lightColor.g, lightColor.b, 255);
        SDL_Rect lightRect = {trafficLights[i].rect.x + 15, trafficLights[i].rect.y + 25, 20, 20};
        SDL_RenderFillRect(renderer, &lightRect);
    }
}

void updateTrafficLight() {
    static int frameCounter = 0;
    frameCounter++;

    if (frameCounter % 300 == 0) {
        trafficLights[currentLight].isGreen = false;
        currentLight = (currentLight + 1) % 4;
        trafficLights[currentLight].isGreen = true;
        frameCounter = 0;
    }
}
