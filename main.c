#include "particle.h"
#include <raylib.h>
#include <stdbool.h>
#include <wctype.h>


t_player p1;
t_particle **array;

int	ft_convert(int i, int new_min, int new_max, int old_min, int old_max)
{
	return ((new_max - new_min) *(i - old_min) / (old_max - old_min) + new_min);
}

void    DrawUI(t_brush *brush)
{
    switch (brush->mat_id) {
        case mat_id_sand:
            DrawRectangle(28, 28, 24, 24, RAYWHITE); break;
        case mat_id_water:
            DrawRectangle(68, 28, 24, 24, RAYWHITE); break;
        case mat_id_stone:
            DrawRectangle(108, 28, 24, 24,RAYWHITE); break;
        case mat_id_smoke:
            DrawRectangle(148, 28, 24, 24,RAYWHITE); break;
        default:
            DrawRectangle(80, 28, 24, 24, RAYWHITE); break;
    }
    DrawRectangle(30, 30, 20, 20, mat_col_sand);
    DrawRectangle(70, 30, 20, 20, mat_col_water);
    DrawRectangle(110, 30, 20, 20, mat_col_stone);
    DrawRectangle(150, 30, 20, 20, mat_col_smoke);
}

void    InitPlayer(void)
{
    p1.p_width = 10;
    p1.p_height = 10;
    p1.x = array_width / 2;
    p1.y = array_height / 2;
    p1.id = mat_id_p1;
    p1.vel_y = GRAVITY;
    p1.vel_x = 0;
    p1.is_facing_right = true;
    p1.texture = LoadTexture("./texture.png");

    array[p1.y][p1.x].id = mat_id_p1;
}

bool IsOnGround()
{
    return !InBounds(p1.y + 1, p1.x) || !IsEmpty(p1.y + 1, p1.x);
}

void PlayerMove()
{

    if (IsKeyDown(KEY_D))
    {
        p1.is_facing_right = true;
        p1.vel_x = MOVE_SPEED;
    }
    else if (IsKeyDown(KEY_A))
    {
        p1.is_facing_right = false;
        p1.vel_x = -MOVE_SPEED;
    }
    else
        p1.vel_x *= 0.9f;

    if (p1.vel_x > 5) p1.vel_x = MAX_VEL;
    if (p1.vel_x < -5) p1.vel_x = -MAX_VEL;

    if (IsKeyPressed(KEY_SPACE) && IsOnGround())
    {
        p1.vel_y -= JUMP;
        p1.is_jumping = true;
    }

    if (!IsOnGround())
        p1.vel_y += GRAVITY;
    else
    {
        // p1.vel_y = 0;
        p1.is_jumping = false;
    }

    float new_x = p1.x + p1.vel_x;
    float new_y = p1.y + p1.vel_y;

    // Check boundaries horizontal
    if (InBounds(new_y, new_x) && IsEmpty(new_y, new_x))
    {
        array[p1.y][p1.x].id = mat_id_empty;
        p1.x = new_x;
        p1.y = new_y;
        new_x = p1.x;
        array[p1.y][p1.x].id = mat_id_p1;
    }
    else
    {
        p1.vel_x = 0;
        p1.vel_y = 0;
    }
    // Check boundaries vertical
    if (!InBounds(new_y, new_x) || !IsEmpty(new_y, new_x))
    {
        new_y = p1.y + p1.vel_y / 2;
        p1.vel_y = 0;
    }
    //UpdatePosition
    if (InBounds(new_y, new_x) && IsEmpty(new_y, new_x))
    {
        array[p1.y][p1.x].id = mat_id_empty;
        p1.x = new_x;
        p1.y = new_y;
        array[p1.y][p1.x].id = mat_id_p1;
    }
}

