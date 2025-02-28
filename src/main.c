#include "traffic_simulation.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


void drawTrafficLightIndicator(SDL_Renderer *renderer);
void simulateTraffic();
void drawIntersection(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    
    SDL_Rect verticalRoad = {SCREEN_WIDTH / 2 - ROAD_WIDTH / 2, 0, ROAD_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &verticalRoad);
    
    SDL_Rect horizontalRoad = {0, SCREEN_HEIGHT / 2 - ROAD_WIDTH / 2, SCREEN_WIDTH, ROAD_WIDTH};
    SDL_RenderFillRect(renderer, &horizontalRoad);
}

int main(int argc, char* argv[]) {
    simulateTraffic();
    return 0;
}

void simulateTraffic() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    
    SDL_Window *window = SDL_CreateWindow("Traffic Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return;
    }
    //SDL_RenderSetScale(renderer, 0.9, 0.9);
    bool running = true;
    SDL_Event event;
    int frameCounter = 0;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        
        frameCounter++;
        SDL_SetRenderDrawColor(renderer, 0, 200, 200, 255);
        SDL_RenderClear(renderer);        
        drawIntersection(renderer);
        
        
        if (frameCounter % 30 == 0) {
            createVehicle();
        }
        
        updateVehicles();
        
        for (int i = 0; i < MAX_VEHICLES; i++) {
            if (vehicles[i].active) {
                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                SDL_RenderFillRect(renderer, &vehicles[i].rect);
            }
        }
        
        updateTrafficLight();
        drawTrafficLightIndicator(renderer);
        
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
