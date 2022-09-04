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


    int speed = 300;

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



        // update_pos_platforms(&game);
        update_positions(&game);
        handle_edges(&game);
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