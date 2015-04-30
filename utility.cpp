
//Utility Function to draw circles
#include "declaration.cpp"
void cirsetpix(int circenx, int circeny, int x, int y)
{
	glVertex2i(circenx+x,circeny+y);
	glVertex2i(circenx+x,circeny-y);
	glVertex2i(circenx-x,circeny+y);
	glVertex2i(circenx-x,circeny-y);
	glVertex2i(circenx+y,circeny+x);
	glVertex2i(circenx+y,circeny-x);
	glVertex2i(circenx-y,circeny+x);
	glVertex2i(circenx-y,circeny-x);
}
void dispcir(int circenx, int circeny, int cirrad)
{
	int x = 0, y = cirrad;
	int dec = 1-cirrad;
	glPointSize(4);
	glBegin(GL_POINTS);
	cirsetpix(circenx,circeny,x,y);
	while(y>x)
	{
		if(dec>=0)
		{
			dec+=2-(2*y);
			y--;
		}
		dec += 3 + (2*x);
		x++;
		cirsetpix(circenx,circeny,x,y);
	}
	glEnd();
}

void add_bullet()
{
    struct bullet tp;
    tp.x = ship_x + VARA + (VARB/2.0);
    tp.y = ship_y + (4.0*VARC)/3.0;
    bullets.push_back(tp);
}

void write_settings()
{
    FILE *out;
    out = fopen("settings","w");
    if(out == NULL)
    {
        return ;
    }
    fprintf(out,"# Settings can be changed by changing the values of the numbers. Please do not remove the brackets\n");
    fprintf(out,"Maximum Bombs = [ %u ]\n",MAX_BOMB);
    fprintf(out,"Unit Move = [ %u ]\n",UNIT_MOVE);
    fprintf(out,"Background Refresh Rate = [ %u ]\n",BACKGROUND_REFRESH_DELAY);
    fclose(out);
}

void set_settings()
{
    int d_max,d_unit,d_refresh;

    d_max=10;
    d_unit=5;
    d_refresh=200;

    FILE *in;
    in = fopen("settings","r");
    if(in == NULL)
    {
        MAX_BOMB=d_max;
        UNIT_MOVE=d_unit;
        BACKGROUND_REFRESH_DELAY=d_refresh;
        write_settings();
        return;
    }
    int c;
    while(c=getc(in),c!='[');
    fscanf(in,"%u",&MAX_BOMB);
    while(c=getc(in),c!='[');
    fscanf(in,"%u",&UNIT_MOVE);
    while(c=getc(in),c!='[');
    fscanf(in,"%u",&BACKGROUND_REFRESH_DELAY);

    if(!(MAX_BOMB<=MAX_MAX_BOMB && MAX_BOMB>=1))
    MAX_BOMB=d_max;

    if(!(UNIT_MOVE<=20 && UNIT_MOVE>=1))
    UNIT_MOVE=d_unit;

    if(!(BACKGROUND_REFRESH_DELAY<=500 && BACKGROUND_REFRESH_DELAY>=60))
    BACKGROUND_REFRESH_DELAY=d_refresh;

    fclose(in);
}

void get_high_score()
{
    FILE *in;
    in = fopen("highscore","rb");
    if(in==NULL)
    {
        high_score=0;
    }
    else
    {
        fread(&high_score,1,sizeof(long long int),in);
        fclose(in);
    }
}
void set_high_score()
{

    if(curr_score <= high_score) return;
    high_score = curr_score;
    FILE *out;
    out = fopen("highscore","wb");
    if(out == NULL)
    {
        return;
    }
    fwrite(&high_score, 1, sizeof(long long int), out);
    fclose(out);
}

void exit_game()
{
    set_high_score();
    bullets.clear();
    printf("Thank You For Playing Galaxian !!\n\n\n");
    printf("This Game was made by :\n1. Ashish Kedia (12IT14)\n2. Ajith P S (12IT04)\n3. Adarsh Mohata (12IT03)\nNational Institute of Technology Karnataka, Surathkal");
    printf("\n\nYour Score : %lld\nHigh Score : %lld\n\n",curr_score,high_score);
    exit(0);
}
