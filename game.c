# include "game.h"


Game* init_state(){

    return NULL;
}

int is_on_platform(Platform* platforms,int num,float ball_x,float ball_y,int width){

    for(int i=0;i<num;i++){
        int plat_x=(platforms+i)->pos_rect.x;
        int plat_y=(platforms+i)->pos_rect.y;

        for(int j=0; j<width;j++){
            if(ball_y==plat_y && ball_x==(plat_x+width)){
                return 1;
            }
        }
    }
    return 0;
}

void moving_ball(int speed,SDL_Rect dest, SDL_Renderer* rend,){

    int close=0;
    while(!close){
        SDL_Event event;

      while (SDL_PollEvent(&event)) {

        int on_platform=is_on_platform(*Platform platforms,int num,float ball_x,float ball_y,int width);
        if (on_platform){
            float gravity=0
        }else{
            float gravity=-0.001;

            speed+=gravity;
        

            dest.y += speed;
        }
            switch (event.type) {

                case SDL_QUIT:

                    close = 1;
                    break;

                case SDL_KEYDOWN:

                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            if(!on_platform){
                                break;
                            }
                            dest.y -= speed;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dest.x -= speed;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            // dest.y += speed / 30;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dest.x += speed;
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

}



void render_game(Game* game,SDL_Renderer* renderer){
    ;
}