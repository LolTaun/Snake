#include "Game.h"
#include "SDL_ttf/SDL_ttf.h"

int main(int argc, char** argv) {
    SDL_Window *window = nullptr;
    SDL_TimerID  stop_timer;
    MainLoop loop_payload;

//    SDL_Window *score_window = nullptr;
//
//    SDL_Renderer *renderer;
//    TTF_Font* Sans = TTF_OpenFont("/home/laptop-cajs/CLionProjects/3rd_sem/Snake/OpenSans-Light.ttf", 24);
//    SDL_Color white = {255, 255, 255};
//    SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, "Some text", white);
//    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface_message);
//    SDL_Rect Message_rect;
//    Message_rect.x = 0;
//    Message_rect.y = 0;
//    Message_rect.w = 100;
//    Message_rect.h = 100;
//    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
//    SDL_FreeSurface(surface_message);
//    SDL_DestroyTexture(Message);


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

    MainSDLFunc(window, loop_payload);

    SDL_RemoveTimer(stop_timer);
    SDL_DestroyRenderer(loop_payload.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
