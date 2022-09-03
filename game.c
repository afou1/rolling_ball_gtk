# include "game.h"



void init_ball(Ball* ball){
    ball->ptr_surface= IMG_Load("../ball.png");
    ball->ptr_texture=NULL;
    ball->pos_rect.x=(WINDOW_WIDTH-BALL_WIDTH)/2;
    ball->pos_rect.y=WINDOW_HEIGHT/2;

}


int ball_is_on_platform(Platform* arr_platforms,int num,float ball_x,float ball_y,int width){

    for(int i=0;i<num;i++){
        int plat_x=(arr_platforms+i)->pos_rect.x;
        int plat_y=(arr_platforms+i)->pos_rect.y;

        for(int j=0; j<width;j++){
            if(ball_y==plat_y && ball_x==(plat_x+width)){
                return 1;
            }
        }
    }
    return 0;
}



void update_pos_ball(Game *game,int on_plateform){


    float gravity=-0.001;
    static float speed_y;
    static float speed_x=10;

    if(on_plateform==0){
        speed_y+=gravity;
        game->ball.pos_rect.y += speed_y;
    }

        
}




void init_platforms(Platform *arr_platforms,Ball ball){
    SDL_Surface* surface_platform = IMG_Load("../platform.png");
    for (int i=0;i<NUM_PLATFORMS;i++) {
        arr_platforms[i].ptr_surface = surface_platform;
        arr_platforms[i].pos_rect.h = PLATFORM_HEIGHT;
        arr_platforms[i].pos_rect.w = PLATFORM_WIDTH;
        arr_platforms[i].pos_rect.x = -1;
        arr_platforms[i].pos_rect.y = -1;
        arr_platforms[i].pixel_speed=PLATFORM_SPEED;
        arr_platforms[i].ptr_texture=NULL;
    }
    arr_platforms[0].pos_rect.x=(WINDOW_WIDTH-PLATFORM_WIDTH)/2;
    arr_platforms[0].pos_rect.y=ball.pos_rect.y+BALL_HEIGHT;
}

int get_valid_x(int old_w){
    srand(time(NULL));
    int new_w= old_w;
    while(new_w==old_w){
        new_w=rand()%(WINDOW_WIDTH-PLATFORM_WIDTH);
    }
    return new_w;
}
void update_pos_platforms(Game *game){
    Platform* arr_platforms=game->platforms;
    int new_y=0,new_x=0;
    for (int i=0;i<NUM_PLATFORMS;i++){
        if(arr_platforms[i].pos_rect.y>0 && arr_platforms[i].pos_rect.x>0){
            new_y=arr_platforms[i].pos_rect.y-PLATFORM_SPEED;
            if (new_y<0){
                arr_platforms[i].pos_rect.y=-1;
                arr_platforms[i].pos_rect.x=-1;
                game->first_plat=(game->first_plat+1)%NUM_PLATFORMS;
            }else{
                arr_platforms[i].pos_rect.y=new_y;
            }
        }
    }
    if(arr_platforms[game->last_plat].pos_rect.y<WINDOW_HEIGHT/2){
        new_x=get_valid_x(arr_platforms[game->last_plat].pos_rect.x);
        game->last_plat=(game->last_plat+1)%NUM_PLATFORMS;
        arr_platforms[game->last_plat].pos_rect.x=new_x;
        arr_platforms[game->last_plat].pos_rect.y=WINDOW_HEIGHT-PLATFORM_HEIGHT-2;
    }
}

void render_platforms(Platform *arr_platforms,SDL_Renderer* renderer){
    for (int i=0;i<NUM_PLATFORMS;i++){
        if(arr_platforms[i].pos_rect.y>0 && arr_platforms[i].pos_rect.x>0){
            if(arr_platforms[i].ptr_texture==NULL){
                arr_platforms[i].ptr_texture=SDL_CreateTextureFromSurface(renderer, arr_platforms[i].ptr_surface);
            }
            SDL_RenderCopy(renderer, arr_platforms[i].ptr_texture, NULL, &arr_platforms[i].pos_rect);
        }
    }
}
void render_ball(Ball* ball,SDL_Renderer* renderer){
    if(ball->ptr_texture==NULL){
        ball->ptr_texture=SDL_CreateTextureFromSurface(renderer, ball->ptr_surface);
    }
    SDL_RenderCopy(renderer, ball->ptr_texture, NULL,  &ball->pos_rect);
}
void init_state(Game *game){
    game->first_plat=0;
    game->last_plat=0;
    init_ball(&game->ball);
    init_platforms(game->platforms,game->ball);
}

void render_game(Game* game,SDL_Renderer* renderer){
    render_platforms(game->platforms,renderer);
    render_ball(&game->ball,renderer);
}

void update_positions(Game* game){
    update_pos_platforms(game);
    int bool_ball=ball_is_on_platform(game->platforms,NUM_PLATFORMS,game->ball.pos_rect.x,game->ball.pos_rect.y,PLATFORM_WIDTH);
    update_pos_ball(game,bool_ball);
}