#define VARA 30
#define VARB 30
#define VARC 50
#define VARD 15
#define MAX_MAX_BOMB 50
#define BOMB_MIN_SEC 3
#define BOMB_MAX_SEC 15
#define BULLET_SEC 3
#define SCORE_BOARD_HEIGHT 36
#define SCORE_BOARD_WIDTH 110
#define SCORE_BOARD_PADDING 20
#define PADDING_BELOW 30
#define STARS_MAX 200
#define STARS_MIN 100
#define STARS_MAX_SIZE 150
#define STARS_MIN_SIZE 100

extern GLdouble width, height;
extern double seg_len;
extern int game_state;

//Main Ship Variables
extern bool ship_left, ship_right;
extern int ship_x, ship_y;
extern unsigned int ship_span, FPS, UNIT_MOVE;
extern GLfloat ship_points[13][2];

//Bomb Variables
extern unsigned int MAX_BOMB;
extern GLfloat bomb_pos[MAX_MAX_BOMB][2];
extern bool bomb_present[MAX_MAX_BOMB],bomb_shape[MAX_MAX_BOMB];
extern unsigned int BOMB_COUNT, bomb_speed[MAX_MAX_BOMB], bomb_color[MAX_MAX_BOMB][3];

//Bullets Variable
extern std::vector<struct bullet> bullets;

//Score Variables
extern long long int curr_score,high_score;

//Background Stars
extern int star_pos[STARS_MAX][2], num_stars, k;
extern float star_size[STARS_MAX];
extern unsigned int BACKGROUND_REFRESH_DELAY;

//Mouse Hover Variables
extern bool quit_mouse_hover_yes, quit_mouse_hover_no;
extern bool pause_mouse_hover_resume, pause_mouse_hover_quit;
extern bool start_mouse_hover_start, start_mouse_hover_quit;
extern int left_bound_quit_yes, right_bound_quit_yes, left_bound_quit_no, right_bound_quit_no, up_bound_quit, down_bound_quit;
extern int left_bound_pause_quit, right_bound_pause_quit, left_bound_pause_resume, right_bound_pause_resume, up_bound_pause, down_bound_pause;
extern int left_bound_start, right_bound_start, up_bound_start_quit, down_bound_start_quit, up_bound_start_start, down_bound_start_start;
