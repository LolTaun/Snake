#include <iostream>
#include <SDL2/SDL.h>
#include "snake+direction.h"
#include "snake_context.h"
#define SDL_TOTAL_WIDTH (SNAKE_BLOCK_SIZE_IN_PIXELS * SNAKE_GAME_WIDTH)
#define SDL_TOTAL_HEIGHT (SNAKE_BLOCK_SIZE_IN_PIXELS * SNAKE_GAME_HEIGHT)
#define SNAKE_STEP_RATE_IN_MS 100 ///HELP ME PLS
struct MainLoop{
    SDL_Renderer *renderer;
    Snake *snake;

};

int sdl_main_loop(MainLoop *payload){
    SDL_Event e;
    SDL_Rect r;
    while(SDL_PollEvent(&e)){
        switch (e.type) {
            case SDL_QUIT:{
                return 0;
            }
            case SDL_USEREVENT:
                Snake::snake_context_step(&payload->snake);
                break;
            case SDL_KEYDOWN:{
                //////// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
            }
        }
    }
};

uint32_t sdl_timer_callback(uint32_t interval, void *payload){
    SDL_Event e;
    SDL_UserEvent userEvent;
    userEvent.type = SDL_USEREVENT;
    userEvent.code = 0;
    userEvent.data1 = nullptr;
    userEvent.data2 = nullptr;
    e.type = SDL_USEREVENT;
    /// sth!!!
}


int main() {
    SDL_Window *window = nullptr;
    SDL_TimerID  stop_timer;
    MainLoop loop_payload;
    srand(time(nullptr));
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        throw std::runtime_error("ERROR: SDL_INIT_VIDEO");
    }
    window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED
                                       SDL_WINDOWPOS_UNDEFINED,           // initial y position
                               640,                               // width, in pixels
                               480,                               // height, in pixels
                               SDL_WINDOW_OPENG)
    loop_payload.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_);

    if(loop_payload.renderer = nullptr){
        throw std::runtime_error("renderer");
    }
    Snake::snake_context_initialize(loop_payload.snake);
    stop_timer = SDL_AddTimer(SNAKE_STEP_RATE_IN_MS, sdl_timer_callback, NULL); /// FIX ME PLS
    if(stop_timer == 0){
        throw std::runtime_error("step_timer");
    }

    while(sdl_main_loop(&loop_payload)){

    }
    SDL_RemoveTimer(stop_timer);
    SDL_DestroyRenderer(loop_payload.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;



//    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
//
//    // Create an application window with the following settings:
//    window = SDL_CreateWindow(
//            "An SDL2 window",                  // window title
//            SDL_WINDOWPOS_UNDEFINED,           // initial x position
//            SDL_WINDOWPOS_UNDEFINED,           // initial y position
//            640,                               // width, in pixels
//            480,                               // height, in pixels
//            SDL_WINDOW_OPENGL                  // flags - see below
//    );
//
//    // Check that the window was successfully created
//    if (window == NULL) {
//        // In the case that the window could not be made...
//        printf("Could not create window: %s\n", SDL_GetError());
//        return 1;
//    }
//
//    // The window is open: could enter program loop here (see SDL_PollEvent())
//
//    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
//
//    // Close and destroy the window
//    SDL_DestroyWindow(window);
//
//    // Clean up
//    SDL_Quit();

    return 0;
}
