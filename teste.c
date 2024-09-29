#include <raylib.h>


int	main()
{
	int	height = 500;
	int	width = 500;
	InitWindow(height, width, "Hello World");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
			DrawRectangle(width /3 , height / 3, width /4, height /4, RED);
		EndDrawing();
	}
	CloseWindow();
	return (0);
}
