#include "game.h"



int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    TTF_Init();
    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;
    IMG_Init(imgFlags);
    Game game;
    init_state(&game);
    long counter_over=game.time_start;
    int sec_left=20;
    int close = 0;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            if(game.ball.on_platform){
                                jump(&game);
                            }
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            move_left(&game);
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            move_right(&game);
                            break;
                        default:
                            break;
                    }
            }
        }
        update_positions(&game);
        handle_edges(&game);
        if(game.game_over){
            SDL_RenderClear(rend);
            SDL_SetRenderDrawColor(rend,53,81,92,0);
            if(counter_over==game.time_start){
                struct timeval t;
                gettimeofday(&t,0);
                counter_over=t.tv_sec+6;
            }
            struct timeval t;
            gettimeofday(&t,0);
            sec_left=(int)(counter_over-t.tv_sec);
            render_game_over(&game,sec_left,rend);
            SDL_RenderPresent(rend);
            if(sec_left<=0){
                close=1;
                break;
            }
            SDL_Delay(1000 / 25);
        }else{
            update_score(&game);
            SDL_RenderClear(rend);
            SDL_SetRenderDrawColor(rend,53,81,92,0);
            render_game(&game,rend);
            SDL_RenderPresent(rend);
            SDL_Delay(1000 / 144);
        }

    }
    destroy_game(&game);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}