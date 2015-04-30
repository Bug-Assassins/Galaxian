/*This File contains all the Functions related
to drawing and rendering of each frame*/
#include "declaration.cpp"

void draw_main_ship(int x, int y)
{
    glPushMatrix();
    glTranslatef(ship_x,ship_y,0);
    //Letf Wing
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(VARA,0);
        glVertex2f(VARA,VARC/2.0);
    glEnd();

    //Right Wing
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(VARA+VARB,0);
        glVertex2f(VARA+VARA+VARB,0);
        glVertex2f(VARA+VARB,VARC/2.0);
    glEnd();

    //Main Body
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f(VARA,0);
        glVertex2f(VARA+VARB,0);
        glVertex2f(VARA+VARB,VARC);
        glVertex2f(VARA+VARB/2.0, (4.0*VARC)/3.0);
        glVertex2f(VARA,VARC);
    glEnd();

    //Main Body's Window
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
        glVertex2f(VARA+(VARB/3.0), VARC/2.0);
        glVertex2f(VARA + (2.0*VARB)/3.0, VARC/2.0);
        glVertex2f(VARA + (2.0*VARB)/3.0, (3*VARC)/4.0);
        glVertex2f(VARA+(VARB/3.0), (3*VARC)/4.0);
    glEnd();
    glPopMatrix();
    glFlush();
}
void draw_bombs()
{
    glColor3f(0.2, 0.8, 0.4);
    unsigned int i;
    if(BOMB_COUNT!=MAX_BOMB)
    {
        for(i=0;i<MAX_BOMB;i++)
            if(bomb_present[i]==false)
            {
                bomb_present[i] = true;
                bomb_pos[i][0] = (seg_len*i) + VARD + rand()%((int)(seg_len-VARD-VARD+1));
                bomb_pos[i][1] = height-(3*VARD);
                bomb_speed[i] = BOMB_MIN_SEC + (rand()%((int)(BOMB_MAX_SEC-BOMB_MIN_SEC+1)));
                bomb_shape[i] = rand()%2;
                bomb_color[i][0] = rand()%10000;
                bomb_color[i][1] = rand()%10000;
                bomb_color[i][2] = rand()%10000;
                BOMB_COUNT++;
            }
    }
    for(i=0;i<MAX_BOMB;i++)
    {
        glPushMatrix();
        glTranslatef(bomb_pos[i][0],bomb_pos[i][1],0);
        glColor3f(0.0001 + bomb_color[i][0]/10000.0, 0.0001 + bomb_color[i][1]/10000.0, 0.0001 + bomb_color[i][2]/10000.0);
        if(bomb_shape[i])
        {
            glBegin(GL_POLYGON);
                glVertex2f(-VARD,-VARD);
                glVertex2f(VARD,-VARD);
                glVertex2f(VARD,VARD);
                glVertex2f(-VARD,VARD);
            glEnd();
        }
        else
        {
            dispcir(0,0,VARD);
        }
        glPopMatrix();
    }
}

void draw_bullets()
{
    unsigned int i;
    glColor3f(1.0, 0, 0);
    glPointSize(5);
    glBegin(GL_POINTS);
    for(i=0;i<bullets.size();i++)
    {
        glVertex2i(bullets[i].x,bullets[i].y);
    }
    glEnd();
    glPointSize(1);
}

void draw_score(long long int score)
{
    long long int tempsc = score;
    int stk[20],sp=0;

    while(tempsc>0)
    {
        stk[sp++] = (tempsc%10);
        tempsc /= 10;
    }
    sp--;
    while(sp>=0)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, stk[sp--]+'0');
    }
    if(score == 0) glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
}

void draw_score_board()
{
    glPushMatrix();
    glTranslatef(SCORE_BOARD_PADDING, height - SCORE_BOARD_HEIGHT - SCORE_BOARD_PADDING, 0);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(SCORE_BOARD_WIDTH, 0);
        glVertex2f(SCORE_BOARD_WIDTH, SCORE_BOARD_HEIGHT);
        glVertex2f(0, SCORE_BOARD_HEIGHT);
    glEnd();
    glLineWidth(5);
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
        glVertex2f(0, 0);
        glVertex2f(SCORE_BOARD_WIDTH, 0);
        glVertex2f(SCORE_BOARD_WIDTH, SCORE_BOARD_HEIGHT);
        glVertex2f(0, SCORE_BOARD_HEIGHT);
        glVertex2f(0,0);
    glEnd();
    glLineWidth(1);
    glColor3f(1,0.98,0);
        glPushMatrix();
            glTranslatef(8,8,0);
            glScalef(0.2,0.2,1);
            draw_score(curr_score);
        glPopMatrix();
    glPopMatrix();
}

