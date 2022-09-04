# include "game.h"



void init_ball(Ball* ball){
    ball->ptr_surface= IMG_Load("../ball.png");
    ball->ptr_texture=NULL;
    ball->pos_rect.x=(WINDOW_WIDTH-BALL_WIDTH)/2;
    ball->pos_rect.y=WINDOW_HEIGHT/2;
    ball->pos_rect.w=BALL_WIDTH;
    ball->pos_rect.h=BALL_HEIGHT;
    ball->speed_x=15;
    ball->speed_y=3;
    ball->jump_force=0;
    ball->bool_jump=0;

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

void init_score_message(Game *game){
    game->score.pos_message.x = 0;
    game->score.pos_message.y = 0;
    game->score.pos_message.w = 200;
    game->score.pos_message.h = 100;
    game->score.game_font = TTF_OpenFont("/home/afou/The_projects/random_c/rolling_ball_gtk/score.ttf", 24);
    game->score.color.r=255;
    game->score.color.g=255;
    game->score.color.b=255;
    game->score.ptr_surface=NULL;
    game->score.ptr_texture=NULL;


}

void init_state(Game *game){
    struct timeval t;
    gettimeofday(&t,0);
    game->time_start=t.tv_sec;
    srand(time(NULL));
    game->first_plat=0;
    game->last_plat=0;
    game->current_score=0;
    game->game_over=0;

    init_ball(&game->ball);
    init_platforms(game->platforms,game->ball);
    init_score_message(game);
}

void update_pos_ball(Game *game){
    //ball_is_on_platform(game);
    //float gravity=0.05;
    if(game->ball.on_platform==0){
        game->ball.pos_rect.y += game->ball.speed_y-game->ball.jump_force;
        if(game->ball.jump_force!=0){
            game->ball.jump_force-=1;

        }else{
            game->ball.bool_jump=0;
        }
    }else{
        if(game->ball.bool_jump){
            game->ball.bool_jump=0;
            game->ball.jump_force=0;
        }

    }
}

void update_score(Game* game){
    struct timeval t;
    gettimeofday(&t,0);
    game->current_score=t.tv_sec-game->time_start;

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
        arr_platforms[game->last_plat].pos_rect.y=WINDOW_HEIGHT-1;
    }
}

void update_positions(Game* game){

    update_pos_platforms(game);
    proc_collisions_platforms(game);
    update_pos_ball(game);
}

int is_coliding(Platform p, Ball b){
    if (p.pos_rect.y<=(b.pos_rect.y+BALL_HEIGHT)  && p.pos_rect.y>=(b.pos_rect.y+BALL_HEIGHT/5) &&
        b.pos_rect.x+BALL_WIDTH/2>=p.pos_rect.x && b.pos_rect.x<=(p.pos_rect.x+PLATFORM_WIDTH-BALL_WIDTH/5)){
        return 1;
    }
    return 0;
}

int proc_collisions_platforms(Game* game){
    Platform* arr_platforms=game->platforms;
    for (int i=0;i<NUM_PLATFORMS;i++) {
        if (arr_platforms[i].pos_rect.y > 0 && arr_platforms[i].pos_rect.x > 0 &&
            is_coliding(arr_platforms[i], game->ball)) {
            game->ball.pos_rect.y = arr_platforms[i].pos_rect.y - BALL_HEIGHT;
            game->ball.current_platform=&arr_platforms[i];
            game->ball.on_platform=1;
            return 1;
        }
    }
    game->ball.on_platform=0;
    game->ball.current_platform=NULL;
    return 0;
}

void handle_edges(Game *game){

    if ( game->ball.pos_rect.x+ game->ball.pos_rect.w> WINDOW_WIDTH)
            game->ball.pos_rect.x= WINDOW_WIDTH - game->ball.pos_rect.w;


        if ( game->ball.pos_rect.x< 0)
            game->ball.pos_rect.x= 0;


        if (game->ball.pos_rect.y + game->ball.pos_rect.h > WINDOW_HEIGHT){
            game->ball.pos_rect.y= WINDOW_HEIGHT - game->ball.pos_rect.h;
            game->game_over=1;
        }


        if (game->ball.pos_rect.y < 0)
            game->ball.pos_rect.y = 0;
}

