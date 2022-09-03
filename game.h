#ifndef ROLLING_BALL_GTK_GAME_H
#define ROLLING_BALL_GTK_GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>



typedef struct Platform{
    SDL_Rect pos_rect;
} Platform;

typedef struct Ball{
    SDL_Rect pos_rect;

} Ball;

typedef struct Game{


} Game;


Game* init_state();
void render_game(Game* game,SDL_Renderer* renderer);

#endif //ROLLING_BALL_GTK_GAME_H
