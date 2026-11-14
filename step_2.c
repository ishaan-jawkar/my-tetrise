#include <stdio.h>
#define row 10
#define column 20
char boxes_grid[row][column];
void make_boxes()
{
   for(int i=0;i<row;i++)
   {
    for(int j=0;j<column;j++)
    {
       boxes_grid[i][j]='.';
    }
   }
}
const char tetromeinoes[4][4]=
{
    //i-block
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
};
int main()
{
    {
 make_boxes();
   for(int i=0;i<10;i++)
   {
    for(int j=0;j<20;j++)
    {
        printf("%c",boxes_grid[i][j]);
    }
    printf("\n");
   }
    }
    for(int i=0;i<4;i++)
    {
    for(int j=0;j<4;j++)        
    {
        if(tetromeinoes[i][j]==1)
        {
            printf("@");
        }
        else
        {
            printf(".");
        }
    }
        printf("\n");
}
return 0;
}