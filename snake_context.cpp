#include "snake_context.h"

void Food::NewFoodPos(Snake *ctx, Snake *ctx2, Food *food) {
    if(food->pos.size() > FOOD_MAX_NUMBER - 1) return;
    srand(time(nullptr));
    while(true){

        int x = rand() % SNAKE_GAME_WIDTH, y = rand() % SNAKE_GAME_HEIGHT;
        food->pos.emplace_back(x, y);
        if (!IsFoodInsideSnake(ctx, ctx2, food)) {
            return;
        } else food->pos.erase(food->pos.begin() + food->pos.size() - 1);
    }

}

void Snake::Init(Snake *ctx, bool snake_id) {
    ctx->body.pos.reserve(SNAKE_MATRIX_SIZE);
    ReInit(ctx, snake_id);
}

void Snake::ReInit(Snake *ctx, bool snake_id) {
    ctx->body.dir = ctx->body.prev_dir = Direction::SNAKE_DIR_UP;
    ctx->body.length = SNAKE_START_SIZE;
    ctx->body.pos.resize(SNAKE_START_SIZE);
    srand(time(nullptr));
    int spawn_place = rand() % SNAKE_GAME_WIDTH / 2;
    if(snake_id) spawn_place = SNAKE_GAME_WIDTH - spawn_place;
    ctx->body.pos.resize(ctx->body.length);
    for(int i = 0; i < ctx->body.length - 1; ++i){
        ctx->body.pos[i] = std::make_pair(spawn_place, i + 8);
    }
}

void Snake::GrowUp(Snake *ctx) {
    ctx->body.length++;
    ctx->score.food_eaten++;
//        ctx->body.pos.resize(ctx->body.length);
    ctx->body.pos.push_back(ctx->body.prev_cell);
    if(ctx->score.max_size < ctx->body.length) ctx->score.max_size = ctx->body.length;
//        ctx->body.pos[ctx->body.length - 1] = ctx->body.prev_cell;
}

void Snake::Move(Snake *ctx, Snake *ctx2, Food *food) {
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

///     window border
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
        if (food->pos[i] == ctx->body.pos[0]) {
            food->pos.erase(food->pos.begin() + i);
            Food::NewFoodPos(ctx, ctx2, food);
            GrowUp(ctx);

        }
    }
}

void Snake::Redirection(Snake *ctx, Direction dir) {
    if(dir == SNAKE_DIR_RIGHT && ctx->body.prev_dir != SNAKE_DIR_LEFT){
        ctx->body.dir = SNAKE_DIR_RIGHT;
    }else if (dir == SNAKE_DIR_DOWN && ctx->body.prev_dir != SNAKE_DIR_UP){
        ctx->body.dir = SNAKE_DIR_DOWN;
    } else if (dir == SNAKE_DIR_LEFT && ctx->body.prev_dir != SNAKE_DIR_RIGHT){
        ctx->body.dir = SNAKE_DIR_LEFT;
    }else if (dir == SNAKE_DIR_UP && ctx->body.prev_dir != SNAKE_DIR_DOWN){
        ctx->body.dir = SNAKE_DIR_UP;
    }
}

bool IsFoodInsideSnake(Snake *snake, Snake *snake2, Food *food) {
    for(int i = 0; i < food->pos.size(); ++i) {
        for (int j = i + 1; j < food->pos.size(); j++) {
            if (food->pos[j] == food->pos[i]) {
                return true;
            }
        }
    }
    for(int i = 0; i < snake->body.length; ++i){
        for(int j = 0; j < food->pos.size(); j++) {
            if (food->pos[j] == snake->body.pos[i]) {
                return true;
            }
        }
    }
    for(int i = 0; i < snake2->body.length; ++i){
        for(int j = 0; j < food->pos.size(); j++) {
            if (food->pos[j] == snake2->body.pos[i]) return true;
        }
    }
    return false;
}

void Snake::scores::UpdateScore() {
    score = kill_count * 10 + (max_size - SNAKE_START_SIZE) * 2 + food_eaten;
}
