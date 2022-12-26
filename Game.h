#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "snake_context.h"
#include <thread>
const static uint8_t GAME_COOLDOWN = 75;

struct MainLoop{
    SDL_Renderer *renderer = nullptr, *score_renderer = nullptr;
    Snake *snake, *snake2;
    Food* food;
    MainLoop(){
        snake = new Snake;
        snake2 = new Snake;
        food = new Food;
    };
};

bool KeyboardHandling(SDL_KeyboardEvent *key, MainLoop *payload){
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
        default:
            return true;
    }
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
};

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
}

void CreateMainWindow(SDL_Window *window, MainLoop &loop_payload);

void CreateScoreWindow(SDL_Window *window, MainLoop &loop_payload);

#pragma region ====================RENDERS======================
void SnakeRender(Snake *snake, SDL_Renderer *renderer, bool snake_id){
    SDL_Rect head;
    head.x = snake->body.pos[0].first * 20;
    head.y = snake->body.pos[0].second * 20;
    head.w = 18;
    head.h = 18;
    if(snake_id) {
        SDL_SetRenderDrawColor(renderer, 0, 225, 0, 255);
        SDL_RenderFillRect(renderer, &head);
        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
    } else{
        SDL_SetRenderDrawColor(renderer, 60, 60, 225, 255);
        SDL_RenderFillRect(renderer, &head);
        SDL_SetRenderDrawColor(renderer, 60, 60, 150, 255);
    }
    for(size_t i = 1; i < snake->body.length; i++){
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
//    std::thread th1([&loop_payload](){
//        SnakeRender(loop_payload.snake, loop_payload.renderer, false);
//    });
//    std::thread th2([&loop_payload](){
//        SnakeRender(loop_payload.snake2, loop_payload.renderer, true);
//    });
    SnakeRender(loop_payload.snake, loop_payload.renderer, false); /// FOR DEBUGGING PURPOSES
    SnakeRender(loop_payload.snake2, loop_payload.renderer, true); /// FOR DEBUGGING PURPOSES
    for(int i = 0; i < loop_payload.food->pos.size(); i++) {
        SDL_Rect foods;
        foods.x = loop_payload.food->pos[i].first * 20;
        foods.y = loop_payload.food->pos[i].second * 20;
        foods.w = 18;
        foods.h = 18;
        SDL_SetRenderDrawColor(loop_payload.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(loop_payload.renderer, &foods);
    }
//    th1.join(); th2.join();
    SDL_RenderPresent(loop_payload.renderer);
}

void ScoreRender(MainLoop &loop_payload){
    SDL_RenderClear(loop_payload.score_renderer);

    TTF_Font* Sans = TTF_OpenFont("../OpenSans-Medium.ttf", 125);
    SDL_Color player1 = {60, 60, 225};
    SDL_Color player2 = {0, 225, 0};
    SDL_Surface* surface_message;
    SDL_Texture* Message;
    SDL_Rect Message_rect;

//    SDL_RenderFillRect(loop_payload.renderer, &surface_message);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake->body.length).c_str(), player1);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 30;
    Message_rect.y = 60;
    Message_rect.w = 20;
    Message_rect.h = 30;
    SDL_SetRenderDrawColor(loop_payload.renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(loop_payload.renderer, &Message_rect);
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake2->body.length).c_str(), player2);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 658;
    Message_rect.y = 60;
    Message_rect.w = 20;
    Message_rect.h = 30;
    SDL_RenderFillRect(loop_payload.renderer, &Message_rect);
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);


    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(Message);
    SDL_RenderPresent(loop_payload.score_renderer);
}

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
#pragma endregion

