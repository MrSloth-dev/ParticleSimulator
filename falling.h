
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

// For now, all particle information will simply be a value to determine its material id
#define mat_id_empty (short)0
#define mat_id_sand  (short)1
#define mat_id_water (short)2
#define mat_id_salt (short)3
#define mat_id_wood (short)4
#define mat_id_fire (short)5
#define mat_id_smoke (short)6
#define mat_id_ember (short)7
#define mat_id_steam (short)8
#define mat_id_gunpowder (short)9
#define mat_id_oil (short)10
#define mat_id_lava (short)11
#define mat_id_stone (short)12
#define mat_id_acid (short)13

// Colors
#define mat_col_empty (Color){0, 0, 0, 0}
#define mat_col_sand  (Color){150, 100, 50, 255}
#define mat_col_salt  (Color){200, 180, 190, 255}
#define mat_col_water (Color){20, 100, 170, 200}
#define mat_col_stone (Color){120, 110, 120, 255}
#define mat_col_wood (Color){60, 40, 20, 255}
#define mat_col_fire  (Color){150, 20, 0, 255}
#define mat_col_smoke (Color){50, 50, 50, 255}
#define mat_col_ember (Color){200, 120, 20, 255}
#define mat_col_steam (Color){220, 220, 250, 255}
#define mat_col_gunpowder (Color){60, 60, 60, 255}
#define mat_col_oil (Color){80, 70, 60, 255}
#define mat_col_lava  (Color){200, 50, 0, 255}
#define mat_col_acid  (Color){90, 200, 60, 255}
typedef struct s_particle {
	short	id;
	Color	color;
	short	updated_this_frame;
} t_particle;

void	InitArray(t_particle **array, int height, int width);
void	DrawArray(t_particle **array);
