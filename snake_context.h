#pragma once

#include <cstdlib>
#include <cstdint>
#include <vector>

const static uint32_t SNAKE_GAME_WIDTH = 36;
const static uint32_t SNAKE_GAME_HEIGHT = 36;
const static uint32_t SNAKE_STEP_RATE = 125;
const static uint32_t SNAKE_BLOCK_SIZE_IN_PIXELS = 20;
const static uint32_t SNAKE_MATRIX_SIZE = (SNAKE_GAME_WIDTH * SNAKE_GAME_HEIGHT);
const static uint32_t SNAKE_START_SIZE = 7;
const static uint32_t FOOD_MAX_NUMBER = 2;

enum Direction{
    SNAKE_DIR_RIGHT,
    SNAKE_DIR_UP,
    SNAKE_DIR_LEFT,
    SNAKE_DIR_DOWN
};

struct Food;
class Snake;
static bool IsFoodInsideSnake(Snake *ctx, Food* food);
struct Food {
    std::vector<std::pair<int, int>> pos;
    static void NewFoodPos(Snake *ctx, Food *food){
        if(food->pos.size() > FOOD_MAX_NUMBER) return;
        srand(time(nullptr));
        int x = rand() % SNAKE_GAME_WIDTH, y = rand() % SNAKE_GAME_HEIGHT;
        food->pos.emplace_back(x, y);
        if(!IsFoodInsideSnake(ctx, food)){
            return;
        }

    }
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

    static void Init(Snake *ctx, bool snake_id){
        ctx->body.pos.reserve(SNAKE_MATRIX_SIZE);
        ctx->body.dir = ctx->body.prev_dir = Direction::SNAKE_DIR_UP;
        ctx->body.length = SNAKE_START_SIZE;
        srand(time(nullptr));
        int spawn_place = rand() % SNAKE_GAME_WIDTH / 2;
        if(snake_id) spawn_place += SNAKE_GAME_WIDTH / 4;
        ctx->body.pos.resize(ctx->body.length);
        for(int i = 0; i < ctx->body.length - 1; ++i){
            ctx->body.pos[i] = std::make_pair(spawn_place, i + 8);
        }
    }

    static void Move(Snake *ctx, Food *food){
        ctx->body.prev_cell = ctx->body.pos[ctx->body.length - 1];
        for(int i = ctx->body.length - 1; i > 0; --i){
            ctx->body.pos[i].first = ctx->body.pos[i - 1].first;
            ctx->body.pos[i].second = ctx->body.pos[i - 1].second;
        }

        switch (ctx->body.dir) {
            case SNAKE_DIR_RIGHT:
                ctx->body.pos[0].first++;
                break;
            case SNAKE_DIR_UP:
                ctx->body.pos[0].second--;
                break;
            case SNAKE_DIR_LEFT:
                ctx->body.pos[0].first--;
                break;
            case SNAKE_DIR_DOWN:
                ctx->body.pos[0].second++;
                break;
        }

        ctx->body.prev_dir = ctx->body.dir;

///     wall?
        if(ctx->body.pos[0].first == SNAKE_GAME_WIDTH){
            ctx->body.pos[0].first = 0;
        } else if(ctx->body.pos[0].first == -1){
            ctx->body.pos[0].first = SNAKE_GAME_WIDTH - 1;
        } else if (ctx->body.pos[0].second == SNAKE_GAME_HEIGHT){
            ctx->body.pos[0].second = 0;
        } else if (ctx->body.pos[0].second == -1){
            ctx->body.pos[0].second = SNAKE_GAME_HEIGHT - 1;
        }

///     food
        for(int i = 0; i < food->pos.size(); i++) {
            if (food->pos[i].first == ctx->body.pos[0].first && food->pos[i].second == ctx->body.pos[0].second) {
                Food::NewFoodPos(ctx, food);
                ++ctx->body.length;
                food->pos.erase(food->pos.begin() + i);
            }
        }
    }

    static void Redirection(Snake *ctx, Direction dir){
        if(dir == SNAKE_DIR_RIGHT && ctx->body.prev_dir != SNAKE_DIR_LEFT){ ///!!!!!!!!!!!!!
            ctx->body.dir = SNAKE_DIR_RIGHT;
        }else if (dir == SNAKE_DIR_DOWN && ctx->body.prev_dir != SNAKE_DIR_UP){
            ctx->body.dir = SNAKE_DIR_DOWN;
        } else if (dir == SNAKE_DIR_LEFT && ctx->body.prev_dir != SNAKE_DIR_RIGHT){
            ctx->body.dir = SNAKE_DIR_LEFT;
        }else if (dir == SNAKE_DIR_UP && ctx->body.prev_dir != SNAKE_DIR_DOWN){
            ctx->body.dir = SNAKE_DIR_UP;
        }
    }
};

static bool IsFoodInsideSnake(Snake *ctx, Food* food){
    for(int i = 0; i < ctx->body.length; ++i){
        for(int j = 0; j < food->pos.size(); j++) {
            if (food->pos[j].first == ctx->body.pos[i].first && food->pos[j].second == ctx->body.pos[i].second) {
                return true;
            }
        }
    } return false;
}

static bool IsKilled(Snake *ctx, Snake *ctx2, Food* food) {
    for (int i = 1; i < ctx->body.length; ++i) {
        if (ctx->body.pos[0].first == ctx->body.pos[i].first && ctx->body.pos[0].second == ctx->body.pos[i].second) {
            food->pos.emplace_back(ctx->body.pos[1].first, ctx->body.pos[1].second);
            return true;
        }
    }
    for(int i = 0; i < ctx2->body.length; i++){
        if (ctx->body.pos[0].first == ctx2->body.pos[i].first && ctx->body.pos[0].second == ctx2->body.pos[i].second) {
            food->pos.emplace_back(ctx->body.pos[1].first, ctx->body.pos[1].second);
            return true;
        }
    }
    return false;
}