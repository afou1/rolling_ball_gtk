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
                                       1000, 1000, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Surface* surface_ball;
    SDL_Surface* surface_platform;
    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;
    int flg= IMG_Init(imgFlags);
    surface_ball = IMG_Load("/home/afou/The_projects/random_c/rolling_ball_gtk/ball.png");
    surface_platform = IMG_Load("/home/afou/The_projects/random_c/rolling_ball_gtk/platform.png");

    SDL_Texture* tex_ball = SDL_CreateTextureFromSurface(rend, surface_ball);
    SDL_Texture* tex_platform = SDL_CreateTextureFromSurface(rend, surface_platform);
    SDL_Rect dest,rect_platform;



    printf("IMG_Load: %s %d %d\n", IMG_GetError(),imgFlags,flg);
    SDL_QueryTexture(tex_ball, NULL, NULL, &dest.w, &dest.h);
    SDL_QueryTexture(tex_platform, NULL, NULL, &rect_platform.w, &rect_platform.h);
    dest.w = 30;
    dest.h = 30;

    dest.x = (1000 - dest.w) / 2;
    dest.y = (1000 - dest.h) / 2;

    rect_platform.x=0;
    rect_platform.y=0;
    rect_platform.w=200;
    rect_platform.h=50;

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
                            dest.y -= speed / 30;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dest.x -= speed / 30;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dest.y += speed / 30;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dest.x += speed / 30;
                            break;
                        default:
                            break;
                    }
            }
        }


        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;


        if (dest.x < 0)
            dest.x = 0;


        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;


        if (dest.y < 0)
            dest.y = 0;


        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend,53,81,92,0);
        SDL_RenderCopy(rend, tex_ball, NULL, &dest);
        SDL_RenderCopy(rend, tex_platform, NULL, &rect_platform);
        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 144);
    }


    SDL_DestroyTexture(tex_ball);
    SDL_DestroyTexture(tex_platform);

    SDL_DestroyRenderer(rend);


    SDL_DestroyWindow(win);


    SDL_Quit();

    return 0;
}