#include <iostream>
#include "SDL2/SDL.h"
#include "snake_context.h"
#include <thread>
#include <mutex>
#define SDL_TOTAL_WIDTH (SNAKE_BLOCK_SIZE_IN_PIXELS * SNAKE_GAME_WIDTH)
#define SDL_TOTAL_HEIGHT (SNAKE_BLOCK_SIZE_IN_PIXELS * SNAKE_GAME_HEIGHT)
#define SNAKE_STEP_RATE_IN_MS 100 ///HELP ME PLS
std::mutex mtx;
bool is_stopped = false;

struct MainLoop{
    SDL_Renderer *renderer;
    Snake *snake, *snake2;
    Food* food;
    MainLoop(){
        snake = new Snake;
        snake2 = new Snake;
        food = new Food;
    }
};

bool KeyboardHandling(SDL_KeyboardEvent *key, MainLoop *payload){
//    if(snake_id) {
        switch (key->keysym.sym) {
            case SDLK_LEFT:
                Snake::Redirection(payload->snake2, SNAKE_DIR_LEFT);
                return true;
            case SDLK_UP:
                Snake::Redirection(payload->snake2, SNAKE_DIR_UP);
                return true;
            case SDLK_RIGHT:
                Snake::Redirection(payload->snake2, SNAKE_DIR_RIGHT);
                return true;
            case SDLK_DOWN:
                Snake::Redirection(payload->snake2, SNAKE_DIR_DOWN);
                return true;
            case SDLK_ESCAPE:
                return false;
//            default:
//                return true;
//        }
//    } else{
//        switch (key->keysym.sym) {
            case SDLK_a:
                Snake::Redirection(payload->snake, SNAKE_DIR_LEFT);
                return true;
            case SDLK_w:
                Snake::Redirection(payload->snake, SNAKE_DIR_UP);
                return true;
            case SDLK_d:
                Snake::Redirection(payload->snake, SNAKE_DIR_RIGHT);
                return true;
            case SDLK_s:
                Snake::Redirection(payload->snake, SNAKE_DIR_DOWN);
                return true;
//            case SDLK_ESCAPE:
//                return false;
            default:
                return true;
        }
//    }
}

void CreateGrid(SDL_Renderer *renderer){ /// ===========Function to Render Grid at the beginning============
    for(size_t i = 0; i < SNAKE_MATRIX_SIZE; i++){
        for(size_t j = 0; j < SNAKE_MATRIX_SIZE; j+=20) {
            SDL_Rect background_RECT;
            background_RECT.x = j;
            background_RECT.y = i * 20;
            background_RECT.w = 18;
            background_RECT.h = 18;

            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
            SDL_RenderFillRect(renderer, &background_RECT);
        }
        if(i != 35) {
            SDL_Rect ver_lines_RECT;
            ver_lines_RECT.x = i * 20 + 18;
            ver_lines_RECT.y = 0;
            ver_lines_RECT.w = 2;
            ver_lines_RECT.h = 720;

            SDL_Rect hor_lines_RECT;
            hor_lines_RECT.x = 0;
            hor_lines_RECT.y = i * 20 + 18;
            hor_lines_RECT.w = 720;
            hor_lines_RECT.h = 2;

            SDL_SetRenderDrawColor(renderer, 145, 0, 111, 255);
            SDL_RenderFillRect(renderer, &hor_lines_RECT);
            SDL_RenderFillRect(renderer, &ver_lines_RECT);
        }
    }
    SDL_RenderPresent(renderer);
}

int sdl_main_loop(MainLoop *payload){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch (e.type) {
            case SDL_QUIT:{
                return 0;
            }
            case SDL_USEREVENT:
                return 1;
            case SDL_KEYDOWN:
                return KeyboardHandling(&e.key, payload);
        }
    }
    return 1;
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

