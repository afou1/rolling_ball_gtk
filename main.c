#include "game.h"



int main(int argc, char *argv[])
{

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Surface* surface_ball;
    SDL_Surface* surface_platform;
    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;
    int flg= IMG_Init(imgFlags);

    Game game;
    init_state(&game);

    int close = 0;
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);

    int speed = 300;

    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            if(event.type==SDL_QUIT){
                close = 1;
                break;
            }
            else if(event.type==SDL_KEYDOWN ||event.key.repeat==1){
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        // appelle a update_pos_ball
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        move_left(&game);
                        // appelle a update_pos_ball

                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        move_right(&game);
                        // appelle a update_pos_ball

                        break;
                    default:
                        break;
                }
            }


        }




        update_positions(&game);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend,53,81,92,0);
        render_game(&game,rend);
        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 144);
    }




    SDL_DestroyRenderer(rend);


    SDL_DestroyWindow(win);


    SDL_Quit();

    return 0;
}