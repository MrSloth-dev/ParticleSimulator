#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define array_height 100
#define array_width 300
#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1920

#define GRAVITY 1.0f
#define MOVE_SPEED 2.0f
#define ACCELERATION 0.2
#define FRICTION 0.3f
#define MAX_VEL 3
#define JUMP 5.0f


// Material IDs
#define mat_id_p1 -1
#define mat_id_empty 0
#define mat_id_sand  1
#define mat_id_water 2
#define mat_id_stone 3
#define mat_id_smoke  4

// Colors
#define mat_col_p1 (Color)RAYWHITE
#define mat_col_empty (Color){0, 0, 0, 255}
#define mat_col_sand  (Color){194, 178, 128, 255}
#define mat_col_water (Color){0, 119, 190, 255}
#define mat_col_stone (Color){169, 169, 169, 255}
#define mat_col_smoke (Color){50, 50, 50, 255}

typedef struct {
    short id;
    Color color;
    bool updated_this_frame;
} t_particle;

typedef struct s_player
{
    int p_width;
    int p_height;
    int x;
    int y;
    float   vel_x;
    float   vel_y;
    bool    is_facing_right;
    bool    is_jumping;
    short id;
    Texture2D   texture;
} t_player;

typedef struct {
    short radius;
    int x;
    int y;
    short mat_id;
} t_brush;



int InBounds(int y, int x);
int IsEmpty(int y, int x);
void UpdateSand(int y, int x);
void UpdateWater(int y, int x);
void InitBrush(t_brush *brush, t_particle **array);
void DrawFrame(t_particle **array);
void CalculateFrame(t_particle **array);
void ResetUpdateFlags(t_particle **array);


void UpdateWater(int y, int x);
void UpdateSand(int y, int x);
void UpdateStone(int y, int x);
void UpdateSmoke(int y, int x);