#pragma region ====================RENDERS======================
void SnakeRender(Snake *snake, SDL_Renderer *renderer){
    SDL_Rect head;
    head.x = snake->body.pos[0].first * 20;
    head.y = snake->body.pos[0].second * 20;
    head.w = 18;
    head.h = 18;
    SDL_SetRenderDrawColor(renderer, 0, 225, 0, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
    for(size_t i = 1; i < snake->body.length - 1; i++){
        SDL_Rect tail;
        tail.x = snake->body.pos[i].first * 20;
        tail.y = snake->body.pos[i].second * 20;
        tail.w = 18;
        tail.h = 18;

        SDL_RenderFillRect(renderer, &tail);
    }
    SDL_Rect prev_cell;
    prev_cell.x = snake->body.prev_cell.first * 20;
    prev_cell.y = snake->body.prev_cell.second * 20;
    prev_cell.w = 18;
    prev_cell.h = 18;
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(renderer, &prev_cell);
}

void MainRender(MainLoop &loop_payload){ /// =============Function to render Snake=============
    std::thread th1([&loop_payload](){
        SnakeRender(loop_payload.snake, loop_payload.renderer);
    });
    std::thread th2([&loop_payload](){
        SnakeRender(loop_payload.snake2, loop_payload.renderer);
    });
    for(int i = 0; i < loop_payload.food->pos.size(); i++) {
        SDL_Rect foods;
        foods.x = loop_payload.food->pos[i].first * 20;
        foods.y = loop_payload.food->pos[i].second * 20;
        foods.w = 18;
        foods.h = 18;
        SDL_SetRenderDrawColor(loop_payload.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(loop_payload.renderer, &foods);
    }
    th1.join(); th2.join();
    SDL_RenderPresent(loop_payload.renderer);
}
#pragma endregion

void ClearSnake(SDL_Renderer *renderer, Snake* snake){
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    for(size_t i = 0; i < snake->body.length; i++){
        SDL_Rect tail;
        tail.x = snake->body.pos[i].first * 20;
        tail.y = snake->body.pos[i].second * 20;
        tail.w = 18;
        tail.h = 18;
        SDL_RenderFillRect(renderer, &tail);
    }
}

void SnakeMoveHandling(MainLoop &loop_payload){
//    std::vector<std::thread> threads(2);
//    for(size_t i = 0; i < threads.size(); i++){
//        threads[i] = std::thread([&i, &loop_payload](){
    Snake::Init(loop_payload.snake, false);
    Snake::Init(loop_payload.snake2, true);
    Food::NewFoodPos(loop_payload.snake, loop_payload.food);
    MainRender(loop_payload);
//    std::thread th1([&loop_payload](){
//        while(true){
//            if(!sdl_main_loop(&loop_payload)) {
//                is_stopped = true;
//                break;
//            }
//        }
//    });

    while(sdl_main_loop(&loop_payload)) {
        std::thread th2([&loop_payload]() {
            Snake::Move(loop_payload.snake, loop_payload.food);
            if (IsKilled(loop_payload.snake, loop_payload.snake2, loop_payload.food)) {
                ClearSnake(loop_payload.renderer, loop_payload.snake);
                Snake::Init(loop_payload.snake, false);
            }
        });
        std::thread th3([&loop_payload]() {
            Snake::Move(loop_payload.snake2, loop_payload.food);
            if (IsKilled(loop_payload.snake2, loop_payload.snake, loop_payload.food)) {
                ClearSnake(loop_payload.renderer, loop_payload.snake2);
                Snake::Init(loop_payload.snake2, true);
            }
        });
        th2.join(); th3.join();
        MainRender(loop_payload);
        SDL_Delay(50);
    }
//    th1.detach();
//        });
//    }
//    for(auto &i : threads){
//        i.join();
//    }


}

void MainSDLFunc(SDL_Window *window, MainLoop &loop_payload){

    window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
                              718,                               // width, in pixels
                              718,                               // height, in pixels
                              SDL_WINDOW_OPENGL);
    loop_payload.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    CreateGrid(loop_payload.renderer);

    if(loop_payload.renderer == nullptr) {
        throw std::runtime_error("renderer");
    }

    SnakeMoveHandling(loop_payload);
}

int main(int argc, char** argv) {
    SDL_Window *window = nullptr;
    SDL_TimerID  stop_timer;
    MainLoop loop_payload;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        throw std::runtime_error("ERROR: SDL_INIT_VIDEO");
    }

    MainSDLFunc(window, loop_payload);

    SDL_RemoveTimer(stop_timer);
    SDL_DestroyRenderer(loop_payload.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
