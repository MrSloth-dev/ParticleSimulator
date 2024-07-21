#include <raylib.h>
#include "falling.h"
#include <stdlib.h>

int	height = 1080;
int	width = 1920;
int	main()
{
	t_particle **array;
	array = malloc(sizeof(t_particle*) * height);
	for (int k = 0; k < height; k++)
		array[k] = malloc(sizeof(t_particle) * width);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			array[j][i].id = mat_id_empty;
			array[j][i].color = mat_col_empty;
		}
	}
	//InitArray(array, height, width);
	array[100][100].id = mat_id_water;
	array[150][150].id = mat_id_sand;
	InitWindow(width, height, "FallingAutomata");
	while(!WindowShouldClose())
	{
		SetTargetFPS(30);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		//DrawArray(array);
		EndDrawing();
	}
	for (int k = 0; k < height; k++)
		free(array[k]);
	free(array);
	return (0);
}

void	InitArray(t_particle** array, int height, int width)
{
}

void	DrawArray(t_particle** array)
{
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			switch (array[i][j].id) {
				case mat_id_empty:
					DrawPixel(i, j, mat_col_empty); break;
				case mat_id_sand:
					DrawPixel(i, j, mat_col_sand); break;
				case mat_id_water:
					DrawPixel(i, j, mat_col_water); break;
				default :
					DrawPixel(i, j, mat_col_empty); break;
			}
		}
	}
}
