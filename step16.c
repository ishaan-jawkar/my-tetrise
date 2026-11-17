#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// Define grid dimensions (adjust if defined elsewhere in your header)
int row = 20;
int column = 10;

// Tetrominoes blueprint array
const char tetromeinoes[7][4][4] = {
    // I-Block
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
    // O-Block
    {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    // S-Block
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    // Z-Block
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // L-Block
    {{0,1,0,0}, {0,1,0,0}, {0,1,1,0}, {0,0,0,0}},
    // J-Block
    {{0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0}},
    // T-Block
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}
};

// Clear the screen buffer grid to dots
void make_boxes(char **boxes_grid)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            if(boxes_grid[i][j] != '@') // Keep locked blocks
            {
                boxes_grid[i][j] = '.';
            }
        }
    }
}

// 90-degree Clockwise Matrix Rotation
void rotate(char piece[4][4])
{
    char temp[4][4];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            temp[i][j] = piece[i][j];
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            piece[j][3 - i] = temp[i][j];
        }
    }
}

// Collision detection function prototype / stub (adjust parameters to match your existing implementation)
int cheak_collision(int x_tar, int y_tar, char piece[4][4], char **boxes_grid)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(piece[i][j] == 1)
            {
                int next_x = x_tar + j;
                int next_y = y_tar + i;

                // Check wall and floor boundaries
                if(next_x < 0 || next_x >= column || next_y >= row)
                {
                    return 1; // Collision detected
                }
                // Check collision with already locked blocks on grid
                if(next_y >= 0 && boxes_grid[next_y][next_x] == '@')
                {
                    return 1;
                }
            }
        }
    }
    return 0; // No collision
}

// Keyboard input handler with pass-by-reference
void input(int *xco, int *yco, char curr_piece[4][4], char **boxes_grid)
{
    if(_kbhit())
    {
        char ch = _getch();
        if(ch == 'a' || ch == 'A')
        {
            if(cheak_collision((*xco) - 1, *yco, curr_piece, boxes_grid) == 0)
            {
                (*xco)--;
            }
        }
        else if(ch == 's' || ch == 'S')
        {
            if(cheak_collision(*xco, (*yco) + 1, curr_piece, boxes_grid) == 0)
            {
                (*yco)++;
            }
        }
        else if(ch == 'd' || ch == 'D')
        {
            if(cheak_collision((*xco) + 1, *yco, curr_piece, boxes_grid) == 0)
            {
                (*xco)++;
            }
        }
        else if(ch == 'w' || ch == 'W')
        {
            char temp[4][4];
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    temp[i][j] = curr_piece[i][j];
                }
            }
            rotate(temp);
            if(cheak_collision(*xco, *yco, temp, boxes_grid) == 0)
            {
                rotate(curr_piece);
            }
        }
    }
}

int main()
{
    // Dynamically allocate 2D screen buffer grid
    char **boxes_grid = (char **)malloc(row * sizeof(char *));
    for(int i = 0; i < row; i++)
    {
        boxes_grid[i] = (char *)malloc(column * sizeof(char));
    }

    // Initialize grid with dots
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            boxes_grid[i][j] = '.';
        }
    }

    srand(time(NULL));

    int xco = 3;
    int yco = 0;
    int shape = rand() % 7;

    char curr_piece[4][4];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            curr_piece[i][j] = tetromeinoes[shape][i][j];
        }
    }

    while(1)
    {
        input(&xco, &yco, curr_piece, boxes_grid);

        // Clear empty cells while keeping locked `@` blocks
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                if(boxes_grid[i][j] != '@')
                {
                    boxes_grid[i][j] = '.';
                }
            }
        }

        // Overlay current active piece onto the grid buffer
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(curr_piece[i][j] == 1)
                {
                    int cur_x = xco + j;
                    int cur_y = yco + i;

                    if(cur_x >= 0 && cur_y >= 0 && cur_x < column && cur_y < row)
                    {
                        boxes_grid[cur_y][cur_x] = '@';
                    }
                }
            }
        }

        system("cls");

        // Render game board
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                printf("%c", boxes_grid[i][j]);
            }
            printf("\n");
        }

        // Gravity drop / collision check
// Gravity drop / collision check
        if(cheak_collision(xco, yco + 1, curr_piece, boxes_grid) == 0)
        {
            yco++; // Move down if space is free
        }
        else
        {
            // LOCK THE PIECE PERMANENTLY INTO THE GRID WHEN IT HITS THE BOTTOM/OBSTACLE
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(curr_piece[i][j] == 1)
                    {
                        int cur_x = xco + j;
                        int cur_y = yco + i;
                        if(cur_x >= 0 && cur_y >= 0 && cur_x < column && cur_y < row)
                        {
                            boxes_grid[cur_y][cur_x] = '@';
                        }
                    }
                }
            }

            // Spawn next piece at the top
            yco = 0;
            xco = 3;
            shape = rand() % 7;
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    curr_piece[i][j] = tetromeinoes[shape][i][j];
                }
            }
        }

        Sleep(500);
    }

    // Free dynamically allocated memory in reverse order
    for(int i = 0; i < row; i++)
    {
        free(boxes_grid[i]);
    }
    free(boxes_grid);

    return 0;
}