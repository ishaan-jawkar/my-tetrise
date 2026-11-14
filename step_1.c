#include <stdio.h>
#define row 10
#define column 20
char boxes_grid[row][column];
void make_boxes()
{
   for(int i=0;i<10;i++)
   {
    for(int j=0;j<20;j++)
    {
       boxes_grid[i][j]='*';
    }
   }
}
int main()
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
return 0;
    }