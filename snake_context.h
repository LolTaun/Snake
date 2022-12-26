#pragma once

#include <cstdlib>
#include <cstdint>
#include <vector>
#include <map>
#include <ctime>
#include "SDL2/SDL.h"

const static uint32_t SNAKE_GAME_WIDTH = 36;
const static uint32_t SNAKE_GAME_HEIGHT = 36;
const static uint32_t SNAKE_MATRIX_SIZE = (SNAKE_GAME_WIDTH * SNAKE_GAME_HEIGHT);
const static uint32_t SNAKE_START_SIZE = 7;
const static uint32_t FOOD_MAX_NUMBER = 3;
const static uint32_t SNAKE_MIN_LENGTH = 3;

enum Direction{
    SNAKE_DIR_RIGHT,
    SNAKE_DIR_UP,
    SNAKE_DIR_LEFT,
    SNAKE_DIR_DOWN
};

struct Food;
class Snake;

static bool IsFoodInsideSnake(Snake *snake, Snake *snake2, Food* food);

struct Food {
    std::vector<std::pair<int, int>> pos;
    static void NewFoodPos(Snake *ctx, Snake *ctx2, Food *food);
};

class Snake{
public:
    struct Body{
        int length;
        Direction prev_dir;
        Direction dir;
        std::vector<std::pair<int, int>> pos;
        std::pair<int, int> prev_cell{0, 0};
    } body;
    struct scores{
        int score = 0;
        int kill_count = 0;
        int max_size = SNAKE_START_SIZE;
        int food_eaten = 0;
        void UpdateScore();
    } score;


    static void Init(Snake *ctx, bool snake_id);

    static void ReInit(Snake *ctx, bool snake_id);

    static void GrowUp(Snake *ctx);

    static void Move(Snake *ctx, Snake *ctx2, Food *food);

    static void Redirection(Snake *ctx, Direction dir);
};

static bool HandleHeadCollision(Snake *ctx1, Snake *ctx2){
    if( (ctx1->body.pos[0] == ctx2->body.pos[0]) || (ctx1->body.pos[0] == ctx2->body.pos[1] && ctx2->body.pos[0] == ctx1->body.pos[1]) ){
        --ctx1->score.kill_count;
        --ctx2->score.kill_count;
        return false;
    }
    return true;
}


static bool IsKilled(Snake *ctx, Snake *ctx2, Food* food, SDL_Renderer *renderer){
    for (int i = 1; i < ctx->body.length; ++i) {
        if (ctx->body.pos[0] == ctx->body.pos[i]) {
            --ctx->score.kill_count;
            return true;
        }
    }

    for(int i = 0; i < ctx2->body.length; i++){
        if (ctx->body.pos[0] == ctx2->body.pos[i]) {
            Snake::GrowUp(ctx);

            for(int j = i + 1; j < ctx2->body.length; j++){
                food->pos.push_back(ctx2->body.pos[j]);
            }
            ctx2->body.length = i;
            ctx2->body.pos.resize(i);
            if(i < SNAKE_MIN_LENGTH) {
                ++ctx->score.kill_count;
                ctx2->ReInit(ctx2, false);
            }
//            food->pos.emplace_back(ctx->body.pos[1].first, ctx->body.pos[1].second);
//            returna true;
        }
    }
    return false;
}

//bool HandleHeadCollision(Snake *ctx1, Snake *ctx2);
