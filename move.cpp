
/*This File Contains the Code to move every thing.
It is called every-time a new frame is rendered*/

void main_ship_move()
{
    if(ship_left)
    {
        if(ship_x>=(int)UNIT_MOVE)
        {
            ship_x -= UNIT_MOVE;
        }
        else if(ship_x>0)
        {
            ship_x = 0;
        }
    }
    else if(ship_right)
    {
        if(ship_x<=(width-ship_span-UNIT_MOVE))
        {
            ship_x += UNIT_MOVE;
        }
        else if(ship_x<=(width-ship_span))
        {
            ship_x = width-ship_span;
        }
    }
}
void bomb_move()
{
    unsigned int i;
    float temps = height/((float)FPS);
    for(i=0;i<MAX_BOMB;i++)
    {
        bomb_pos[i][1] -= temps/(bomb_speed[i]);
        if(bomb_pos[i][1]<=PADDING_BELOW)
        {
            bomb_present[i]=false;
            BOMB_COUNT--;
        }
    }
}

void bullet_move()
{
    unsigned int i;
    float temps = height/((float)FPS);
    temps /= BULLET_SEC;
    for(i = 0;i < bullets.size(); i++)
    {
        bullets[i].y += temps;
        if(bullets[i].y>=height) bullets.erase(bullets.begin() + i),i--;
    }
}

bool collision_bomb_bullet(struct bullet bull, int bomb_ind)
{
    if(bomb_present[bomb_ind]==false) return false;
    if(bull.y<(bomb_pos[bomb_ind][1]-VARD)) return false;
    if(bull.y>(bomb_pos[bomb_ind][1]+VARD)) return false;
    if(bull.x<(bomb_pos[bomb_ind][0]-VARD)) return false;
    if(bull.x>(bomb_pos[bomb_ind][0]+VARD)) return false;
    return true;
}

bool collison_bomb_ship(int bomb_ind)
{
    if(bomb_present[bomb_ind]==0) return false;
    if(bomb_pos[bomb_ind][1]-VARD>ship_y+VARC) return false;
    if(bomb_pos[bomb_ind][0]+VARD<ship_x) return false;
    if(bomb_pos[bomb_ind][0]-VARD>ship_x+VARA+VARA+VARB) return false;


    int diffy=(bomb_pos[bomb_ind][1]-VARD-ship_y);
    int diffx=bomb_pos[bomb_ind][0]-ship_x;


    if(diffx+VARD<VARA)
    {
        if(diffx+VARD==0)
        return false;

        if((VARC)/(2.0*VARA) < (diffy)/(diffx+VARD))
        return false;
        else
        return true;
    }
    else if(diffx+VARD<VARA+VARB)
    {
        if(diffy<VARC)
        return true;
        else //TEST for inside of top triangle
        {
            if(diffx+VARD>VARA+VARB/2.0)
            return true;
            else //CHECK WITH SLOPE
            {
                if(diffx+VARD==VARA)
                return false;

                if(((VARC*2)/(VARB*3))<((diffy-VARC/2.0)/(diffx+VARD-VARA)))
                return false;
                else
                return true;
            }
        }
    }
    else
    {
        if(diffx-VARD<=VARA)
        {
            return true;
        }
        else if(diffx-VARD<VARA+VARB)
        {
            if(diffy <= VARC)
            return true;
            else //test for inside of top triangle
            {
                if(diffx - VARD <= VARA+VARB/2.0)
                return true;
                else //CHECK WITH SLOPE
                {
                    if(VARA+VARB==diffx-VARD)
                    return false;

                    if(((VARC*2)/(VARB*3))<((diffy-VARC/2.0)/(VARA+VARB-(diffx-VARD))))
                    return false;
                    else
                    return true;
                }
            }
        }
        else //check slope of right wing and decide
        {
            if(VARA + VARA + VARB== diffx - VARD)
            return false;

            if((VARC/(2.0*VARA)) < (diffy / (VARA + VARA + VARB - (diffx - VARD))))
            return false;
            else
            return true;
        }
    }
    return false;
}

void detect_collisions()
{
    //To detect collision between bomb and bullets
    unsigned int i,j;
    for(i = 0; i < bullets.size(); i++)
        for(j = 0;j < MAX_BOMB; j++)
            if(bomb_present[j] && collision_bomb_bullet(bullets[i], j))
            {
                curr_score += BOMB_MAX_SEC - bomb_speed[j] + 1;
                bomb_present[j]=false;
                BOMB_COUNT--;
                bullets.erase(bullets.begin() + i);
                i--;
                break;
            }

    //To detect collision between main ship and bomb
    unsigned int ii;
    for(ii = 0; ii < BOMB_COUNT; ii++)
    {
        if(collison_bomb_ship(ii))
        {
            game_state = 5;
        }
    }
}
void timer_func(int v)
{
    if(game_state == 2)
    {
        main_ship_move();
        bomb_move();
        bullet_move();
        detect_collisions();
    }
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer_func, v);
}
