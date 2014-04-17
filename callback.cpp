/*This File contains all the CallBack Function
for Mouse and Keyboard. */
#include "declaration.cpp"

void keyboard_func(int k, int x, int y)
{
    switch(k)
    {
        case GLUT_KEY_LEFT: ship_left=true,ship_right=false;
                            break;
        case GLUT_KEY_RIGHT: ship_right=true,ship_left=false;
                             break;
    }
}
void keyboard_up_func(int k, int x, int y)
{
    switch(k)
    {
        case GLUT_KEY_LEFT: ship_left=false;
                            break;
        case GLUT_KEY_RIGHT:ship_right=false;
                            break;
    }
}
void normal_key(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q':
        case 'Q':   game_state = 4;
                    break;
        case 'p':
        case 'P':   if(game_state == 2) game_state = 3;
                    else if(game_state == 3) game_state = 2;
                    break;
        case 'R':
        case 'r':   if(game_state == 3) game_state = 2;
                    break;

        case 'Y':
        case 'y':   if(game_state == 4) game_state = 5;
                    break;

        case 'N':
        case 'n':   if(game_state == 4) game_state = 3;
                    break;

        case 'S':
        case 's':   if(game_state == 1) game_state = 2;
                    break;

    }
}
void normal_key_up(unsigned char k, int x, int y)
{
    switch(k)
    {
        case ' ':   glutIgnoreKeyRepeat(1);
                    if(game_state == 2) add_bullet();
                    break;
    }
}
void mouse_func(int button, int state, int x, int y)
{
    switch(game_state)
    {
        case 1: if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                {
                    if(y>=down_bound_start_start && y<=up_bound_start_start && x>=left_bound_start && x<=right_bound_start) game_state = 2;
                    if(y>=down_bound_start_quit && y<=up_bound_start_quit && x>=left_bound_start && x<=right_bound_start) game_state = 4;
                }
                break;

        case 2: if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) add_bullet();
                else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) game_state = 3;
                break;

        case 3: if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) game_state = 2;
                else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                {
                    if(y>=down_bound_pause && y<=up_bound_pause && x>=left_bound_pause_quit && x<=right_bound_pause_quit) game_state = 4;
                    if(y>=down_bound_pause && y<=up_bound_pause && x>=left_bound_pause_resume && x<=right_bound_pause_resume) game_state= 2;
                }
                break;

        case 4: if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                {
                    if(y>=down_bound_quit && y<=up_bound_quit && x>=left_bound_quit_yes && x<=right_bound_quit_yes) game_state = 5;
                    if(y>=down_bound_quit && y<=up_bound_quit && x>=left_bound_quit_no && x<=right_bound_quit_no) game_state= 3;
                }
    }
}
void mouse_motion(int x, int y)
{
    switch(game_state)
    {
        case 1: if(y>=down_bound_start_start && y<=up_bound_start_start && x>=left_bound_start && x<=right_bound_start)
                {
                    start_mouse_hover_start = true;
                }
                else start_mouse_hover_start = false;

                if(y>=down_bound_start_quit && y<=up_bound_start_quit && x>=left_bound_start && x<=right_bound_start)
                {
                    start_mouse_hover_quit = true;
                }
                else start_mouse_hover_quit = false;
                break;

        case 2: if(x<=0)    ship_x = 0;
                else if(x >= (width - ship_span)) ship_x = width - ship_span;
                else ship_x = x;
                break;

        case 3: if(y>=down_bound_pause && y<=up_bound_pause && x>=left_bound_pause_quit && x<=right_bound_pause_quit)
                {
                    pause_mouse_hover_quit = true;
                }
                else pause_mouse_hover_quit = false;

                if(y>=down_bound_pause && y<=up_bound_pause && x>=left_bound_pause_resume && x<=right_bound_pause_resume)
                {
                    pause_mouse_hover_resume = true;
                }
                else pause_mouse_hover_resume = false;
                break;

        case 4: if(y>=down_bound_quit && y<=up_bound_quit && x>=left_bound_quit_yes && x<=right_bound_quit_yes)
                {
                    quit_mouse_hover_yes = true;
                }
                else quit_mouse_hover_yes = false;

                if(y>=down_bound_quit && y<=up_bound_quit && x>=left_bound_quit_no && x<=right_bound_quit_no)
                {
                    quit_mouse_hover_no = true;
                }
                else quit_mouse_hover_no = false;

                break;
    }
}
