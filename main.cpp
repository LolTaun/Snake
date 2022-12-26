#include "Game.h"


int main(int argc, char** argv) {
    SDL_Window *window = nullptr;
    SDL_TimerID  stop_timer;
    MainLoop loop_payload;

    SDL_Window *score_window = nullptr;

//    SDL_Renderer *renderer;
//    score_window = SDL_CreateWindow("Score", SDL_WINDOWPOS_UNDEFINED,
//                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
//                              718,                               // width, in pixels
//                              100,                               // height, in pixels
//                              SDL_WINDOW_OPENGL);
//    loop_payload.score_renderer = SDL_CreateRenderer(score_window, -1, SDL_RENDERER_ACCELERATED);
//    TTF_Init();
//    TTF_Font* Sans = TTF_OpenFont("../OpenSans-Light.ttf", 124);
//    SDL_Color white = {255, 255, 255};
//    SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, "Ilya Molodec!", white);
//    SDL_Texture* Message = SDL_CreateTextureFromSurface(loop_payload.score_renderer, surface_message);
//    SDL_Rect Message_rect;
//    Message_rect.x = 0;
//    Message_rect.y = 0;
//    Message_rect.w = 150;
//    Message_rect.h = 30;
//    SDL_RenderCopy(loop_payload.score_renderer, Message, NULL, &Message_rect);
//    SDL_FreeSurface(surface_message);
//    SDL_DestroyTexture(Message);
//    SDL_RenderPresent(loop_payload.score_renderer);


//    std::string score_text = "score: " + std::to_string(25);
//    SDL_Color textColor = { 255, 255, 255, 0 };
//    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
//    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
//    int text_width = textSurface->w;
//    int text_height = textSurface->h;
//    SDL_FreeSurface(textSurface);
//    SDL_Rect renderQuad = { 20, win_height - 30, text_width, text_height };
//    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
//    SDL_DestroyTexture(text);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        throw std::runtime_error("ERROR: SDL_INIT_VIDEO");
    }

    MainSDLFunc(window, score_window, loop_payload);

    SDL_RemoveTimer(stop_timer);
    SDL_DestroyRenderer(loop_payload.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