void SnakeMoveHandling(SDL_Window *window, MainLoop &loop_payload){
    Snake::Init(loop_payload.snake, false);
    Snake::Init(loop_payload.snake2, true);
    Food::NewFoodPos(loop_payload.snake, loop_payload.snake2, loop_payload.food);
    MainRender(loop_payload);

    while(sdl_main_loop(&loop_payload)) {
            Uint64 start = SDL_GetPerformanceCounter();
//        if(loop_payload.snake->body.pos[0].first == loop_payload.snake2->body.pos[0].first &&
//            loop_payload.snake->body.pos[0].second == loop_payload.snake2->body.pos[0].second){
//
//        } else {

                std::thread th2([&loop_payload]() {Snake::Move(loop_payload.snake, loop_payload.snake2, loop_payload.food);});
                std::thread th3([&loop_payload]() {Snake::Move(loop_payload.snake2, loop_payload.snake, loop_payload.food);});
                th2.join(); th3.join();
                if(HandleHeadCollision(loop_payload.snake, loop_payload.snake2)) {
                std::thread th2_2([&loop_payload]() {
                    if (IsKilled(loop_payload.snake, loop_payload.snake2, loop_payload.food, loop_payload.renderer)) {
                        ClearSnake(loop_payload.renderer, loop_payload.snake);
                        Snake::ReInit(loop_payload.snake, false);
                    }
                });
                std::thread th3_2([&loop_payload]() {
                    if (IsKilled(loop_payload.snake2, loop_payload.snake, loop_payload.food, loop_payload.renderer)) {
                        ClearSnake(loop_payload.renderer, loop_payload.snake2);
                        Snake::ReInit(loop_payload.snake2, true);
                    }
                });
                th2_2.join(); th3_2.join();
            } else {
                    ClearSnake(loop_payload.renderer, loop_payload.snake);
                    ClearSnake(loop_payload.renderer, loop_payload.snake2);
                    Snake::ReInit(loop_payload.snake, false);
                    Snake::ReInit(loop_payload.snake2, true);
                }
            CreateGrid(loop_payload.renderer); /// ====FOR DEBUGGING PURPOSES====
            MainRender(loop_payload);
            loop_payload.snake->score.UpdateScore(); loop_payload.snake2->score.UpdateScore();
            CreateScoreWindow(window, loop_payload);
            Uint64 end = SDL_GetPerformanceCounter();
            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
            if(GAME_COOLDOWN - elapsedMS > 0) {
                SDL_Delay(GAME_COOLDOWN - elapsedMS);
            }
//        }
    }
}

#pragma region Create Windows
void CreateMainWindow(SDL_Window *window, MainLoop &loop_payload){
    window = SDL_CreateWindow("SNAKE 2.0", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
                              718,                               // width, in pixels
                              718,                               // height, in pixels
                              SDL_WINDOW_OPENGL);
    loop_payload.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    CreateGrid(loop_payload.renderer);
}

void CreateScoreWindow(SDL_Window *window, MainLoop &loop_payload){

    SDL_SetRenderDrawColor(loop_payload.score_renderer, 0, 0, 0, 0);
    SDL_RenderClear(loop_payload.score_renderer);


    TTF_Font* Sans = TTF_OpenFont("../OpenSans-Medium.ttf", 24);
    SDL_Color white = {255, 255, 255};
    SDL_Color player1 = {60, 60, 225};
    SDL_Color player2 = {0, 225, 0};


    SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, "Player 1", player1);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, "Player 2", player2);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = (718 - surface_message->w);
    Message_rect.y = 0;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

#pragma region Score
    surface_message = TTF_RenderText_Solid(Sans, "Score", white);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = (718 - surface_message->w) / 2;
    Message_rect.y = 30;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake->score.score).c_str(), player1);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 30;
    Message_rect.y = 30;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake2->score.score).c_str(), player2);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 688 - surface_message->w;
    Message_rect.y = 30;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);
#pragma endregion

#pragma region current size
    surface_message = TTF_RenderText_Solid(Sans, "Current size", white);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = (718 - surface_message->w) / 2;
    Message_rect.y = 60;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake->body.length).c_str(), player1);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 30;
    Message_rect.y = 60;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake2->body.length).c_str(), player2);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 688-surface_message->w;
    Message_rect.y = 60;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);
#pragma endregion

#pragma region Max size
    surface_message = TTF_RenderText_Solid(Sans, "Max size", white);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = (718 - surface_message->w) / 2;
    Message_rect.y = 90;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake->score.max_size).c_str(), player1);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 30;
    Message_rect.y = 90;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake2->score.max_size).c_str(), player2);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 688 - surface_message->w;
    Message_rect.y = 90;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);
#pragma endregion

#pragma region Kill count
    surface_message = TTF_RenderText_Solid(Sans, "Kill count", white);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = (718 - surface_message->w) / 2;
    Message_rect.y = 120;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake->score.kill_count).c_str(), player1);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 30;
    Message_rect.y = 120;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);

    surface_message = TTF_RenderText_Solid(Sans, std::to_string(loop_payload.snake2->score.kill_count).c_str(), player2);
    Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
    Message_rect.x = 688 - surface_message->w;
    Message_rect.y = 120;
    Message_rect.w = surface_message->w;
    Message_rect.h = 30;
    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);
#pragma endregion

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(Message);
    SDL_RenderPresent(loop_payload.score_renderer);
}
#pragma endregion

void MainSDLFunc(SDL_Window *window, SDL_Window *score_window, MainLoop &loop_payload){

    CreateMainWindow(window, loop_payload);

    TTF_Init();
    score_window = SDL_CreateWindow("Score", 600,
                              30,           // initial y position
                              718,                               // width, in pixels
                              150,                               // height, in pixels
                              SDL_WINDOW_OPENGL);
    loop_payload.score_renderer = SDL_CreateRenderer(score_window, -1, SDL_RENDERER_ACCELERATED);
    CreateScoreWindow(score_window, loop_payload);

    if(loop_payload.renderer == nullptr) {
        throw std::runtime_error("renderer");
    }

    SnakeMoveHandling(score_window, loop_payload);
}
