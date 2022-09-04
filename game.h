#ifndef ROLLING_BALL_GTK_GAME_H
#define ROLLING_BALL_GTK_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <time.h>


#define NUM_PLATFORMS 10
#define PLATFORM_WIDTH 150
#define PLATFORM_HEIGHT 50
#define PLATFORM_SPEED 3

#define BALL_HEIGHT 30
#define BALL_WIDTH 30

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

typedef struct Platform{
    SDL_Rect pos_rect;
    int pixel_speed;
    SDL_Surface *ptr_surface;
    SDL_Texture *ptr_texture;
} Platform;

typedef struct Ball{
    SDL_Rect pos_rect;
    int speed_x;
    int speed_y;
    Platform* current_platform;
    SDL_Surface *ptr_surface;
    SDL_Texture *ptr_texture;

} Ball;

typedef struct Game{
    int first_plat;
    int last_plat;
    Platform platforms[NUM_PLATFORMS];
    Ball ball;

} Game;

void init_platforms(Platform *arr_platforms,Ball ball);
void init_state(Game *game);
void update_pos_platforms(Game *game);
void update_positions(Game* game);
void render_platforms(Platform *arr_platforms,SDL_Renderer* renderer);
void render_game(Game* game,SDL_Renderer* renderer);
void move_left(Game* game);
void move_right(Game* game);
#endif //ROLLING_BALL_GTK_GAME_H
