//#include "Game.h"

//MainLoop::MainLoop() {
//    snake = new Snake;
//    snake2 = new Snake;
//    food = new Food;
//}

//bool KeyboardHandling(SDL_KeyboardEvent *key, MainLoop *payload){
//    switch (key->keysym.sym) {
//        case SDLK_LEFT:
//            Snake::Redirection(payload->snake2, SNAKE_DIR_LEFT);
//            return true;
//        case SDLK_UP:
//            Snake::Redirection(payload->snake2, SNAKE_DIR_UP);
//            return true;
//        case SDLK_RIGHT:
//            Snake::Redirection(payload->snake2, SNAKE_DIR_RIGHT);
//            return true;
//        case SDLK_DOWN:
//            Snake::Redirection(payload->snake2, SNAKE_DIR_DOWN);
//            return true;
//        case SDLK_ESCAPE:
//            return false;
//        case SDLK_a:
//            Snake::Redirection(payload->snake, SNAKE_DIR_LEFT);
//            return true;
//        case SDLK_w:
//            Snake::Redirection(payload->snake, SNAKE_DIR_UP);
//            return true;
//        case SDLK_d:
//            Snake::Redirection(payload->snake, SNAKE_DIR_RIGHT);
//            return true;
//        case SDLK_s:
//            Snake::Redirection(payload->snake, SNAKE_DIR_DOWN);
//            return true;
//        default:
//            return true;
//    }
//}

//void CreateGrid(SDL_Renderer *renderer){ /// ===========Function to Render Grid at the beginning============
//    for(size_t i = 0; i < SNAKE_MATRIX_SIZE; i++){
//        for(size_t j = 0; j < SNAKE_MATRIX_SIZE; j+=20) {
//            SDL_Rect background_RECT;
//            background_RECT.x = j;
//            background_RECT.y = i * 20;
//            background_RECT.w = 18;
//            background_RECT.h = 18;
//
//            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
//            SDL_RenderFillRect(renderer, &background_RECT);
//        }
//        if(i != 35) {
//            SDL_Rect ver_lines_RECT;
//            ver_lines_RECT.x = i * 20 + 18;
//            ver_lines_RECT.y = 0;
//            ver_lines_RECT.w = 2;
//            ver_lines_RECT.h = 720;
//
//            SDL_Rect hor_lines_RECT;
//            hor_lines_RECT.x = 0;
//            hor_lines_RECT.y = i * 20 + 18;
//            hor_lines_RECT.w = 720;
//            hor_lines_RECT.h = 2;
//
//            SDL_SetRenderDrawColor(renderer, 145, 0, 111, 255);
//            SDL_RenderFillRect(renderer, &hor_lines_RECT);
//            SDL_RenderFillRect(renderer, &ver_lines_RECT);
//        }
//    }
//    SDL_RenderPresent(renderer);
//}
//
//int sdl_main_loop(MainLoop *payload){
//    SDL_Event e;
//    while(SDL_PollEvent(&e)){
//        switch (e.type) {
//            case SDL_QUIT:{
//                return 0;
//            }
//            case SDL_USEREVENT:
//                return 1;
//            case SDL_KEYDOWN:
//                return KeyboardHandling(&e.key, payload);
//        }
//    }
//    return 1;
//};