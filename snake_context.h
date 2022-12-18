#pragma once

#include <cstdlib>
#include <cstdint>
#include "snake+direction.h"
#define X_ 0
#define Y_ 1
const static uint32_t SNAKE_GAME_WIDTH = 36;
const static uint32_t SNAKE_GAME_HEIGHT = 36;
const static uint32_t SNAKE_STEP_RATE = 125;
const static uint32_t SNAKE_BLOCK_SIZE_IN_PIXELS = 20;
const static uint32_t SNAKE_MATRIX_SIZE = (SNAKE_GAME_WIDTH * SNAKE_GAME_HEIGHT);



class Snake{
public:
    struct Body{
        int length;
        Direction prev_dir;
        Direction dir;
        int pos[SNAKE_MATRIX_SIZE][2];
    } body;



    struct Food {
        int x;
        int y;
    } food;

    static void snake_context_initialize(Snake *ctx){
        ctx->body.dir = ctx->body.prev_dir = SNAKE_DIR_UP;
        ctx->body.length = 3;
        for(int i = 0; i < SNAKE_MATRIX_SIZE; ++i){
            ctx->body.pos[i][X_] = 8;
            ctx->body.pos[i][Y_] = 8;
        }
    }

    static bool snake_context_is_food_inside_snake(Snake *ctx){
        for(int i = 0; i < ctx->body.length; ++i){
            if(ctx->food.x == ctx->body.pos[i][X_] && ctx->food.y == ctx->body.pos[i][Y_]){
                return true;
            }
        }
    }

    static void snake_context_new_food_pos(Snake *ctx){
        while (true){
            ctx->food.x = rand() % SNAKE_GAME_WIDTH;
            ctx->food.y = rand() % SNAKE_GAME_HEIGHT;
            if(snake_context_is_food_inside_snake(ctx)){
                return;
            }

        }
    }

    static void snake_context_step(Snake *ctx){
        for(int i = ctx->body.length; i > 0; --i){
            ctx->body.pos[i][X_] = ctx->body.pos[i - 1][X_];
            ctx->body.pos[i][Y_] = ctx->body.pos[i - 1][Y_];
        }

        switch (ctx->body.dir) {
            case SNAKE_DIR_RIGHT:
                ctx->body.pos[0][X_]++;
                break;
            case SNAKE_DIR_UP:
                ctx->body.pos[0][Y_]--;
                break;
            case SNAKE_DIR_LEFT:
                ctx->body.pos[0][X_]--;
                break;
            case SNAKE_DIR_DOWN:
                ctx->body.pos[0][Y_]++;
                break;
        }

        ctx->body.prev_dir = ctx->body.dir;

///     wall?
        if(ctx->body.pos[0][X_] == SNAKE_GAME_WIDTH){
            ctx->body.pos[0][X_] = 0;
        } else if(ctx->body.pos[0][X_] == -1){
            ctx->body.pos[0][X_] = SNAKE_GAME_WIDTH - 1;
        } else if (ctx->body.pos[0][Y_] == SNAKE_GAME_HEIGHT){
            ctx->body.pos[0][Y_] = 0;
        } else if (ctx->body.pos[0][Y_] == -1){
            ctx->body.pos[0][Y_] = SNAKE_GAME_HEIGHT - 1;
        }

///     food
        if(ctx->food.x == ctx->body.pos[0][X_] && ctx->food.y == ctx->body.pos[0][Y_]) {
            Snake::snake_context_new_food_pos(ctx);
            ++ctx->body.length;
        }

        /// kill??
        for(int i = 0; i < ctx->body.length; ++i){
            if(ctx->body.pos[0][X_] == ctx->body.pos[i][X_] && ctx->body.pos[0][Y_] == ctx->body.pos[i][Y_]){
                Snake::snake_context_initialize(ctx);
            }
        }
    }

    static void snake_context_redirect(Snake *ctx, Direction dir){
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

