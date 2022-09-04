# include "game.h"



void init_ball(Ball* ball){
    ball->ptr_surface= IMG_Load("../ball.png");
    ball->ptr_texture=NULL;
    ball->pos_rect.x=(WINDOW_WIDTH-BALL_WIDTH)/2;
    ball->pos_rect.y=WINDOW_HEIGHT/2;
    ball->pos_rect.w=BALL_WIDTH;
    ball->pos_rect.h=BALL_HEIGHT;
    ball->speed_x=10;

}


void handle_edges(Game *game){

    if ( game->ball.pos_rect.x+ game->ball.pos_rect.w> WINDOW_WIDTH)
            game->ball.pos_rect.x= WINDOW_WIDTH - game->ball.pos_rect.w;


        if ( game->ball.pos_rect.x< 0)
            game->ball.pos_rect.x= 0;


        if (game->ball.pos_rect.y + game->ball.pos_rect.h > WINDOW_HEIGHT)
            game->ball.pos_rect.y= WINDOW_HEIGHT - game->ball.pos_rect.h;

        if (game->ball.pos_rect.y < 0)
            game->ball.pos_rect.y = 0;
}


void ball_is_on_platform(Game* game){

    Ball *ball=&game->ball;
    Platform *arr_platforms=game->platforms;
    



    for(int i=0;i<NUM_PLATFORMS;i++){
        int plat_x=(arr_platforms+i)->pos_rect.x;
        int plat_y=(arr_platforms+i)->pos_rect.y;


        if(ball->pos_rect.y+BALL_HEIGHT==plat_y){
            if(ball->pos_rect.x>=plat_x && ball->pos_rect.x<=(plat_x+PLATFORM_WIDTH-BALL_WIDTH)){
                ball->current_platform=arr_platforms+i;
                ball->on_platform=1;
                return;
                // return 1;
        }
        }
    }
    ball->on_platform=0;;
}

void move_left(Game *game){
    game->ball.pos_rect.x-=game->ball.speed_x;
};

void move_right(Game *game){
    game->ball.pos_rect.x+=game->ball.speed_x;
};

void jump(Game* game){
    game->ball.jump_force=20;
    game->ball.bool_jump=1;
}



void update_pos_ball(Game *game){
    
    ball_is_on_platform(game);


    float gravity=0.05;
    float speed_y=5;

    if(game->ball.on_platform==0){
        speed_y+=gravity-game->ball.jump_force;
    
        game->ball.pos_rect.y += speed_y;
        if(game->ball.jump_force!=0){
            game->ball.jump_force-=1;

        }else{
            game->ball.bool_jump=0;
        }
    }else{
  
        game->ball.pos_rect.y=game->ball.current_platform->pos_rect.y-BALL_HEIGHT;
        if(game->ball.bool_jump){
                    
        speed_y+=gravity-game->ball.jump_force;
    
        game->ball.pos_rect.y += speed_y;

        }

    }//if the ball is on a platform, then it will take the y coordinate of the platform

        
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
    //render_ball(&game->ball,renderer);
    render_platforms(game->platforms,renderer);
    render_ball(&game->ball,renderer);
}

int is_coliding(Platform p, Ball b){
    // if (p.pos_rect.y<(b.pos_rect.y+BALL_HEIGHT) && b.pos_rect.x>=p.pos_rect.x && b.pos_rect.x<=(p.pos_rect.x+PLATFORM_WIDTH-BALL_WIDTH)){
    //     return 1;
    // }
    if (p.pos_rect.y<(b.pos_rect.y+BALL_HEIGHT)  && p.pos_rect.y>(b.pos_rect.y+BALL_HEIGHT/5) &&
           b.pos_rect.x+BALL_WIDTH/2>=p.pos_rect.x && b.pos_rect.x<=(p.pos_rect.x+PLATFORM_WIDTH-BALL_WIDTH/5)){
            return 1;
           }
    return 0;
}

void proc_collisions_platforms(Game* game){
    Platform* arr_platforms=game->platforms;
    for (int i=0;i<NUM_PLATFORMS;i++) {
        if (arr_platforms[i].pos_rect.y > 0 && arr_platforms[i].pos_rect.x > 0 &&
            is_coliding(arr_platforms[i], game->ball)) {
            game->ball.pos_rect.y = arr_platforms[i].pos_rect.y - BALL_HEIGHT;
        }
    }
}

void update_positions(Game* game){
    update_pos_platforms(game);
    proc_collisions_platforms(game);
    // ball_is_on_platform(game->platforms,NUM_PLATFORMS,&game->ball);
    update_pos_ball(game);
}