void draw_background()
{
    k = (k+1)%BACKGROUND_REFRESH_DELAY;
    if(k==1)
    {
        num_stars = STARS_MIN + rand()%((int)(STARS_MAX-STARS_MIN + 1));
        for(int i=1;i<=num_stars;i++)
        {
            star_pos[i][0] = rand()%((int)width);
            star_pos[i][1] = rand()%((int)height);
            star_size[i] = (STARS_MIN_SIZE + rand()%((int)(STARS_MAX_SIZE - STARS_MIN_SIZE + 1))) / (100.0);
        }
    }
    glColor3f(252/255.0,228/255.0,94/255.0);
    for(int i=0;i<num_stars;i++)
    {
        glPointSize(star_size[i]);
        glBegin(GL_POINTS);
        glVertex2f(star_pos[i][0], star_pos[i][1]);
        glEnd();
    }
}

void draw_string(std::string str)
{
    for(unsigned int i=0;i<str.length();i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i));
    }
}

void draw_pause_menu()
{
    glPushMatrix();
        glTranslatef((width/2.0) - 250,(height/2.0) - 150, 0);
        glColor3f(0,0,0);
        glBegin(GL_POLYGON);
            glVertex2f(0,0);
            glVertex2f(500,0);
            glVertex2f(500,300);
            glVertex2f(0,300);
        glEnd();
        glLineWidth(4);
        glColor3f(0.3,0.7,0.5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0,0);
            glVertex2f(500,0);
            glVertex2f(500,300);
            glVertex2f(0,300);
        glEnd();
        glLineWidth(1);
            glPushMatrix();
                glTranslatef(90, 210, 0);
                glScalef(0.4,0.4,0);
                glColor3f(207/255.0,46/255.0,240/255.0);
                draw_string("Pause Game");
            glPopMatrix();
            glPushMatrix();
                glTranslatef(80, 150, 0);
                glScalef(0.25,0.25,0);
                glColor3f(1,179/255.0,85/255.0);
                draw_string("Press P/R or Q/Esc");
            glPopMatrix();
            glPushMatrix();
                glTranslatef(90,50,0);
                glPushMatrix();
                    if(pause_mouse_hover_quit)
                    {
                        glColor3f(149/255.0, 152/255.0, 156/255.0);
                        glBegin(GL_POLYGON);
                            glVertex2f(0,0);
                            glVertex2f(140,0);
                            glVertex2f(140,45);
                            glVertex2f(0,45);
                        glEnd();
                    }
                    glLineWidth(2);
                    glColor3f(91/255.0,161/255.0,247/255.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex2f(0,0);
                        glVertex2f(140,0);
                        glVertex2f(140,45);
                        glVertex2f(0,45);
                    glEnd();
                    glTranslatef(35,5,0);
                    glScalef(0.25,0.25,0);
                    glColor3f(1,0,0);
                    draw_string("Quit");
                glPopMatrix();
                glTranslatef(200,0,0);
                glPushMatrix();
                    if(pause_mouse_hover_resume)
                    {
                        glColor3f(149/255.0, 152/255.0, 156/255.0);
                        glBegin(GL_POLYGON);
                            glVertex2f(0,0);
                            glVertex2f(140,0);
                            glVertex2f(140,45);
                            glVertex2f(0,45);
                        glEnd();
                    }
                    glLineWidth(2);
                    glColor3f(91/255.0,161/255.0,247/255.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex2f(0,0);
                        glVertex2f(140,0);
                        glVertex2f(140,45);
                        glVertex2f(0,45);
                    glEnd();
                    glTranslatef(10,5,0);
                    glScalef(0.25,0.25,0);
                    glColor3f(0,1,0);
                    draw_string("Resume");
                glPopMatrix();
            glPopMatrix();
    glPopMatrix();
    glLineWidth(1);
}

void draw_exit_menu()
{
    glPushMatrix();
        glTranslatef((width/2.0) - 250,(height/2.0) - 150, 0);
        glColor3f(0,0,0);
        glBegin(GL_POLYGON);
            glVertex2f(0,0);
            glVertex2f(500,0);
            glVertex2f(500,300);
            glVertex2f(0,300);
        glEnd();
        glLineWidth(4);
        glColor3f(0.3,0.7,0.5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0,0);
            glVertex2f(500,0);
            glVertex2f(500,300);
            glVertex2f(0,300);
        glEnd();
        glLineWidth(1);
            glPushMatrix();
                glTranslatef(110, 210, 0);
                glScalef(0.4,0.4,0);
                glColor3f(207/255.0,46/255.0,240/255.0);
                draw_string("Quit Game");
            glPopMatrix();
            glPushMatrix();
                glTranslatef(130, 150, 0);
                glScalef(0.25,0.25,0);
                glColor3f(1,179/255.0,85/255.0);
                draw_string("Are You Sure?");
            glPopMatrix();
            glPushMatrix();
                glTranslatef(120,50,0);
                glPushMatrix();
                    if(quit_mouse_hover_yes)
                    {
                        glColor3f(149/255.0, 152/255.0, 156/255.0);
                        glBegin(GL_POLYGON);
                            glVertex2f(0,0);
                            glVertex2f(70,0);
                            glVertex2f(70,45);
                            glVertex2f(0,45);
                        glEnd();
                    }
                    glLineWidth(2);
                    glColor3f(91/255.0,161/255.0,247/255.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex2f(0,0);
                        glVertex2f(70,0);
                        glVertex2f(70,45);
                        glVertex2f(0,45);
                    glEnd();
                    glTranslatef(5,5,0);
                    glScalef(0.25,0.25,0);
                    glColor3f(1,0,0);
                    draw_string("YES");
                glPopMatrix();
                glTranslatef(200,0,0);
                glPushMatrix();
                    if(quit_mouse_hover_no)
                    {
                        glColor3f(149/255.0, 152/255.0, 156/255.0);
                        glBegin(GL_POLYGON);
                            glVertex2f(0,0);
                            glVertex2f(70,0);
                            glVertex2f(70,45);
                            glVertex2f(0,45);
                        glEnd();
                    }
                    glLineWidth(2);
                    glColor3f(91/255.0,161/255.0,247/255.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex2f(0,0);
                        glVertex2f(70,0);
                        glVertex2f(70,45);
                        glVertex2f(0,45);
                    glEnd();
                    glTranslatef(15,5,0);
                    glScalef(0.25,0.25,0);
                    glColor3f(0,1,0);
                    draw_string("NO");
                glPopMatrix();
            glPopMatrix();
    glPopMatrix();
    glLineWidth(1);
}

void draw_start_menu()
{
    glPushMatrix();
    glTranslatef(width/2.0-250,height/2.0-160,0);
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(500,0);
        glVertex2f(500,320);
        glVertex2f(0,320);
    glEnd();
    glLineWidth(3);
    glColor3f(0.3,0.7,0.5);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);
        glVertex2f(500,0);
        glVertex2f(500,320);
        glVertex2f(0,320);
    glEnd();
    glLineWidth(1);
        glPushMatrix();
        glTranslatef(120,250,0);
        glScalef(0.4,0.4,0);
        glColor3f(207/255.0,46/255.0,240/255.0);
        draw_string("GALAXIAN");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(125,180,0);
        glScalef(0.25,0.25,0);
        glColor3f(1,179/255.0,85/255.0);
        draw_string("Highscore: ");
        draw_score(high_score);
        glPopMatrix();

        glPushMatrix();
            if(start_mouse_hover_quit)
            {
                glColor3f(149/255.0, 152/255.0, 156/255.0);
                glBegin(GL_POLYGON);
                    glVertex2f(190,20);
                    glVertex2f(280,20);
                    glVertex2f(280,60);
                    glVertex2f(190,60);
                glEnd();
            }
            glLineWidth(2);
            glColor3f(91/255.0,161/255.0,247/255.0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(190,20);
                glVertex2f(280,20);
                glVertex2f(280,60);
                glVertex2f(190,60);
            glEnd();
        glPopMatrix();

        glLineWidth(2);
            if(start_mouse_hover_start)
            {
                glColor3f(149/255.0, 152/255.0, 156/255.0);
                glBegin(GL_POLYGON);
                    glVertex2f(190,90);
                    glVertex2f(280,90);
                    glVertex2f(280,130);
                    glVertex2f(190,130);
                glEnd();
            }
            glLineWidth(2);
            glColor3f(91/255.0,161/255.0,247/255.0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(190,90);
                glVertex2f(280,90);
                glVertex2f(280,130);
                glVertex2f(190,130);
            glEnd();

        glPushMatrix();
        glTranslatef(200,100,0);
        glScalef(0.25,0.25,0);
        glColor3f(0,1,0);
        draw_string("Start");
        glPopMatrix();


        glPushMatrix();
        glTranslatef(200,30,0);
        glScalef(0.25,0.25,0);
        glColor3f(1,0,0);
        draw_string("Quit");
        glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

void draw_thank_you()
{
    glPushMatrix();
    glTranslatef(width/2.0-250,height/2.0-250,0);
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(500,0);
        glVertex2f(500,500);
        glVertex2f(0,500);
    glEnd();
    glLineWidth(3);
    glColor3f(0.3,0.7,0.5);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);
        glVertex2f(500,0);
        glVertex2f(500,500);
        glVertex2f(0,500);
    glEnd();


        glPushMatrix();
        glTranslatef(125,420,0);
        glScalef(0.4,0.4,0);
        glColor3f(207/255.0,46/255.0,240/255.0);
        draw_string("Made By");
        glPopMatrix();


        glPushMatrix();
        glTranslatef(80,350,0);
        glScalef(0.4,0.4,0);
        glColor3f(105/255.0,64/255.0,239/255.0);
        draw_string("Bug Assassins");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(100,250,0);
        glScalef(0.25,0.25,0);
        glColor3f(240/255.0,212/255.0,30/255.0);
        draw_string("1. Ajith P S");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(100,200,0);
        glScalef(0.25,0.25,0);
        glColor3f(240/255.0,212/255.0,30/255.0);
        draw_string("2. Adarsh Mohata");
        glPopMatrix();


        glPushMatrix();
        glTranslatef(100,150,0);
        glScalef(0.25,0.25,0);
        glColor3f(240/255.0,212/255.0,30/255.0);
        draw_string("3. Ashish Kedia");
        glPopMatrix();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();

    #ifdef __WIN64
        Sleep(5000);
    #elif __WIN32
        Sleep(5000);
    #elif __linux
        sleep(5);
    #elif __unix
        sleep(5);
    #elif __APPLE_CC__
        sleep(5);
    #endif

    exit_game();
}

void maindisp()
{
    glClearColor(0, 0, 0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw_background();
    if(game_state == 1)
    {
        draw_start_menu();
    }
    if(game_state == 2)
    {
        draw_main_ship(ship_x,ship_y);
        draw_bombs();
        draw_bullets();
    }
    else if (game_state == 3)
    {
        draw_pause_menu();
    }
    else if(game_state == 4)
    {
        draw_exit_menu();
    }
    else if(game_state == 5)
    {
        draw_thank_you();
    }
    draw_score_board();
    glFlush();
    glutSwapBuffers();
}

void adjust_menu_bounds()
{
    //For Quit Menu
    left_bound_quit_yes = (width/2.0) + 120 - 250;
    right_bound_quit_yes = left_bound_quit_yes + 70;
    down_bound_quit = (height/2.0) + 50;
    up_bound_quit = down_bound_quit + 45;
    left_bound_quit_no = (width/2.0) + 320 - 250;
    right_bound_quit_no = left_bound_quit_no + 70;

    //For Pause Menu
    left_bound_pause_quit = (width/2.0) + 90 - 250;
    right_bound_pause_quit = left_bound_pause_quit + 140;
    left_bound_pause_resume = left_bound_pause_quit + 200;
    right_bound_pause_resume = right_bound_pause_quit + 200;
    down_bound_pause = (height/2.0) + 50;
    up_bound_pause = down_bound_pause + 45;

    //For Start Menu
    left_bound_start = (width/2.0) - 250 + 190;
    right_bound_start = (width/2.0) - 250 + 280;
    down_bound_start_start = (height/2.0) + 20;
    up_bound_start_start = down_bound_start_start + 40;
    down_bound_start_quit = up_bound_start_start + 30;
    up_bound_start_quit = down_bound_start_quit + 40;
}

void reshape(int w, int h)
{
    ship_x = (ship_x*w)/width;
    width = (GLdouble) w;
    height = (GLdouble) h;
    adjust_menu_bounds();
    seg_len = width/MAX_BOMB;
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    glMatrixMode(GL_MODELVIEW);
}