void ball_is_on_platform(Game* game){

    Ball *ball=&game->ball;
    Platform *arr_platforms=game->platforms;

    for(int i=0;i<NUM_PLATFORMS;i++){
        int plat_x=(arr_platforms+i)->pos_rect.x;
        int plat_y=(arr_platforms+i)->pos_rect.y;
        if(ball->pos_rect.y+BALL_HEIGHT==plat_y && ball->pos_rect.x>=plat_x && ball->pos_rect.x<=(plat_x+PLATFORM_WIDTH-BALL_WIDTH)){
                ball->current_platform=arr_platforms+i;
                ball->on_platform=1;
                break;
        }
    }
    ball->on_platform=0;;
}

void move_left(Game *game){
    game->ball.pos_rect.x-=game->ball.speed_x;
}

void move_right(Game *game){
    game->ball.pos_rect.x+=game->ball.speed_x;
}

void jump(Game* game){
    game->ball.jump_force=game->ball.speed_y*5;
    game->ball.bool_jump=1;
    game->ball.pos_rect.y-=game->ball.jump_force;
}

int get_valid_x(int old_x){

    int new_x= old_x;
    while(new_x>(old_x-PLATFORM_WIDTH/2) && new_x<(old_x+PLATFORM_WIDTH/2)){
        new_x=rand()%(WINDOW_WIDTH-PLATFORM_WIDTH);
    }
    return new_x;
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

void render_score(Score *score,int current_score,SDL_Renderer* renderer){
    sprintf(score->message, "SCORE:%05d\0", current_score);
    if (score->ptr_surface!=NULL) SDL_FreeSurface(score->ptr_surface);
    score->ptr_surface= TTF_RenderText_Solid(score->game_font,score->message, score->color);
    if (score->ptr_texture!=NULL) SDL_DestroyTexture(score->ptr_texture);
    score->ptr_texture = SDL_CreateTextureFromSurface(renderer, score->ptr_surface);
    SDL_RenderCopy(renderer, score->ptr_texture, NULL, &score->pos_message);
}

void render_game(Game* game,SDL_Renderer* renderer){
    render_platforms(game->platforms,renderer);
    render_ball(&game->ball,renderer);
    render_score(&game->score,game->current_score,renderer);
}

void render_game_over(Game* game,int sec_left,SDL_Renderer* renderer){

    char message_over[]="GAME OVER";
    SDL_Surface *surf_over = TTF_RenderText_Solid(game->score.game_font,message_over, game->score.color);
    SDL_Texture *text_over= SDL_CreateTextureFromSurface(renderer, surf_over);
    SDL_Rect rect_over;
    rect_over.x=10;
    rect_over.h=game->score.pos_message.h*2;
    rect_over.y=(WINDOW_HEIGHT-rect_over.h)/2;
    rect_over.w=WINDOW_WIDTH-20;
    SDL_RenderCopy(renderer, text_over, NULL, &rect_over);
    game->score.pos_message.y=rect_over.y+rect_over.h+2;
    game->score.pos_message.x=(WINDOW_WIDTH-game->score.pos_message.w)/2;
    render_score(&game->score,game->current_score,renderer);
    char closing_message[128];
    sprintf(closing_message, "Closing in %d...\0", sec_left);
    SDL_Surface *surf_closing = TTF_RenderText_Solid(game->score.game_font,closing_message, game->score.color);
    SDL_Texture *text_closing= SDL_CreateTextureFromSurface(renderer, surf_closing);
    SDL_Rect rect_closing;
    rect_closing.x=0;
    rect_closing.h=game->score.pos_message.h/2;
    rect_closing.y=0;
    rect_closing.w=game->score.pos_message.w*2;
    SDL_RenderCopy(renderer, text_closing, NULL, &rect_closing);
}

void destroy_platforms(Platform *arr_platforms){
    if(arr_platforms[0].ptr_surface!=NULL){
        SDL_FreeSurface(arr_platforms[0].ptr_surface);
    }
    for(int i=0;i<NUM_PLATFORMS;i++){
        if(arr_platforms[i].ptr_texture!=NULL){
            SDL_DestroyTexture(arr_platforms[i].ptr_texture);
        }
    }
}

void destroy_ball(Ball *ball){
    if(ball->ptr_texture!=NULL){
        SDL_DestroyTexture(ball->ptr_texture);
    }
    if(ball->ptr_surface!=NULL){
        SDL_FreeSurface(ball->ptr_surface);
    }
}

void destroy_score(Score *score){
    if(score->ptr_texture!=NULL){
        SDL_DestroyTexture(score->ptr_texture);
    }
    if(score->ptr_surface!=NULL){
        SDL_FreeSurface(score->ptr_surface);
    }
}

void destroy_game(Game* game){
    destroy_platforms(game->platforms);
    destroy_ball(&game->ball);
    destroy_score(&game->score);
}