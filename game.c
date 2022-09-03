# include "game.h"




void init_platforms(Platform *arr_platforms){
    SDL_Surface* surface_platform = IMG_Load("/home/afou/The_projects/random_c/rolling_ball_gtk/platform.png");
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
    arr_platforms[0].pos_rect.y=(WINDOW_HEIGHT+BALL_HEIGHT)/2;
    arr_platforms[1].pos_rect.x=10;
    arr_platforms[1].pos_rect.y=10;
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
                game->first_plat=game->first_plat+1%NUM_PLATFORMS;
            }else{
                arr_platforms[i].pos_rect.y=new_y;
            }
        }
    }
    if(arr_platforms[game->last_plat].pos_rect.y<WINDOW_HEIGHT/2){
        new_x=get_valid_x(arr_platforms[game->last_plat].pos_rect.x);
        game->last_plat=game->last_plat+1%NUM_PLATFORMS;
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
void init_state(Game *game){
    game->first_plat=0;
    game->last_plat=0;
    init_platforms(game->platforms);
}

void render_game(Game* game,SDL_Renderer* renderer){
    render_platforms(game->platforms,renderer);
}