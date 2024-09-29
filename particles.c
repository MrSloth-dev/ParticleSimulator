#include "particle.h"

extern t_particle **array;


void UpdateWater(int y, int x)
{
    if (array[y][x].updated_this_frame)
        return;

    int dir = (rand() % 2) ? 1 : -1;
    int moved = 0;

    if (InBounds(y + 1, x) && IsEmpty(y + 1, x))
    {
        array[y + 1][x].id = mat_id_water;
        array[y][x].id = mat_id_empty;
        array[y + 1][x].updated_this_frame = true;
        moved = 1;
    }
    else if (InBounds(y + 1, x + dir) && IsEmpty(y + 1, x + dir))
    {
        array[y + 1][x + dir].id = mat_id_water;
        array[y][x].id = mat_id_empty;
        array[y + 1][x + dir].updated_this_frame = true;
        moved = 1;
    }
    else if (InBounds(y + 1, x - dir) && IsEmpty(y + 1, x - dir))
    {
        array[y + 1][x - dir].id = mat_id_water;
        array[y][x].id = mat_id_empty;
        array[y + 1][x - dir].updated_this_frame = true;
        moved = 1;
    }
    if (!moved)
    {
        int spread = 3;
        for (int i = 1; i < spread; i++)
        {
            if (InBounds(y, x + i * dir) && IsEmpty(y, x + dir * i))
            {
                array[y][x + dir * i].id = mat_id_water;
                array[y][x].id = mat_id_empty;
                array[y][x + dir * i].updated_this_frame = true;
                moved = 1;
                break;
            }
        }
    }

    if (!moved)
    {
        int spread = 6;
        for (int i = 1; i < spread; i++)
        {
            if (InBounds(y, x - i * dir) && IsEmpty(y, x - dir * i))
            {
                array[y][x - dir * i].id = mat_id_water;
                array[y][x].id = mat_id_empty;
                array[y][x - dir * i].updated_this_frame = true;
                moved = 1;
                break;
            }
        }
    }
    array[y][x].updated_this_frame = true;
}

void UpdateSand(int y, int x)
{
    if (array[y][x].updated_this_frame)
        return;

    int dir = (rand() % 2) ? 1 : -1;

    if (InBounds(y + 1, x) && IsEmpty(y + 1, x))
    {
        array[y + 1][x].id = mat_id_sand;
        array[y][x].id = mat_id_empty;
        array[y + 1][x].updated_this_frame = true;
    }
    else if (InBounds(y + 1, x + dir) && IsEmpty(y + 1, x + dir))
    {
        array[y + 1][x + dir].id = mat_id_sand;
        array[y][x].id = mat_id_empty;
        array[y + 1][x + dir].updated_this_frame = true;
    }
    else if (InBounds(y + 1, x - dir) && IsEmpty(y + 1, x - dir))
    {
        array[y + 1][x - dir].id = mat_id_sand;
        array[y][x].id = mat_id_empty;
        array[y + 1][x - dir].updated_this_frame = true;
    }

    array[y][x].updated_this_frame = true;
}

void    PushLiquid(int liq_y, int liq_x)
{
    int dir = rand() % 2? 1 : -1;
}

void UpdateStone(int y, int x)
{
    if (array[y][x].updated_this_frame)
        return;
    array[y][x].updated_this_frame = true;
}



void UpdateSmoke(int y, int x)
{
    if (array[y][x].updated_this_frame)
        return;

    int dir = (rand() % 2) ? 1 : -1;

    if (InBounds(y - 1, x) && IsEmpty(y - 1, x))
    {
        array[y - 1][x].id = mat_id_smoke;
        array[y][x].id = mat_id_empty;
        array[y - 1][x].updated_this_frame = true;
    }
    else if (InBounds(y - 1, x + dir) && IsEmpty(y - 1, x + dir))
    {
        array[y - 1][x + dir].id = mat_id_smoke;
        array[y][x].id = mat_id_empty;
        array[y - 1][x + dir].updated_this_frame = true;
    }
    else if (InBounds(y - 1, x - dir) && IsEmpty(y - 1, x - dir))
    {
        array[y - 1][x - dir].id = mat_id_smoke;
        array[y][x].id = mat_id_empty;
        array[y - 1][x - dir].updated_this_frame = true;
    }
    else if (InBounds(y, x + dir) && IsEmpty(y, x + dir))
    {
        array[y][x + dir].id = mat_id_smoke;
        array[y][x].id = mat_id_empty;
        array[y][x + dir].updated_this_frame = true;
    }
    else if (InBounds(y, x - dir) && IsEmpty(y, x - dir))
    {
        array[y][x - dir].id = mat_id_smoke;
        array[y][x].id = mat_id_empty;
        array[y][x - dir].updated_this_frame = true;
    }

    array[y][x].updated_this_frame = true;
}

