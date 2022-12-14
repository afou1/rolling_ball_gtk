#ifndef ROLLING_BALL_GTK_GAME_H
#define ROLLING_BALL_GTK_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <time.h>
#include <sys/time.h>

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
    int jump_force;
    int bool_jump;
    int on_platform;
    Platform* current_platform;
    SDL_Surface *ptr_surface;
    SDL_Texture *ptr_texture;

} Ball;
typedef struct Score{
    SDL_Surface *ptr_surface;
    SDL_Texture *ptr_texture;
    char message[128];
    SDL_Rect pos_message;
    TTF_Font *game_font;
    SDL_Color color;
} Score;
typedef struct Game{
    int first_plat;
    int last_plat;
    Platform platforms[NUM_PLATFORMS];
    long time_start;
    long current_score;
    Score score;
    Ball ball;
    int game_over;

} Game;


void init_ball(Ball* ball);
void init_platforms(Platform *arr_platforms,Ball ball);
void init_score_message(Game *game);
void init_state(Game *game);
void update_pos_ball(Game *game);
void update_score(Game* game);
void update_pos_platforms(Game *game);
void update_positions(Game* game);
int is_coliding(Platform p, Ball b);
int proc_collisions_platforms(Game* game);
void handle_edges(Game *game);
void ball_is_on_platform(Game* game);
void move_left(Game *game);
void move_right(Game *game);
void jump(Game* game);
int get_valid_x(int old_w);
void render_platforms(Platform *arr_platforms,SDL_Renderer* renderer);
void render_ball(Ball* ball,SDL_Renderer* renderer);
void render_score(Score *score,int current_score,SDL_Renderer* renderer);
void render_game(Game* game,SDL_Renderer* renderer);
void render_game_over(Game* game,int sec_left,SDL_Renderer* renderer);
void destroy_platforms(Platform *arr_platforms);
void destroy_ball(Ball *ball);
void destroy_score(Score *score);
void destroy_game(Game* game);


#endif //ROLLING_BALL_GTK_GAME_H