int main()
{
    srand(time(NULL));
    t_brush brush;
    brush.mat_id = mat_id_sand;
    brush.radius = 4;


    array = malloc(sizeof(t_particle*) * array_height);
    for (int k = 0; k < array_height; k++)
        array[k] = malloc(sizeof(t_particle) * array_width);

    for (int y = 0; y < array_height; y++)
    {
        for (int x = 0; x < array_width; x++)
        {
            array[y][x].id = mat_id_empty;
            array[y][x].color = mat_col_empty;
            array[y][x].updated_this_frame = false;
        }
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FallingAutomata");
    InitPlayer();
    SetTargetFPS(30);
    p1.texture = LoadTexture("./texture.png");

    while (!WindowShouldClose())
    {
        ResetUpdateFlags(array);
        InitBrush(&brush, array);
        BeginDrawing();
        DrawText(TextFormat("Vel_x = %d", p1.vel_x), SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10, 50, RAYWHITE);
        PlayerMove();
        CalculateFrame(array);
        DrawFrame(array);
        DrawUI(&brush);
        DrawTexture(p1.texture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, BLUE);
        // DrawTexture(p1.texture, SCRE, , BLUE);
        EndDrawing();
    }

    for (int k = 0; k < array_height; k++)
        free(array[k]);
    free(array);

    CloseWindow();
    return 0;
}

void ResetUpdateFlags(t_particle **array)
{
    for (int y = 0; y < array_height; y++)
    {
        for (int x = 0; x < array_width; x++)
        {
            array[y][x].updated_this_frame = false;
        }
    }
}


void InitBrush(t_brush *brush, t_particle **array)
{
    brush->x = GetMouseX();
    brush->y = GetMouseY();

    if (IsKeyDown(KEY_ONE))
        brush->mat_id = mat_id_sand;
    else if (IsKeyDown(KEY_TWO))
        brush->mat_id = mat_id_water;
    else if (IsKeyDown(KEY_THREE))
        brush->mat_id = mat_id_stone;
    else if (IsKeyDown(KEY_FOUR))
        brush->mat_id = mat_id_smoke;
    else if (IsKeyDown(KEY_FIVE))
        brush->mat_id = mat_id_empty;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        for (int dy = -brush->radius; dy <= brush->radius; dy++)
        {
            for (int dx = -brush->radius; dx <= brush->radius; dx++)
            {
                int x = ft_convert(brush->x + dx, 0, array_width, 0, SCREEN_WIDTH);
                int y = ft_convert(brush->y + dy, 0, array_height, 0, SCREEN_HEIGHT);
                if (InBounds(y, x) && (dx * dx + dy * dy <= brush->radius * brush->radius))
                    array[y][x].id = brush->mat_id;
            }
        }
    }
}

int InBounds(int y, int x)
{
    return (x >= 0 && y >= 0 && x < array_width && y < array_height);
}

int IsEmpty(int y, int x)
{
    return (array[y][x].id == mat_id_empty);
}



void DrawFrame(t_particle **array)
{
    ClearBackground(mat_col_empty);
    for (int y = 0; y < array_height; y++)
    {
        for (int x = 0; x < array_width; x++)
        {
            switch (array[y][x].id) {
                case mat_id_p1:
                    array[y][x].color = mat_col_p1; break;
                case mat_id_empty:
                    array[y][x].color = mat_col_empty; break;
                case mat_id_sand:
                    array[y][x].color = mat_col_sand; break;
                case mat_id_water:
                    array[y][x].color = mat_col_water; break;
                case mat_id_stone:
                    array[y][x].color = mat_col_stone; break;
                case mat_id_smoke:
                    array[y][x].color = mat_col_smoke; break;
                default:
                    array[y][x].color = mat_col_empty; break;
            }
            float scale_x = (float)SCREEN_WIDTH / array_width;
            float scale_y = (float)SCREEN_HEIGHT / array_height;
            DrawRectangle(x * scale_x, y * scale_y, scale_x * 10, scale_y * 10, array[y][x].color);
        }
            // Draw the player as a rectangle
    float scale_x = (float)SCREEN_WIDTH / array_width;
    float scale_y = (float)SCREEN_HEIGHT / array_height;
    Rectangle playerRect = {
        p1.x * scale_x,
        p1.y * scale_y,
        2 * scale_x,
        2 * scale_y
    };
    DrawRectangleRec(playerRect, mat_col_p1);

    // Draw direction indicator
    Vector2 start = {p1.x * scale_x + (playerRect.width / 2), p1.y * scale_y + (playerRect.height / 2)};
    Vector2 end = {
        start.x + (p1.is_facing_right ? 10 : -10),
        start.y
    };
    DrawLineEx(start, end, 2, RED);
    }
}

void CalculateFrame(t_particle **array)
{
    for (int y = array_height - 1; y >= 0; y--)
    {
        for (int x = 0; x < array_width; x++)
        {
            switch (array[y][x].id) {
                case mat_id_empty:
                    break;
                case mat_id_p1:
                    break;
                case mat_id_sand:
                    UpdateSand(y, x); break;
                case mat_id_water:
                    UpdateWater(y, x); break;
                case mat_id_stone:
                    UpdateStone(y, x); break;
                case mat_id_smoke:
                    UpdateSmoke(y, x); break;
                default:
                    break;
            }
        }
    }
}
